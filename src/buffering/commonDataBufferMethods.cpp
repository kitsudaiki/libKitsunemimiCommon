#include <buffering/commonDataBufferMethods.h>

#include <buffering/commonDataBuffer.h>

namespace Kitsune
{

/**
 * @brief CommonDataBuffer::addData
 * @param data
 * @param size
 */
bool
addDataToBuffer(CommonDataBuffer* buffer,
                uint8_t* data,
                const uint64_t size)
{
    if(size == 0 || data == nullptr) {
        return false;
    }
    if(buffer->bufferPosition + size
            >= buffer->numberOfBlocks * buffer->blockSize)
    {
        const uint64_t newBlockNum = (size / buffer->blockSize) + 1;
        allocateBlocks(buffer, newBlockNum);
    }
    memcpy(&buffer->data[buffer->bufferPosition], data, size);
    buffer->bufferPosition += size;
    return true;
}

/**
 * allocate more memory for the buffer
 *
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
    uint8_t* newBuffer =  (uint8_t*)aligned_alloc(buffer->blockSize, newSize * buffer->blockSize);
    if(newBuffer == nullptr) {
        return false;
    }
    memset(newBuffer, 0, newSize * buffer->blockSize);

    // copy the content of the old buffer to the new and deallocate the old
    if(buffer->data != nullptr)
    {
        memcpy(newBuffer, buffer->data, numberOfBlocks * buffer->blockSize);
        free(buffer->data);
    }

    // set the new values
    buffer->numberOfBlocks = newSize;
    buffer->totalBufferSize = newSize * buffer->blockSize;
    buffer->data = newBuffer;

    return true;
}

/**
 * @brief resetBuffer
 * @param buffer
 * @return
 */
bool
resetBuffer(CommonDataBuffer *buffer)
{
    if(buffer->data == nullptr) {
        return false;
    }
    free(buffer->data);
    buffer->data = (uint8_t*)aligned_alloc(buffer->blockSize, buffer->blockSize);
    memset(buffer->data, 0, buffer->blockSize);
    buffer->bufferPosition = 0;
    buffer->totalBufferSize = buffer->blockSize;
    buffer->numberOfBlocks = 1;
    return true;
}

}
