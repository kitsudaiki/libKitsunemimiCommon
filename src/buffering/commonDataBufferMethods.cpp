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
    if(buffer->bufferPosition + size
            >= buffer->numberOfBlocks * buffer->blockSize)
    {
        const uint32_t newBlockNum = (size / buffer->blockSize) + 1;
        allocateBlocks(buffer, newBlockNum);
    }
    memcpy((uint8_t*)buffer + buffer->bufferPosition, data, size);
    buffer->bufferPosition += size;
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
    uint32_t newSize = numberOfBlocks + buffer->numberOfBlocks;
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
    buffer->data = newBuffer;

    return true;
}

/**
 * @brief CommonDataBuffer::resetBuffer
 */
void
resetBuffer(CommonDataBuffer *buffer)
{
    free(buffer->data);
    buffer->data = (uint8_t*)aligned_alloc(buffer->blockSize, buffer->blockSize);
    buffer->bufferPosition = 0;
    buffer->numberOfBlocks = 1;
}

}
