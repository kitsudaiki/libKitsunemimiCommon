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

    initFile();
}

/**
 * @brief destructor
 */
BinaryFileDirect::~BinaryFileDirect()
{
    closeFile();
}

/**
 * @brief create a new file or open an existing file
 *
 * @return true is successful, else false
 */
bool
BinaryFileDirect::initFile()
{
    m_fileDescriptor = open(m_filePath.c_str(),
                            O_CREAT | O_DIRECT | O_RDWR | O_LARGEFILE,
                            0666);
    m_blockSize = 512;

    // check if file is open
    if(m_fileDescriptor == -1) {
        return false;
    }

    return updateFileSize();
}

/**
 * @brief allocate new storage at the end of the file
 *
 * @return true is successful, else false
 */
bool
BinaryFileDirect::allocateStorage(const uint64_t numberOfBlocks,
                                  const uint32_t blockSize)
{
    // precheck
    if(numberOfBlocks == 0
            || m_fileDescriptor < 0
            || blockSize % m_blockSize != 0)
    {
        return false;
    }

    return allocateStorage(numberOfBlocks * blockSize);
}

/**
 * @brief allocate new storage at the end of the file
 *
 * @return true is successful, else false
 */
bool
BinaryFileDirect::allocateStorage(const uint64_t numberOfBytes)
{
    // set first to the start of the file and allocate the new size at the end of the file
    lseek(m_fileDescriptor, 0, SEEK_SET);
    long ret = posix_fallocate(m_fileDescriptor,
                               static_cast<long>(m_totalFileSize),
                               static_cast<long>(numberOfBytes));

    // check if allocation was successful
    if(ret != 0)
    {
        // TODO: process errno
        return false;
    }

    // got the the end of the file
    updateFileSize();

    return true;
}

/**
 * @brief update size-information from the file
 *
 * @return false, if file not open, else true
 */
bool
BinaryFileDirect::updateFileSize()
{
    if(m_fileDescriptor == -1) {
        return false;
    }

    // check if filesize is really 0 or check is requested
    long ret = lseek(m_fileDescriptor, 0, SEEK_END);
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
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::readCompleteFile(DataBuffer &buffer)
{
    // go to the end of the file to get the size of the file
    const long size = lseek(m_fileDescriptor, 0, SEEK_END);
    if(size <= 0) {
        return false;
    }

    // check if size of the file is not compatible with direct-io
    if(buffer.blockSize % 512 != 0) {
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
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::writeCompleteFile(DataBuffer &buffer)
{
    // check if size of the buffer is not compatible with direct-io
    if(buffer.blockSize % 512 != 0) {
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
        if(allocateStorage(sizeDiff) == false) {
            return false;
        }
    }

    // go to the beginning of the file and write data to file
    lseek(m_fileDescriptor, 0, SEEK_SET);
    const ssize_t ret = write(m_fileDescriptor, buffer.data, buffer.usedBufferSize);
    if(ret == -1)
    {
        // TODO: process errno
        return false;
    }

    return true;
}

/**
 * @brief read a readSegment of the file
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::readSegment(DataBuffer &buffer,
                              const uint64_t startBlockInFile,
                              const uint64_t numberOfBlocks,
                              const uint64_t startBlockInBuffer)
{
    // prepare blocksize for mode
    const uint16_t blockSize = buffer.blockSize;
    const uint64_t numberOfBytes = numberOfBlocks * blockSize;
    const uint64_t startBytesInFile = startBlockInFile * blockSize;
    const uint64_t startBytesInBuffer = startBlockInBuffer * blockSize;

    // precheck
    if(numberOfBlocks == 0
            || startBytesInFile + numberOfBytes > m_totalFileSize
            || startBytesInBuffer + numberOfBytes > buffer.numberOfBlocks * buffer.blockSize
            || m_fileDescriptor < 0)
    {
        return false;
    }

    // go to the requested position and read the block
    lseek(m_fileDescriptor,
          static_cast<long>(startBytesInFile),
          SEEK_SET);
    ssize_t ret = read(m_fileDescriptor,
                       static_cast<uint8_t*>(buffer.data) + (startBytesInBuffer),
                       numberOfBytes);

    if(ret == -1)
    {
        // TODO: process errno
        return false;
    }

    return true;
}

/**
 * @brief write a block of the file
 *
 * @return true, if successful, else false
 */
bool
BinaryFileDirect::writeSegment(DataBuffer &buffer,
                               const uint64_t startBlockInFile,
                               const uint64_t numberOfBlocks,
                               const uint64_t startBlockInBuffer)
{
    // prepare blocksize for mode
    const uint16_t blockSize = buffer.blockSize;
    const uint64_t numberOfBytes = numberOfBlocks * blockSize;
    const uint64_t startBytesInFile = startBlockInFile * blockSize;
    const uint64_t startBytesInBuffer = startBlockInBuffer * blockSize;

    // precheck
    if(numberOfBlocks == 0
            || startBytesInFile + numberOfBytes > m_totalFileSize
            || startBytesInBuffer + numberOfBytes > buffer.numberOfBlocks * buffer.blockSize
            || m_fileDescriptor < 0)
    {
        return false;
    }

    // go to the requested position and write the block
    const long retSeek = lseek(m_fileDescriptor,
                               static_cast<long>(startBytesInFile),
                               SEEK_SET);
    if(retSeek < 0) {
        return false;
    }

    // write data to file
    const ssize_t ret = write(m_fileDescriptor,
                              static_cast<uint8_t*>(buffer.data) + startBytesInBuffer,
                              numberOfBytes);

    if(ret == -1)
    {
        // TODO: process errno
        return false;
    }

    // sync file
    fdatasync(m_fileDescriptor);

    return true;
}

/**
 * @brief close the cluser-file
 *
 * @return true, if file-descriptor is valid, else false
 */
bool
BinaryFileDirect::closeFile()
{
    if(m_fileDescriptor == -1) {
        return false;
    }

    close(m_fileDescriptor);
    m_fileDescriptor = -1;
    return true;
}

} // namespace Kitsunemimi
