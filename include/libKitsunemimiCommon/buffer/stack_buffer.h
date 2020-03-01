
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
static Kitsunemimi::StackBufferReserve* m_bufferReserve = nullptr;

struct StackBuffer
{
    uint32_t preOffset = 0;
    uint32_t postOffset = 0;
    uint32_t effectiveBlockSize = 0;
    uint32_t blockSize = BLOCK_BUFFER_BLOCK_SIZE;

    std::deque<DataBuffer*> blocks;

    StackBuffer(const uint32_t preOffset=0,
                const uint32_t postOffset=0)
    {
        this->preOffset = preOffset;
        this->postOffset = postOffset;
        this->effectiveBlockSize = blockSize - preOffset - postOffset;

        if(Kitsunemimi::m_bufferReserve == nullptr) {
            Kitsunemimi::m_bufferReserve = new StackBufferReserve();
        }
    }

    ~StackBuffer()
    {
        std::deque<DataBuffer*>::iterator it;
        for(it = blocks.begin();
            it != blocks.end();
            it++)
        {
            DataBuffer* temp = *it;
            delete temp;
        }
    }
} __attribute__((packed));

/**
 * @brief writeDataIntoBuffer
 * @param blockBuffer
 * @param data
 * @param dataSize
 * @return
 */
inline bool
writeDataIntoBuffer(StackBuffer &blockBuffer,
                    const void* data,
                    const uint64_t dataSize)
{
    if(dataSize > blockBuffer.effectiveBlockSize) {
        return false;
    }

    DataBuffer* currentBlock = blockBuffer.blocks.back();
    const uint64_t estimatedSize = currentBlock->bufferPosition + blockBuffer.postOffset + dataSize;

    if(estimatedSize > blockBuffer.effectiveBlockSize)
    {
        DataBuffer* newBlock = Kitsunemimi::m_bufferReserve->getStage();
        blockBuffer.blocks.push_back(newBlock);
        currentBlock = newBlock;
        currentBlock->bufferPosition += blockBuffer.preOffset;
    }

    uint8_t* dataPos = static_cast<uint8_t*>(currentBlock->data);
    memcpy(&dataPos[currentBlock->bufferPosition], data, dataSize);
    currentBlock->bufferPosition += dataSize;

    return true;
}

/**
 * @brief getFirstBlock
 * @param blockBuffer
 * @return
 */
inline DataBuffer*
getFirstBlock(StackBuffer &blockBuffer)
{
    if(blockBuffer.blocks.size() == 0) {
        return nullptr;
    }

    DataBuffer* buffer = blockBuffer.blocks.front();

    return buffer;
}

/**
 * @brief moveForward
 * @param blockBuffer
 * @return
 */
inline bool
moveForward(StackBuffer &blockBuffer)
{
    if(blockBuffer.blocks.size() == 0) {
        return false;
    }

    DataBuffer* temp = blockBuffer.blocks.front();
    blockBuffer.blocks.pop_front();
    m_bufferReserve->addStage(temp);

    return true;
}

} // namespace Kitsunemimi

#endif // BLOCK_BUFFER_H
