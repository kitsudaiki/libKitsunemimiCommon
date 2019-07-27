/**
 *  @file    commonTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <buffering/commonDataBufferMethods.hpp>
#include <buffering/commonDataBuffer.hpp>

namespace Kitsune
{

/**
 * @brief addDataToBuffer
 *
 * @param buffer pointer to buffer-object
 * @param data
 * @param size
 * @return
 */
bool
addDataToBuffer(CommonDataBuffer* buffer,
                const void* data,
                const uint64_t size)
{
    // precheck
    if(size == 0
            || data == nullptr
            || buffer->bufferPosition + size > buffer->totalBufferSize)
    {
        return false;
    }

    // check buffer-size and allocate more memory if necessary
    if(buffer->bufferPosition + size >= buffer->numberOfBlocks * buffer->blockSize)
    {
        const uint64_t newBlockNum = (size / buffer->blockSize) + 1;
        allocateBlocks(buffer, newBlockNum);
    }

    // copy the new data into the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(buffer->data);
    memcpy(&dataByte[buffer->bufferPosition], data, size);
    buffer->bufferPosition += size;

    return true;
}

/**
 * allocate more memory for the buffer.
 * It allocates a bigger memory-block an copy the old buffer-content into the new.
 *
 * @param buffer pointer to buffer-object
 * @param numberOfBlocks number of blocks to allocate
 * @return true, if successful, else false
 */
bool
allocateBlocks(CommonDataBuffer* buffer,
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

    // prepare new allocated memory
    if(newBuffer == nullptr) {
        return false;
    }
    memset(newBuffer, 0, newSize * buffer->blockSize);

    // copy the content of the old buffer to the new and deallocate the old
    if(buffer->data != nullptr && buffer->inUse == 1)
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
 * reset a buffer and clears the data, so it is like the buffer is totally new
 *
 * @param buffer pointer to buffer-object
 * @param numberOfBlocks
 */
void
resetBuffer(CommonDataBuffer* buffer,
            const uint64_t numberOfBlocks)
{
    // deallocate ald buffer if possible
    if(buffer->data != nullptr && buffer->inUse == 1) {
        alignedFree(buffer->data);
    }

    // allocate one single block as new buffer-data
    buffer->data = static_cast<uint8_t*>(alignedMalloc(buffer->blockSize,
                                                       numberOfBlocks * buffer->blockSize));
    memset(buffer->data, 0, buffer->blockSize);

    // reset metadata of the buffer
    buffer->inUse = 1;
    buffer->bufferPosition = 0;
    buffer->totalBufferSize = numberOfBlocks * buffer->blockSize;
    buffer->numberOfBlocks = numberOfBlocks;
}


/**
 * allocate a number of aligned bytes
 *
 * @param numberOfBytes bytes to allocate
 * @return pointer to the allocated memory
 */
void*
alignedMalloc(const uint16_t blockSize,
              const uint64_t numberOfBytes)
{
    // precheck
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
 * free aligned memory
 *
 * @param ptr pointer to the memory to free
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
    ptr = nullptr;

    return true;
}

}
