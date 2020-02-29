/**
 *  @file    message_ring_buffer.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef MESSAGE_RING_BUFFER_H
#define MESSAGE_RING_BUFFER_H

#include <cinttypes>
#include <string.h>
#include <libKitsunemimiCommon/buffer/data_buffer.h>

namespace Kitsunemimi
{
namespace Network
{

#define RING_BUFFER_SIZE 16*1024*1024


struct MessageRingBuffer
{
    uint8_t* data = static_cast<uint8_t*>(alignedMalloc(4096, RING_BUFFER_SIZE));
    uint64_t totalBufferSize = RING_BUFFER_SIZE;
    uint64_t readPosition = 0;
    uint64_t readWriteDiff = 0;

    // backup-buffer to collect messages, which are splitted
    // in the data-object
    uint8_t* overflowBuffer = static_cast<uint8_t*>(alignedMalloc(4096, RING_BUFFER_SIZE));

    MessageRingBuffer() {}

    ~MessageRingBuffer()
    {
        delete data;
        delete overflowBuffer;
    }
};

/**
 * @brief getWritePosition
 * @param recvBuffer
 * @return
 */
uint64_t
getWritePosition(MessageRingBuffer &recvBuffer)
{
    return (recvBuffer.readPosition + recvBuffer.readWriteDiff) % recvBuffer.totalBufferSize;
}

/**
 * @brief getSpaceToEnd
 * @param recvBuffer
 * @return
 */
uint64_t
getSpaceToEnd(MessageRingBuffer &recvBuffer)
{
    const uint64_t writePosition = getWritePosition(recvBuffer);

    uint64_t spaceToEnd = recvBuffer.totalBufferSize - writePosition;
    if(writePosition < recvBuffer.readPosition) {
        spaceToEnd = recvBuffer.readPosition - writePosition;
    }

    return spaceToEnd;
}

/**
 * @brief write data into the ring-buffer
 *
 * @param recvBuffer ring-buffer-object with the complete data
 * @param data pointer to the new data
 * @param dataSize size of the new data
 *
 * @return false, if data are bigger than the available space inside the buffer, else true
 */
inline bool
addDataToBuffer(MessageRingBuffer &recvBuffer,
                const void* data,
                const uint64_t dataSize)
{
    if(dataSize + recvBuffer.readWriteDiff > recvBuffer.totalBufferSize) {
        return false;
    }

    const uint64_t writePosition = getWritePosition(recvBuffer);
    const uint64_t spaceToEnd = getSpaceToEnd(recvBuffer);

    if(dataSize <= spaceToEnd)
    {
        memcpy(&recvBuffer.data[writePosition], data, dataSize);
    }
    else
    {
        const uint64_t remaining = dataSize - spaceToEnd;
        const uint8_t* dataPos = static_cast<const uint8_t*>(data);

        memcpy(&recvBuffer.data[writePosition], &dataPos[0], spaceToEnd);
        memcpy(&recvBuffer.data[0], &dataPos[spaceToEnd], remaining);
    }

    return true;
}

/**
 * get a pointer to the complete monolitic block of the ring-buffer
 *
 * @param recvBuffer ring-buffer-object with the complete data
 * @param size size of the requested block
 *
 * @return pointer to the beginning of the requested datablock, or nullptr if the requested
 *         block is too big
 */
inline const uint8_t*
getDataPointer(MessageRingBuffer &recvBuffer,
               const uint64_t size)
{
    if(recvBuffer.readWriteDiff < size) {
        return nullptr;
    }

    const uint64_t startPosition = recvBuffer.readPosition % recvBuffer.totalBufferSize;

    // check if requested datablock is splitet
    if(startPosition + size > recvBuffer.totalBufferSize)
    {
        // copy the two parts of the requested block into the overflow-buffer
        const uint64_t firstPart = size - ((startPosition + size) % recvBuffer.totalBufferSize);
        memcpy(&recvBuffer.overflowBuffer[0], &recvBuffer.data[startPosition], firstPart);
        memcpy(&recvBuffer.overflowBuffer[firstPart], &recvBuffer.data[0], size - firstPart);
        return &recvBuffer.overflowBuffer[0];
    }

    return &recvBuffer.data[startPosition];
}

/**
 * @brief moveBufferForward
 *
 * @param recvBuffer
 *
 * @param numberOfBytes
 */
inline void
moveBufferForward(MessageRingBuffer &recvBuffer,
                  const uint64_t numberOfBytes)
{
    recvBuffer.readPosition = (recvBuffer.readPosition + numberOfBytes)
                               % recvBuffer.totalBufferSize;
    recvBuffer.readWriteDiff -= numberOfBytes;
}

/**
 * @brief getObjectFromBuffer
 *
 * @param recvBuffer
 *
 * @return
 */
template <typename T>
inline const T*
getObjectFromBuffer(MessageRingBuffer* recvBuffer)
{
    const void* data = static_cast<const void*>(getDataPointer(*recvBuffer, sizeof(T)));

    return static_cast<const T*>(data);
}

} // namespace Network
} // namespace Kitsunemimi

#endif // MESSAGE_RING_BUFFER_H
