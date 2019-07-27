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
 * @brief CommonThread::CommonThread
 */
CommonThread::CommonThread(int coreId)
{
    m_coreId = coreId;
}

/**
 * @brief CommonThread::~CommonThread
 */
CommonThread::~CommonThread()
{
    stop();
}

/**
 * @brief CommonThread::bindThreadToCore
 * @param coreId
 * @return
 */
bool
CommonThread::bindThreadToCore(const int coreId)
{
    // TODO: get max-core-number of the system
    int num_cores = 4;
    if(coreId < 0
            || coreId >= num_cores)
    {
        return false;
    }

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
 * @brief CommonThread::start
 * @return
 */
bool
CommonThread::start()
{
    if(m_active) {
        return false;
    }
    m_abort = false;
    m_thread = new std::thread(&CommonThread::run, this);
    m_active = true;

    if(m_coreId >= 0) {
        bindThreadToCore(m_coreId);
    }

    return true;
}

/**
 * @brief CommonThread::waitForFinish
 * @return
 */
bool
CommonThread::waitForFinish()
{
    if(m_active == false) {
        return false;
    }
    if(m_thread->joinable()) {
        m_thread->join();
    }
    return true;
}

/**
 * @brief CommonThread::stop
 * @return
 */
bool
CommonThread::stop()
{
    // TODO: check that the thread doesn't typ to stop itself,
    //       because it results into a deadlock
    if(m_active == false) {
        return false;
    }
    m_abort = true;
    if(m_thread->joinable()) {
        m_thread->join();
    }
    m_active = false;
    return true;
}

/**
 * @brief CommonThread::continueThread
 */
void
CommonThread::continueThread()
{
    m_cv.notify_one();
}

/**
 * @brief CommonThread::initBlockThread
 */
void
CommonThread::initBlockThread()
{
    m_block = true;
}

/**
 * @brief CommonThread::mutexLock
 */
void
CommonThread::mutexLock()
{
    m_mutex.lock();
}

/**
 * @brief CommonThread::mutexUnlock
 */
void
CommonThread::mutexUnlock()
{
    m_mutex.unlock();
}

/**
 * @brief CommonThread::blockThread
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
 * @brief CommonThread::sleepThread
 */
bool
CommonThread::sleepThread(const uint32_t uSeconds)
{
    // less than 10 milliseconds doesn't make sense
    if(uSeconds < 10) {
        return false;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(uSeconds));
    return true;
}

/**
 * @brief CommonThread::isActive
 * @return
 */
bool
CommonThread::isActive() const
{
    return m_active;
}

}
