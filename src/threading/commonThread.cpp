/**
 *  @file    commonThread.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <threading/commonThread.hpp>
#include <buffering/commonDataBuffer.hpp>

namespace Kitsune
{

/**
 * constructor
 */
CommonThread::CommonThread(int coreId)
{
    m_coreId = coreId;
}

/**
 * destructor
 */
CommonThread::~CommonThread()
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
CommonThread::bindThreadToCore(const int coreId)
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
CommonThread::start()
{
    // precheck
    if(m_active) {
        return false;
    }

    // init new thread
    m_abort = false;
    m_thread = new std::thread(&CommonThread::run, this);
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
CommonThread::waitForFinish()
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
CommonThread::stop()
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
CommonThread::initBlockThread()
{
    m_block = true;
}

/**
 * lets the thread continue if he waits at the barrier
 */
void
CommonThread::continueThread()
{
    m_cv.notify_one();
}

/**
 * simple mutex-lock
 */
void
CommonThread::mutexLock()
{
    m_mutex.lock();
}

/**
 * simple mutex-unlock
 */
void
CommonThread::mutexUnlock()
{
    m_mutex.unlock();
}

/**
 * lets the thread wait at a barrier
 */
void
CommonThread::blockThread()
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
CommonThread::sleepThread(const uint32_t microSeconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microSeconds));
}

/**
 * check if thread is active
 *
 * @return true, if active, else false
 */
bool
CommonThread::isActive() const
{
    return m_active;
}

} // namespace Kitsune
