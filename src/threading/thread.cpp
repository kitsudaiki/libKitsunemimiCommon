/**
 *  @file    thread.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <threading/thread.hpp>
#include <buffering/dataBuffer.hpp>

namespace Kitsune
{
namespace Common
{

/**
 * constructor
 */
Thread::Thread(int coreId)
{
    m_coreId = coreId;
}

/**
 * destructor
 */
Thread::~Thread()
{
    stop();
}

/**
 * bind the thread to a specific cpu-thread
 *
 * @param coreId id of the cpu-thread where bind
 *
 * @return false if precheck of bind failed, else true
 */
bool
Thread::bindThreadToCore(const int coreId)
{
    // precheck
    // TODO: get max-core-number of the system
    int num_cores = 4;
    if(coreId < 0
            || coreId >= num_cores)
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
 * start the thread
 *
 * @return false if already running, else true
 */
bool
Thread::start()
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

/**
 * wait until the thread has finished its task
 *
 * @return false if not actire or not joinable, else true
 */
bool
Thread::waitForFinish()
{
    // TODO: check that the thread doesn't typ to stop itself,
    //       because it results into a deadlock

    // precheck
    if(m_active == false) {
        return false;
    }

    //
    if(m_thread->joinable()) {
        m_thread->join();
    } else {
        return false;
    }

    return true;
}

/**
 * stop a thread without killing the thread
 */
void
Thread::stop()
{
    // TODO: check that the thread doesn't typ to stop itself,
    //       because it results into a deadlock

    // precheck
    if(m_active == false) {
        return;
    }

    // give thread abort-flag and wait until its end
    m_abort = true;
    waitForFinish();
    m_active = false;
}


/**
 * say the thread, he should wait at the next barrier
 */
void
Thread::initBlockThread()
{
    m_block = true;
}

/**
 * lets the thread continue if he waits at the barrier
 */
void
Thread::continueThread()
{
    m_cv.notify_one();
}

/**
 * simple mutex-lock
 */
void
Thread::mutexLock()
{
    m_mutex.lock();
}

/**
 * simple mutex-unlock
 */
void
Thread::mutexUnlock()
{
    m_mutex.unlock();
}

/**
 * lets the thread wait at a barrier
 */
void
Thread::blockThread()
{
    m_block = false;
    std::unique_lock<std::mutex> lock(m_cvMutex);
    m_cv.wait(lock);
    m_block = false;
}

/**
 * lets the thread sleep for a specific amount of microseconds
 */
void
Thread::sleepThread(const uint32_t microSeconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microSeconds));
}

/**
 * check if thread is active
 *
 * @return true, if active, else false
 */
bool
Thread::isActive() const
{
    return m_active;
}

} // namespace Common
} // namespace Kitsune
