#ifndef BLOCK_BUFFER_RESERVE_H
#define BLOCK_BUFFER_RESERVE_H

#include <iostream>
#include <atomic>
#include <vector>
#include <libKitsunemimiCommon/buffer/data_buffer.h>

#define MAX_RESERVE_SIZE 100
#define BLOCK_BUFFER_BLOCK_SIZE 128*1024

namespace Kitsunemimi
{

class BlockBufferReserve
{
public:
    BlockBufferReserve();
    ~BlockBufferReserve();

    DataBuffer* getBlock();
    void addBlock(DataBuffer* buffer);

private:
    std::vector<DataBuffer*> m_reserve;
    std::atomic_flag m_lock = ATOMIC_FLAG_INIT;
};

}

#endif // BLOCK_BUFFER_RESERVE_H
