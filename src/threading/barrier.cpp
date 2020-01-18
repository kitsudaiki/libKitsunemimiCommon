/**
 *  @file       barrier.cpp
 *
 *  @brief      Barrier class
 *
 *  @details    Barrier to synchronize multiple threads. It wait for the defined number of threads
 *              and release all at once.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/threading/barrier.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 *
 * @param numberOfThreads number of threads to wait at the barrier
 */
Barrier::Barrier(const uint32_t numberOfThreads)
{
    m_numberOfThreads = numberOfThreads;
    m_counter = numberOfThreads;
}

/**
 * @brief Hold at the barrier or release all, if the required number of waiting threads not readed
 *        of else release all waiting threads
 */
void
Barrier::triggerBarrier()
{
    while (m_spin_lock.test_and_set(std::memory_order_acquire))  {
        asm("");
    }

    m_counter--;
    if(m_counter == 0)
    {
        m_counter = m_numberOfThreads;
        m_spin_lock.clear(std::memory_order_release);
        m_cond.notify_all();
    }
    else
    {
        m_spin_lock.clear(std::memory_order_release);
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock);
    }

    return;
}

/**
 * @brief release all waiting threads at the barrier, to avoid dead-locks
 */
void
Barrier::releaseAll()
{
    m_cond.notify_all();
}

} // namespace Kitsunemimi
