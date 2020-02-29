#include <libKitsunemimiCommon/buffer/block_buffer_reserve.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 */
BlockBufferReserve::BlockBufferReserve()
{
    assert(BLOCK_BUFFER_BLOCK_SIZE % 4096 == 0);
}

/**
 * @brief destructor
 */
BlockBufferReserve::~BlockBufferReserve()
{
    while (m_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    for(uint64_t i = 0; i < m_reserve.size(); i++)
    {
        DataBuffer* temp = m_reserve.at(i);
        delete temp;
    }

    m_lock.clear(std::memory_order_release);
}

/**
 * @brief BlockBufferReserve::getBlock
 * @return
 */
DataBuffer*
BlockBufferReserve::getBlock()
{
    while (m_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    if(m_reserve.size() == 0)
    {
        m_lock.clear(std::memory_order_release);
        return new DataBuffer(BLOCK_BUFFER_BLOCK_SIZE/4096, 4096);
    }

    DataBuffer* result = m_reserve.back();
    m_reserve.pop_back();
    m_lock.clear(std::memory_order_release);

    return result;
}

/**
 * @brief BlockBufferReserve::addBlock
 * @param buffer
 */
void
BlockBufferReserve::addBlock(DataBuffer* buffer)
{
    while (m_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    if(m_reserve.size() >= MAX_RESERVE_SIZE)
    {
        delete buffer;
    }
    else
    {
        buffer->bufferPosition = 0;
        m_reserve.push_back(buffer);
    }

    m_lock.clear(std::memory_order_release);
}

}
