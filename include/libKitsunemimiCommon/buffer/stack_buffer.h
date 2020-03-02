
#ifndef BLOCK_BUFFER_H
#define BLOCK_BUFFER_H

#include <stdint.h>
#include <atomic>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>

#include <libKitsunemimiCommon/buffer/data_buffer.h>
#include <libKitsunemimiCommon/buffer/stack_buffer_reserve.h>

namespace Kitsunemimi
{
static Kitsunemimi::StackBufferReserve* m_stackBufferReserve = nullptr;

struct StackBuffer
{
    uint32_t preOffset = 0;
    uint32_t postOffset = 0;
    uint32_t effectiveBlockSize = 0;
    uint32_t blockSize = STACK_BUFFER_BLOCK_SIZE;

    std::deque<DataBuffer*> blocks;

    /**
     * @brief constructor
     *
     * @param preOffset offset at the beginning of the buffer
     * @param postOffset offset at the end of the buffer
     */
    StackBuffer(const uint32_t preOffset=0,
                const uint32_t postOffset=0)
    {
        this->preOffset = preOffset;
        this->postOffset = postOffset;
        this->effectiveBlockSize = blockSize - preOffset - postOffset;

        if(Kitsunemimi::m_stackBufferReserve == nullptr) {
            Kitsunemimi::m_stackBufferReserve = new StackBufferReserve();
        }
    }

    /**
     * @brief destructor
     */
    ~StackBuffer()
    {
        std::deque<DataBuffer*>::iterator it;
        for(it = blocks.begin();
            it != blocks.end();
            it++)
        {
            DataBuffer* temp = *it;
            delete temp;
            //m_stackBufferReserve->addBuffer(temp);
        }
    }
} __attribute__((packed));

/**
 * @brief add new empty buffer on top of the stack-buffer
 *
 * @param stackBuffer reference to stack-buffer-object
 */
inline void
addNewEmptyBuffer(StackBuffer &stackBuffer)
{
    DataBuffer* newBlock = Kitsunemimi::m_stackBufferReserve->getBuffer();
    newBlock->bufferPosition += stackBuffer.preOffset;
    stackBuffer.blocks.push_back(newBlock);
}

/**
 * @brief add data to the buffer
 *
 * @param stackBuffer reference to stack-buffer-object
 * @param data pointer to the data
 * @param dataSize size of the data
 *
 * @return false, if data ore too big, else true
 */
inline bool
writeDataIntoBuffer(StackBuffer &stackBuffer,
                    const void* data,
                    const uint64_t dataSize)
{
    // precheck
    if(dataSize > stackBuffer.effectiveBlockSize) {
        return false;
    }

    DataBuffer* currentBlock = nullptr;

    if(stackBuffer.blocks.size() == 0)
    {
        addNewEmptyBuffer(stackBuffer);
        currentBlock = stackBuffer.blocks.back();
    }
    else
    {
        currentBlock = stackBuffer.blocks.back();
        const uint64_t estimatedSize = currentBlock->bufferPosition
                                       + stackBuffer.postOffset
                                       + dataSize;

        if(estimatedSize > stackBuffer.effectiveBlockSize)
        {
            addNewEmptyBuffer(stackBuffer);
            currentBlock = stackBuffer.blocks.back();
        }
    }

    uint8_t* dataPos = static_cast<uint8_t*>(currentBlock->data);
    memcpy(&dataPos[currentBlock->bufferPosition], data, dataSize);
    currentBlock->bufferPosition += dataSize;

    return true;
}

/**
 * @brief add an object to the buffer
 *
 * @param recvBuffer reference to ringbuffer-object
 * @param data pointer to the object, which shoulb be written to the buffer
 *
 * @return false if precheck or allocation failed, else true
 */
template <typename T>
inline bool
addObjectToBuffer(StackBuffer &stackBuffer, T* data)
{
    return writeDataIntoBuffer(stackBuffer, data, sizeof(T));
}

/**
 * @brief get first element of the stack
 *
 * @param stackBuffer reference to stack-buffer-object
 *
 * @return
 */
inline DataBuffer*
getFirstElement(StackBuffer &stackBuffer)
{
    // precheck
    if(stackBuffer.blocks.size() == 0) {
        return nullptr;
    }

    // get first element of the stack
    DataBuffer* buffer = stackBuffer.blocks.front();

    return buffer;
}

/**
 * @brief moveForward
 * @param stackBuffer reference to stack-buffer-object
 * @return
 */
inline bool
moveForward(StackBuffer &stackBuffer)
{
    // precheck
    if(stackBuffer.blocks.size() == 0) {
        return false;
    }

    // move buffer from the stack into the reserve
    DataBuffer* temp = stackBuffer.blocks.front();
    stackBuffer.blocks.pop_front();
    m_stackBufferReserve->addBuffer(temp);

    return true;
}

} // namespace Kitsunemimi

#endif // BLOCK_BUFFER_H
