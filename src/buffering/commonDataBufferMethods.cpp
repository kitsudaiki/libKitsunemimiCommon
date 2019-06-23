#include <buffering/commonDataBufferMethods.h>

#include <buffering/commonDataBuffer.h>

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
                const uint8_t* data,
                const uint64_t size)
{
    if(size == 0 || data == nullptr
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
    memcpy(&buffer->data[buffer->bufferPosition], data, size);
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
allocateBlocks(CommonDataBuffer* buffer, const uint64_t numberOfBlocks)
{
    if(numberOfBlocks == 0) {
        return true;
    }

    // create the new buffer
    uint64_t newSize = numberOfBlocks + buffer->numberOfBlocks;
    uint8_t* newBuffer =  static_cast<uint8_t*>(alignedMalloc(buffer->blockSize,
                                                              newSize * buffer->blockSize));

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
resetBuffer(CommonDataBuffer *buffer,
            const uint32_t numberOfBlocks)
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
              const uint32_t numberOfBytes)
{
    void *mem = malloc(numberOfBytes+blockSize+sizeof(void*));
    void **ptr = (void**)((uintptr_t)((uint8_t*)mem+blockSize+sizeof(void*)) & ~(blockSize-1));
    ptr[-1] = mem;
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
alignedFree(void *ptr)
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
