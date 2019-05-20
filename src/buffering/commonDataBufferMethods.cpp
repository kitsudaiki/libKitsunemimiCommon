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
    if(size == 0 || data == nullptr) {
        return false;
    }

    // check buffer-size and allocate more memory if necessary
    if(buffer->bufferPosition + size
            >= buffer->numberOfBlocks * buffer->blockSize)
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
    uint8_t* newBuffer =  static_cast<uint8_t*>(aligned_alloc(buffer->blockSize,
                                                              newSize * buffer->blockSize));

    // prepare new allocated memory
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
 * reset a buffer and clears the data, so it is like the buffer is totally new
 *
 * @param buffer pointer to buffer-object
 */
void
resetBuffer(CommonDataBuffer *buffer)
{
    // deallocate ald buffer if possible
    if(buffer->data != nullptr) {
        free(buffer->data);
    }

    // allocate one single block as new buffer-data
    buffer->data = static_cast<uint8_t*>(aligned_alloc(buffer->blockSize,
                                                       buffer->blockSize));
    memset(buffer->data, 0, buffer->blockSize);

    // reset metadata of the buffer
    buffer->bufferPosition = 0;
    buffer->totalBufferSize = buffer->blockSize;
    buffer->numberOfBlocks = 1;
}

}
