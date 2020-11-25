/**
 *  @file       thread.cpp
 *
 *  @brief      Common Thead-class.
 *
 *  @details    This class is only a collection of some thread-function like blocking and so on
 *              which I often use. This makes the creation of threads more easy for me. Additionally
 *              this class provides the ability to bind a new one of this thread to a specific
 *              cpu-thread.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/threading/thread.h>
#include <libKitsunemimiCommon/threading/event.h>
#include <libKitsunemimiCommon/buffer/data_buffer.h>
#include <libKitsunemimiCommon/threading/thread_handler.h>
#include <libKitsunemimiCommon/threading/cleanup_thread.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 */
Thread::Thread(int coreId)
{
    m_coreId = coreId;

    ThreadHandler::getInstance()->registerThread(this);
}

/**
 * @brief destructor
 */
Thread::~Thread()
{
    ThreadHandler::getInstance()->unregisterThread();
    stopThread();
}

/**
 * @brief bind the thread to a specific cpu-thread
 *
 * @param coreId id of the cpu-thread where bind
 *
 * @return false if precheck of bind failed, else true
 */
bool
Thread::bindThreadToCore(const int coreId)
{
    // precheck
    uint32_t num_cores = std::thread::hardware_concurrency();;
    if(coreId < 0
            || static_cast<uint32_t>(coreId) >= num_cores)
    {
        return false;
    }

    // bind thread
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(coreId, &cpuset);
    const int ret = pthread_setaffinity_np(m_thread->native_handle(),
                                           sizeof(cpu_set_t),
                                           &cpuset);

    if(ret != 0) {
        return false;
    }
    return true;
}

/**
 * @brief add a new event to the queue
 * @param newEvent new event
 */
void
Thread::addEventToQueue(Event* newEvent)
{
    while(m_eventQueue_lock.test_and_set(std::memory_order_acquire)) { asm(""); }
    m_eventQueue.push_back(newEvent);
    m_eventQueue_lock.clear(std::memory_order_release);

}

/**
 * @brief get the next event from the queue
 *
 * @return nullptr, if the queue is empty, else the next event of the queue
 */
Event*
Thread::getEventFromQueue()
{
    Event* result = nullptr;

    while(m_eventQueue_lock.test_and_set(std::memory_order_acquire)) { asm(""); }

    // get the next from the queue
    if(m_eventQueue.empty() == false)
    {
        result = m_eventQueue.front();
        m_eventQueue.pop_front();
    }

    m_eventQueue_lock.clear(std::memory_order_release);

    return result;

}

/**
 * @brief start the thread
 *
 * @return false if already running, else true
 */
bool
Thread::startThread()
{
    // precheck
    if(m_active) {
        return false;
    }

    // init new thread
    m_abort = false;
    m_thread = new std::thread(&Thread::run, this);
    m_active = true;

    // bind thread to cpu-thread, if required
    if(m_coreId >= 0) {
        bindThreadToCore(m_coreId);
    }

    return true;
}

bool
Thread::scheduleThreadForDeletion()
{
    if(m_scheduledForDeletion) {
        return false;
    }

    m_scheduledForDeletion = true;
    CleanupThread::getInstance()->addThreadForCleanup(this);

    return true;
}

/**
 * @brief stop a thread without killing the thread
 */
void
Thread::stopThread()
{
    // precheck
    if(m_active == false) {
        return;
    }

    // give thread abort-flag and wait until its end
    m_abort = true;

    if(m_thread->joinable()) {
        m_thread->join();
    }

    m_active = false;
}

/**
 * @brief say the thread, he should wait at the next barrier
 */
void
Thread::initBlockThread()
{
    m_block = true;
}

/**
 * @brief let the thread continue if he waits at the barrier
 */
void
Thread::continueThread()
{
    m_cv.notify_one();
}

/**
 * @brief simple mutex-lock
 */
void
Thread::mutexLock()
{
    m_mutex.lock();
}

/**
 * @brief simple mutex-unlock
 */
void
Thread::mutexUnlock()
{
    m_mutex.unlock();
}

/**
 * @brief spin-lock
 */
void
Thread::spinLock()
{
    while (m_spin_lock.test_and_set(std::memory_order_acquire))
    {
        asm("");
        /**
         * Explaination from stack overflow:
         *
         * What's more, if you use volatile, gcc will store those variables in RAM and add a bunch
         * of ldd and std to copy them to temporary registers.
         * This approach, on the other hand, doesn't use volatile and generates no such overhead.
         */
    }
}

/**
 * @brief spin-unlock
 */
void
Thread::spinUnlock()
{
    m_spin_lock.clear(std::memory_order_release);
}

/**
 * @brief let the thread wait at a barrier
 */
void
Thread::blockThread()
{
    m_block = true;
    std::unique_lock<std::mutex> lock(m_cvMutex);
    m_cv.wait(lock);
    m_block = false;
}

/**
 * @brief let the thread sleep for a specific amount of microseconds
 */
void
Thread::sleepThread(const uint32_t microSeconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microSeconds));
}

/**
 * @brief check if thread is active
 *
 * @return true, if active, else false
 */
bool
Thread::isActive() const
{
    return m_active;
}

} // namespace Kitsunemimi
