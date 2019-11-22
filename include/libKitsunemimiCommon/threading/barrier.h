/**
 *  @file       barrier.h
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

#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <pthread.h>
#include <vector>
#include <atomic>

namespace Kitsunemimi
{
namespace Common
{

class Barrier
{
public:
    Barrier(const uint32_t numberOfThreads);

    void triggerBarrier();
    void releaseAll();

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::atomic_flag m_spin_lock = ATOMIC_FLAG_INIT;

    uint32_t m_numberOfThreads = 0;
    uint32_t m_counter = 0;
    bool m_abort = false;
};

} // namespace Common
} // namespace Kitsunemimi

#endif // BARRIER_H
