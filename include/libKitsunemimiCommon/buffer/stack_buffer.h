/**
 *  @file       stack_buffer.h
 *
 *  @brief      Stack of multiple data-buffer
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef STACK_BUFFER_H
#define STACK_BUFFER_H

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
    DataBuffer* localReserve = nullptr;
    StackBufferReserve* stackBufferReserve = nullptr;

    /**
     * @brief constructor
     *
     * @param preOffset offset at the beginning of the buffer
     * @param postOffset offset at the end of the buffer
     */
    StackBuffer(const uint32_t preOffset = 0,
                const uint32_t postOffset = 0)
    {
        this->preOffset = preOffset;
        this->postOffset = postOffset;
        this->effectiveBlockSize = blockSize - preOffset - postOffset;

        if(Kitsunemimi::m_stackBufferReserve == nullptr) {
            Kitsunemimi::m_stackBufferReserve = new StackBufferReserve();
        }
        stackBufferReserve = Kitsunemimi::m_stackBufferReserve;
    }

    /**
     * @brief destructor
     */
    ~StackBuffer()
    {
        // add all buffer within the current stack-buffer to the stack-buffer-reserve
        std::deque<DataBuffer*>::iterator it;
        for(it = blocks.begin();
            it != blocks.end();
            it++)
        {
            DataBuffer* temp = *it;
            stackBufferReserve->addBuffer(temp);
        }

        // move local reserve to central stack-buffer-reserve
        if(localReserve != nullptr) {
            stackBufferReserve->addBuffer(localReserve);
        }
    }
};

/**
 * @brief add new empty buffer on top of the stack-buffer
 *
 * @param stackBuffer reference to stack-buffer-object
 */
inline void
extendBuffer_StackBuffer(StackBuffer &stackBuffer)
{
    DataBuffer* newBlock = nullptr;

    // get new buffer from the local reserve or the central stack reserve
    if(stackBuffer.localReserve != nullptr)
    {
        newBlock = stackBuffer.localReserve;
        stackBuffer.localReserve = nullptr;
    }
    else
    {
        newBlock = stackBuffer.stackBufferReserve->getBuffer();
    }

    // set pre-offset inside the new buffer and add it to the new buffer
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
addData_StackBuffer(StackBuffer &stackBuffer,
                    const void* data,
                    const uint64_t dataSize)
{
    // precheck
    if(dataSize > stackBuffer.effectiveBlockSize) {
        return false;
    }
    assert(dataSize <= stackBuffer.effectiveBlockSize);

    DataBuffer* currentBlock = nullptr;

    if(stackBuffer.blocks.size() == 0)
    {
        // init first buffer on the stack
        extendBuffer_StackBuffer(stackBuffer);
        currentBlock = stackBuffer.blocks.back();
    }
    else
    {
        // get current buffer from the stack and calculate estimated size after writing the new data
        currentBlock = stackBuffer.blocks.back();
        const uint64_t estimatedSize = currentBlock->bufferPosition
                                       + stackBuffer.postOffset
                                       + dataSize;

        // if estimated size is to big for the current buffer, add a new empty buffer to the stack
        if(estimatedSize > stackBuffer.effectiveBlockSize)
        {
            extendBuffer_StackBuffer(stackBuffer);
            currentBlock = stackBuffer.blocks.back();
        }
    }

    // write data into buffer
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
addObject_StackBuffer(StackBuffer &stackBuffer, T* data)
{
    return addData_StackBuffer(stackBuffer, data, sizeof(T));
}

/**
 * @brief get first element of the stack
 *
 * @param stackBuffer reference to stack-buffer-object
 *
 * @return pointer to the first buffer of the stack
 */
inline DataBuffer*
getFirstElement_StackBuffer(StackBuffer &stackBuffer)
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
 * @brief remove the first buffer of the stack
 *
 * @param stackBuffer reference to stack-buffer-object
 *
 * @return false, if stack is empty, else true
 */
inline bool
removeFirst_StackBuffer(StackBuffer &stackBuffer)
{
    // precheck
    if(stackBuffer.blocks.size() == 0) {
        return false;
    }

    // move buffer from the stack into the reserve
    DataBuffer* temp = stackBuffer.blocks.front();
    temp->bufferPosition = 0;
    stackBuffer.blocks.pop_front();

    // add to local reserve, if there is no one is set or else add to central stack-buffer-reserve
    if(stackBuffer.localReserve == nullptr) {
        stackBuffer.localReserve = temp;
    } else {
        stackBuffer.stackBufferReserve->addBuffer(temp);
    }

    return true;
}

/**
 * @brief reset stack-buffer
 *
 * @param stackBuffer reference to stack-buffer-object
 */
inline void
reset_StackBuffer(StackBuffer &stackBuffer)
{
    // add all buffer within the current stack-buffer to the stack-buffer-reserve
    std::deque<DataBuffer*>::iterator it;
    for(it = stackBuffer.blocks.begin();
        it != stackBuffer.blocks.end();
        it++)
    {
        DataBuffer* temp = *it;
        temp->bufferPosition = 0;
        *it = nullptr;

        // move local reserve to central stack-buffer-reserve
        if(stackBuffer.localReserve == nullptr) {
            stackBuffer.localReserve = temp;
        } else {
            stackBuffer.stackBufferReserve->addBuffer(temp);
        }
    }

    stackBuffer.blocks.clear();
}

} // namespace Kitsunemimi

#endif // STACK_BUFFER_H
