#include <libKitsunemimiCommon/buffer/stack_buffer_reserve.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 */
StackBufferReserve::StackBufferReserve()
{
    assert(STACK_BUFFER_BLOCK_SIZE % 4096 == 0);
}

/**
 * @brief destructor
 */
StackBufferReserve::~StackBufferReserve()
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
 * @brief StackBufferReserve::addBlock
 * @param buffer
 */
bool
StackBufferReserve::addBuffer(DataBuffer* buffer)
{
    if(buffer == nullptr) {
        return false;
    }

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

    return true;
}

/**
 * @brief StackBufferReserve::getNumberOfStages
 * @return
 */
uint64_t
StackBufferReserve::getNumberOfBuffers()
{
    while (m_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    const uint64_t result = m_reserve.size();
    m_lock.clear(std::memory_order_release);
    return result;
}

/**
 * @brief StackBufferReserve::getBlock
 * @return
 */
DataBuffer*
StackBufferReserve::getBuffer()
{
    while (m_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    if(m_reserve.size() == 0)
    {
        m_lock.clear(std::memory_order_release);
        return new DataBuffer(STACK_BUFFER_BLOCK_SIZE/4096, 4096);
    }

    DataBuffer* result = m_reserve.back();
    m_reserve.pop_back();
    m_lock.clear(std::memory_order_release);

    return result;
}

}
