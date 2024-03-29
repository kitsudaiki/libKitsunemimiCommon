/**
 *  @file       stack_buffer_reserve.h
 *
 *  @brief      Reserve for stack-buffer to avoid unnecessary memory-allocations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef STACK_BUFFER_RESERVE_H
#define STACK_BUFFER_RESERVE_H

#include <iostream>
#include <atomic>
#include <vector>
#include <libKitsunemimiCommon/buffer/data_buffer.h>

#define STACK_BUFFER_BLOCK_SIZE 256*1024

namespace Kitsunemimi
{
class StackBufferReserve_Test;

class StackBufferReserve
{
public:
    static StackBufferReserve* getInstance();

    bool addBuffer(DataBuffer* buffer);
    uint64_t getNumberOfBuffers();
    DataBuffer* getBuffer();

private:
    StackBufferReserve(const uint32_t reserveSize = 100);
    ~StackBufferReserve();

    uint32_t m_reserveSize = 0;
    std::vector<DataBuffer*> m_reserve;
    std::atomic_flag m_lock = ATOMIC_FLAG_INIT;

    static StackBufferReserve* m_stackBufferReserve;
    friend StackBufferReserve_Test;
};

}

#endif // STACK_BUFFER_RESERVE_H
