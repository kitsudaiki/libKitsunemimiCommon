#include <buffering/commonDataBufferMethods.h>

#include <buffering/commonDataBuffer.h>

namespace Kitsune
{

/**
 * @brief CommonDataBuffer::addData
 * @param data
 * @param size
 */
void
addDataToBuffer(CommonDataBuffer* buffer,
                uint8_t* data,
                const uint64_t size)
{
    if(buffer->numberOfWrittenBytes + size
            >= buffer->numberOfBlocks * buffer->blockSize)
    {
        const uint32_t newBlockNum = (size / buffer->blockSize) + 1;
        allocateBlocks(buffer, newBlockNum);
    }
    memcpy((uint8_t*)buffer + buffer->numberOfWrittenBytes, data, size);
    buffer->numberOfWrittenBytes += size;
}

/**
 * allocate more memory for the buffer
 *
 * @param numberOfBlocks number of blocks to allocate
 * @return true, if successful, else false
 */
bool
allocateBlocks(CommonDataBuffer* buffer, const uint32_t numberOfBlocks)
{
    if(numberOfBlocks == 0) {
        return true;
    }

    // create the new buffer
    uint32_t newSize = numberOfBlocks + numberOfBlocks;
    uint8_t* newBuffer = aligned_malloc(newSize, buffer->blockSize);
    memset(newBuffer, 0, newSize * buffer->blockSize);

    // copy the content of the old buffer to the new and deallocate the old
    if(buffer != nullptr)
    {
        memcpy(newBuffer, buffer, numberOfBlocks * buffer->blockSize);
        aligned_free(buffer->data);
    }

    // set the new values
    buffer->numberOfBlocks = newSize;
    buffer->data = newBuffer;

    return true;
}

/**
 * @brief CommonDataBuffer::resetBuffer
 */
void
resetBuffer(CommonDataBuffer *buffer)
{
    aligned_free(buffer->data);
    buffer->data = aligned_malloc(1, buffer->blockSize);
    buffer->numberOfWrittenBytes = 0;
    buffer->numberOfBlocks = 1;
}

/**
 * allocate a number of aligned bytes
 *
 * @param numberOfBytes bytes to allocate
 * @return pointer to the allocated memory
 */
uint8_t*
aligned_malloc(const uint32_t numberOfBlocks,
               const uint32_t blockSize)
{
    uint32_t numberOfBytes = numberOfBlocks * blockSize;
    void *mem = malloc(numberOfBytes+blockSize+sizeof(void*));
    void **ptr = (void**)((uintptr_t)((uint8_t*)mem+blockSize+sizeof(void*)) & ~(blockSize-1));
    ptr[-1] = mem;
    memset(ptr, 0, numberOfBytes);
    return (uint8_t*)ptr;
}

/**
 * aligned_free to free aligned memory
 *
 * @param ptr pointer to the memory to free
 * @return true, if pointer not nullptr, else false
 */
bool
aligned_free(uint8_t *ptr)
{
    if(ptr != nullptr)
    {
        free(((void**)ptr)[-1]);
        ptr = nullptr;
        return true;
    }
    return false;
}

}
