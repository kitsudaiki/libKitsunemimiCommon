/**
 *  @file    binary_file_direct.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief class for binary-file-handling
 */

#include <libKitsunemimiCommon/files/binary_file_direct.h>

using Kitsunemimi::DataBuffer;

namespace Kitsunemimi
{

/**
 * @brief constructor
 *
 * @param filePath file-path of the binary-file
 */
BinaryFileDirect::BinaryFileDirect(const std::string &filePath)
{
    m_filePath = filePath;

    ErrorContainer error;
    if(initFile(error) == false) {
        LOG_ERROR(error);
    }
}

/**
 * @brief destructor
 */
BinaryFileDirect::~BinaryFileDirect()
{
    ErrorContainer error;
    if(closeFile(error) == false) {
        LOG_ERROR(error);
    }
}

/**
 * @brief create a new file or open an existing file
 *
 * @param error reference for error-output
 *
 * @return true is successful, else false
 */
bool
BinaryFileDirect::initFile(ErrorContainer &error)
{
    m_fileDescriptor = open(m_filePath.c_str(),
                            O_CREAT | O_DIRECT | O_RDWR | O_LARGEFILE,
                            0666);
    m_blockSize = 512;

    // check if file is open
    if(m_fileDescriptor == -1)
    {
        error.addMeesage("Failed to initialize binary file for path '" + m_filePath + "'");
        return false;
    }

    return updateFileSize(error);
}

/**
 * @brief allocate new storage at the end of the file
 *
 * @param error reference for error-output
 *
 * @return true is successful, else false
 */
bool
BinaryFileDirect::allocateStorage(const uint64_t numberOfBlocks,
                                  const uint32_t blockSize,
                                  ErrorContainer &error)
{
    if(numberOfBlocks == 0) {
        return true;
    }

    // precheck
    if(blockSize % m_blockSize != 0
            || m_fileDescriptor < 0)
    {
        error.addMeesage("Failed to read segment of binary file for path '"
                         + m_filePath
                         + "', because the precheck failed. Either the buffer is incompatible "
                           "or the file is not open.");
        return false;
    }

    return allocateStorage(numberOfBlocks * blockSize, error);
}

/**
 * @brief allocate new storage at the end of the file
 *
 * @return true is successful, else false
 */
bool
BinaryFileDirect::allocateStorage(const uint64_t numberOfBytes,
                                  ErrorContainer &error)
{
    // set first to the start of the file and allocate the new size at the end of the file
    lseek(m_fileDescriptor, 0, SEEK_SET);
    const long ret = posix_fallocate(m_fileDescriptor,
                                     static_cast<long>(m_totalFileSize),
                                     static_cast<long>(numberOfBytes));

    // check if allocation was successful
    if(ret != 0)
    {
        // TODO: process errno
        error.addMeesage("Failed to allocate new storage for the binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    // got the the end of the file
    return updateFileSize(error);
}

/**
 * @brief update size-information from the file
 *
 * @param error reference for error-output
 *
 * @return false, if file not open, else true
 */
bool
BinaryFileDirect::updateFileSize(ErrorContainer &error)
{
    if(m_fileDescriptor == -1)
    {
        error.addMeesage("Failed to allocate new storage for the binary file for path '"
                         + m_filePath
                         + "', because the file is not open.");
        return false;
    }

    // check if filesize is really 0 or check is requested
    const long ret = lseek(m_fileDescriptor, 0, SEEK_END);
    if(ret >= 0) {
        m_totalFileSize = static_cast<uint64_t>(ret);
    }

    lseek(m_fileDescriptor, 0, SEEK_SET);

    return true;
}

/**
 * @brief read a complete binary file into a data-buffer object
 *
 * @param buffer reference to the buffer, where the data should be written into
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::readCompleteFile(DataBuffer &buffer,
                                   ErrorContainer &error)
{
    // go to the end of the file to get the size of the file
    const long size = lseek(m_fileDescriptor, 0, SEEK_END);
    if(size <= 0)
    {
        error.addMeesage("Failed to find the end of the binary file for path '"
                         + m_filePath
                         + "'.");
        return false;
    }

    // check if size of the file is not compatible with direct-io
    if(buffer.blockSize % 512 != 0)
    {
        error.addMeesage("Failed to read the binary file for path '"
                         + m_filePath
                         + "', because the buffer has a incompatible blocksize, "
                           "which is not a multiple of 512.");
        return false;
    }

    // resize buffer to the size of the file
    uint64_t numberOfBlocks = (static_cast<uint64_t>(size) / buffer.blockSize);
    if(size % buffer.blockSize != 0) {
        numberOfBlocks++;
    }
    allocateBlocks_DataBuffer(buffer, numberOfBlocks);

    // go to the beginning of the file again and read the complete file into the buffer
    lseek(m_fileDescriptor, 0, SEEK_SET);
    const ssize_t ret = read(m_fileDescriptor, buffer.data, static_cast<uint64_t>(size));
    if(ret == -1)
    {
        // TODO: process errno
        error.addMeesage("Failed to read the binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    // size buffer-size
    buffer.usedBufferSize = static_cast<uint64_t>(size);

    return true;
}

/**
 * @brief write a complete buffer into a binary-file
 *
 * @param buffer reference to the buffer with the data, which should be written into the file
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::writeCompleteFile(DataBuffer &buffer,
                                    ErrorContainer &error)
{
    // check if size of the buffer is not compatible with direct-io
    if(buffer.blockSize % 512 != 0)
    {
        error.addMeesage("Failed to write to binary file for path '"
                         + m_filePath
                         + "', because the buffer has a incompatible blocksize, "
                           "which is not a multiple of 512.");
        return false;
    }

    // resize file to the size of the buffer
    int64_t sizeDiff = buffer.usedBufferSize - m_totalFileSize;
    if(sizeDiff > 0)
    {
        // round diff up to full block-size
        if(sizeDiff % m_blockSize != 0) {
            sizeDiff += m_blockSize - (sizeDiff % m_blockSize);
        }

        // allocate additional memory
        if(allocateStorage(sizeDiff, error) == false)
        {
            error.addMeesage("Failed to write to binary file for path '"
                             + m_filePath
                             + "'");
            return false;
        }
    }

    // go to the beginning of the file and write data to file
    lseek(m_fileDescriptor, 0, SEEK_SET);
    const ssize_t ret = write(m_fileDescriptor, buffer.data, buffer.usedBufferSize);
    if(ret == -1)
    {
        // TODO: process errno
        error.addMeesage("Failed to write to binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    return true;
}

/**
 * @brief read a readSegment of the file
 *
 *
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::readSegment(DataBuffer &buffer,
                              const uint64_t startBlockInFile,
                              const uint64_t numberOfBlocks,
                              const uint64_t startBlockInBuffer,
                              ErrorContainer &error)
{
    if(numberOfBlocks == 0) {
        return true;
    }

    // prepare blocksize for mode
    const uint16_t blockSize = buffer.blockSize;
    const uint64_t numberOfBytes = numberOfBlocks * blockSize;
    const uint64_t startBytesInFile = startBlockInFile * blockSize;
    const uint64_t startBytesInBuffer = startBlockInBuffer * blockSize;

    // precheck
    if(startBytesInFile + numberOfBytes > m_totalFileSize
            || startBytesInBuffer + numberOfBytes > buffer.numberOfBlocks * buffer.blockSize
            || m_fileDescriptor < 0)
    {
        error.addMeesage("Failed to read segment of binary file for path '"
                         + m_filePath
                         + "', because the precheck failed. Either the buffer is incompatible "
                           "or the file is not open.");
        return false;
    }

    // go to the requested position and read the block
    const long retSeek = lseek(m_fileDescriptor,
                               static_cast<long>(startBytesInFile),
                               SEEK_SET);
    if(retSeek < 0)
    {
        error.addMeesage("Failed to go to the requested read position in binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    const ssize_t ret = read(m_fileDescriptor,
                             static_cast<uint8_t*>(buffer.data) + (startBytesInBuffer),
                             numberOfBytes);

    if(ret == -1)
    {
        // TODO: process errno
        error.addMeesage("Failed to read segment of binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    return true;
}

/**
 * @brief write a block of the file
 *
 *
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::writeSegment(DataBuffer &buffer,
                               const uint64_t startBlockInFile,
                               const uint64_t numberOfBlocks,
                               const uint64_t startBlockInBuffer,
                               ErrorContainer &error)
{
    if(numberOfBlocks == 0) {
        return true;
    }

    // prepare blocksize for mode
    const uint16_t blockSize = buffer.blockSize;
    const uint64_t numberOfBytes = numberOfBlocks * blockSize;
    const uint64_t startBytesInFile = startBlockInFile * blockSize;
    const uint64_t startBytesInBuffer = startBlockInBuffer * blockSize;

    // precheck
    if(startBytesInFile + numberOfBytes > m_totalFileSize
            || startBytesInBuffer + numberOfBytes > buffer.numberOfBlocks * buffer.blockSize
            || m_fileDescriptor < 0)
    {
        error.addMeesage("Failed to write segment to binary file for path '"
                         + m_filePath
                         + "', because the precheck failed. Either the buffer is incompatible "
                           "or the file is not open.");
        return false;
    }

    // go to the requested position and write the block
    const long retSeek = lseek(m_fileDescriptor,
                               static_cast<long>(startBytesInFile),
                               SEEK_SET);
    if(retSeek < 0)
    {
        error.addMeesage("Failed to go to the requested write position in binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    // write data to file
    const ssize_t ret = write(m_fileDescriptor,
                              static_cast<uint8_t*>(buffer.data) + startBytesInBuffer,
                              numberOfBytes);

    if(ret == -1)
    {
        // TODO: process errno
        error.addMeesage("Failed to write segment to binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    // sync file
    fdatasync(m_fileDescriptor);

    return true;
}

/**
 * @brief close the cluser-file
 *
 * @param error reference for error-output
 *
 * @return true, if file-descriptor is valid, else false
 */
bool
BinaryFileDirect::closeFile(ErrorContainer &error)
{
    // precheck
    if(m_fileDescriptor == -1) {
        return true;
    }

    // try to close file
    if(close(m_fileDescriptor) < 0)
    {
        // TODO: process errno
        error.addMeesage("Failed to close binary file for path '"
                         + m_filePath
                         + "'");
        return false;
    }

    m_fileDescriptor = -1;
    return true;
}

} // namespace Kitsunemimi
