/**
 *  @file    ring_buffer.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cinttypes>
#include <string.h>
#include <libKitsunemimiCommon/buffer/data_buffer.h>

namespace Kitsunemimi
{

#define RING_BUFFER_SIZE 16*1024*1024


struct RingBuffer
{
    uint8_t* data = static_cast<uint8_t*>(alignedMalloc(4096, RING_BUFFER_SIZE));
    uint64_t totalBufferSize = RING_BUFFER_SIZE;
    uint64_t readPosition = 0;
    uint64_t usedSize = 0;

    // backup-buffer to collect messages, which are splitted
    // in the data-object
    uint8_t* overflowBuffer = static_cast<uint8_t*>(alignedMalloc(4096, RING_BUFFER_SIZE));

    /**
     * @brief constructor
     */
    RingBuffer() {}

    /**
     * @brief destructor
     */
    ~RingBuffer()
    {
        delete data;
        delete overflowBuffer;
    }
};

/**
 * @brief getWritePosition
 *
 * @param ringBuffer reference to ringbuffer-object
 *
 * @return
 */
inline uint64_t
getWritePosition(RingBuffer &ringBuffer)
{
    return (ringBuffer.readPosition + ringBuffer.usedSize) % ringBuffer.totalBufferSize;
}

/**
 * @brief getSpaceToEnd
 *
 * @param ringBuffer
 *
 * @return
 */
inline uint64_t
getSpaceToEnd(RingBuffer &ringBuffer)
{
    const uint64_t writePosition = getWritePosition(ringBuffer);

    uint64_t spaceToEnd = ringBuffer.totalBufferSize - writePosition;
    if(writePosition < ringBuffer.readPosition) {
        spaceToEnd = ringBuffer.readPosition - writePosition;
    }

    return spaceToEnd;
}

/**
 * @brief write data into the ring-buffer
 *
 * @param ringBuffer reference to ringbuffer-object
 * @param data pointer to the new data
 * @param dataSize size of the new data
 *
 * @return false, if data are bigger than the available space inside the buffer, else true
 */
inline bool
addDataToBuffer(RingBuffer &ringBuffer,
                const void* data,
                const uint64_t dataSize)
{
    if(dataSize + ringBuffer.usedSize > ringBuffer.totalBufferSize) {
        return false;
    }

    const uint64_t writePosition = getWritePosition(ringBuffer);
    const uint64_t spaceToEnd = getSpaceToEnd(ringBuffer);

    if(dataSize <= spaceToEnd)
    {
        memcpy(&ringBuffer.data[writePosition], data, dataSize);
    }
    else
    {
        const uint64_t remaining = dataSize - spaceToEnd;
        const uint8_t* dataPos = static_cast<const uint8_t*>(data);

        memcpy(&ringBuffer.data[writePosition], &dataPos[0], spaceToEnd);
        memcpy(&ringBuffer.data[0], &dataPos[spaceToEnd], remaining);
    }

    ringBuffer.usedSize += dataSize;

    return true;
}

/**
 * @brief add an object to the buffer
 *
 * @param ringBuffer reference to ringbuffer-object
 * @param data pointer to the object, which shoulb be written to the buffer
 *
 * @return false if precheck or allocation failed, else true
 */
template <typename T>
inline bool
addObjectToBuffer(RingBuffer &ringBuffer, T* data)
{
    return addDataToBuffer(ringBuffer, data, sizeof(T));
}

/**
 * get a pointer to the complete monolitic block of the ring-buffer
 *
 * @param ringBuffer reference to ringbuffer-object
 * @param size size of the requested block
 *
 * @return pointer to the beginning of the requested datablock, or nullptr if the requested
 *         block is too big
 */
inline const uint8_t*
getDataPointer(RingBuffer &ringBuffer,
               const uint64_t size)
{
    if(ringBuffer.usedSize < size) {
        return nullptr;
    }

    const uint64_t startPosition = ringBuffer.readPosition % ringBuffer.totalBufferSize;

    // check if requested datablock is splitet
    if(startPosition + size > ringBuffer.totalBufferSize)
    {
        // copy the two parts of the requested block into the overflow-buffer
        const uint64_t firstPart = size - ((startPosition + size) % ringBuffer.totalBufferSize);
        memcpy(&ringBuffer.overflowBuffer[0], &ringBuffer.data[startPosition], firstPart);
        memcpy(&ringBuffer.overflowBuffer[firstPart], &ringBuffer.data[0], size - firstPart);
        return &ringBuffer.overflowBuffer[0];
    }

    return &ringBuffer.data[startPosition];
}

/**
 * @brief moveBufferForward
 *
 * @param ringBuffer reference to ringbuffer-object
 * @param numberOfBytes
 */
inline void
moveBufferForward(RingBuffer &ringBuffer,
                  const uint64_t numberOfBytes)
{
    ringBuffer.readPosition = (ringBuffer.readPosition + numberOfBytes)
                               % ringBuffer.totalBufferSize;
    ringBuffer.usedSize -= numberOfBytes;
}

/**
 * @brief getObjectFromBuffer
 *
 * @param ringBuffer reference to ringbuffer-object
 *
 * @return
 */
template <typename T>
inline const T*
getObjectFromBuffer(RingBuffer &ringBuffer)
{
    const void* data = static_cast<const void*>(getDataPointer(ringBuffer, sizeof(T)));

    return static_cast<const T*>(data);
}

} // namespace Kitsunemimi

#endif // RING_BUFFER_H
