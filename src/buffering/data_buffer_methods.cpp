/**
 *  @file       data_buffer_methods.cpp
 *
 *  @brief      Methods for the data-buffer.
 *
 *  @details    Besause I don't wanted to press all the methods into the data-buffer struct-object
 *              I separated these into this file without class. It for memory allocation and delete
 *              in data-buffers.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsuneCommon/buffering/data_buffer_methods.h>
#include <libKitsuneCommon/buffering/data_buffer.h>

namespace Kitsune
{
namespace Common
{

/**
 * @brief copy data into the buffer and resize the buffer in necessary
 *
 * @param buffer pointer to buffer-object
 * @param data pointer the the data, which should be written into the buffer
 * @param dataSize number of bytes to write
 *
 * @return false if precheck or allocation failed, else true
 */
bool
addDataToBuffer(DataBuffer* buffer,
                const void* data,
                const uint64_t dataSize)
{
    // precheck
    if(dataSize == 0
            || data == nullptr
            || buffer->bufferPosition + dataSize > buffer->totalBufferSize)
    {
        return false;
    }

    // check buffer-size and allocate more memory if necessary
    if(buffer->bufferPosition + dataSize >= buffer->numberOfBlocks * buffer->blockSize)
    {
        const uint64_t newBlockNum = (dataSize / buffer->blockSize) + 1;
        if(allocateBlocks(buffer, newBlockNum) == false) {
            return false;
        }
    }

    // copy the new data into the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(buffer->data);
    memcpy(&dataByte[buffer->bufferPosition], data, dataSize);
    buffer->bufferPosition += dataSize;

    return true;
}

/**
 * @brief allocate more memory for the buffer.
 *        It allocates a bigger memory-block an copy the old buffer-content into the new.
 *
 * @param buffer pointer to buffer-object
 * @param numberOfBlocks number of blocks to allocate
 *
 * @return true, if successful, else false
 */
bool
allocateBlocks(DataBuffer* buffer,
               const uint64_t numberOfBlocks)
{
    // precheck
    if(numberOfBlocks == 0) {
        return true;
    }

    // create the new buffer
    uint64_t newSize = numberOfBlocks + buffer->numberOfBlocks;
    void* newBuffer =  alignedMalloc(buffer->blockSize,
                                     newSize * buffer->blockSize);
    if(newBuffer == nullptr) {
        return false;
    }

    // copy the content of the old buffer to the new and deallocate the old
    if(buffer->data != nullptr
            && buffer->inUse == 1)
    {
        memcpy(newBuffer, buffer->data, numberOfBlocks * buffer->blockSize);
        alignedFree(buffer->data);
    }

    // set the new values
    buffer->inUse = 1;
    buffer->numberOfBlocks = newSize;
    buffer->totalBufferSize = newSize * buffer->blockSize;
    buffer->data = newBuffer;

    return true;
}

/**
 * @brief reset a buffer and clears the data, so it is like the buffer is totally new
 *
 * @param buffer pointer to buffer-object
 * @param numberOfBlocks number of new allocated blocks after buffer-reset
 *
 * @return false if precheck or allocation failed, else true
 */
bool
resetBuffer(DataBuffer* buffer,
            const uint64_t numberOfBlocks)
{
    // precheck
    if(buffer == nullptr
            || numberOfBlocks == 0)
    {
        return false;
    }

    // deallocate ald buffer if possible
    if(buffer->data != nullptr
            && buffer->inUse == 1)
    {
        alignedFree(buffer->data);
    }

    // allocate at least one single block as new buffer-data
    void* newBuffer = alignedMalloc(buffer->blockSize,
                                    numberOfBlocks * buffer->blockSize);
    if(newBuffer == nullptr) {
        return false;
    }

    // reset metadata of the buffer
    buffer->inUse = 1;
    buffer->bufferPosition = 0;
    buffer->totalBufferSize = numberOfBlocks * buffer->blockSize;
    buffer->numberOfBlocks = numberOfBlocks;

    return true;
}


/**
 * @brief allocate a number of aligned bytes
 *
 * @param blockSize size of a single block for alignment. MUST be a multiple of 512.
 * @param numberOfBytes bytes to allocate
 *
 * @return pointer to the allocated memory or nullptr if blocksize is not a multiple of 512
 *         or allocation failed
 */
void*
alignedMalloc(const uint16_t blockSize,
              const uint64_t numberOfBytes)
{
    // precheck
    // have to be a multiple of 512 to be able for direct write operations in
    // the persistence library
    if(blockSize % 512 != 0) {
        return nullptr;
    }

    // allocate new memory
    void* ptr = nullptr;
    const int ret = posix_memalign(&ptr, blockSize, numberOfBytes);
    if(ret != 0) {
        return nullptr;
    }

    // init memory
    memset(ptr, 0, numberOfBytes);

    return ptr;
}

/**
 * @brief free aligned memory
 *        this method is a bit useless, but I wanted a equivalent for the alignedMalloc-method
 *
 * @param  ptr pointer to the memory to free
 *
 * @return true, if pointer not nullptr, else false
 */
bool
alignedFree(void* ptr)
{
    // precheck
    if(ptr == nullptr) {
        return false;
    }

    // free data
    free(ptr);

    return true;
}

} // namespace Common
} // namespace Kitsune
