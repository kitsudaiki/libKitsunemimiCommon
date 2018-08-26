/**
 *  @file    commonThread.cpp
 *  @author  Tobias Anker
 *
 *  @section DESCRIPTION
 *
 *  TODO: Description
 */

#include "commonThread.h"

namespace Kitsune
{

/**
 * @brief CommonThread::CommonThread
 */
CommonThread::CommonThread()
{
}

/**
 * @brief CommonThread::~CommonThread
 */
CommonThread::~CommonThread()
{
    stop();
}

/**
 * @brief CommonThread::start
 * @return
 */
bool CommonThread::start()
{
    if(m_active) {
        return false;
    }
    m_abort = false;
    m_thread = new std::thread(&CommonThread::run, this);

    /*if(m_coreId != 0xFFFFFFFF)
    {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(m_coreId, &cpuset);

        //pthread_attr_setaffinity_np(m_thread->native_handle(), sizeof(cpu_set_t), &cpuset);
    }*/
    return true;
}

/**
 * @brief CommonThread::stop
 * @return
 */
bool CommonThread::stop()
{
    if(!m_active) {
        return false;
    }
    m_abort = true;
    m_thread->join();
    return true;
}

/**
 * @brief CommonThread::continueThread
 */
void CommonThread::continueThread()
{
    m_cv.notify_one();
}

/**
 * @brief CommonThread::initBlockThread
 */
void CommonThread::initBlockThread()
{
    m_block = true;
}

/**
 * @brief CommonThread::mutexLock
 */
void CommonThread::mutexLock()
{
    m_mutex.lock();
}

/**
 * @brief CommonThread::mutexUnlock
 */
void CommonThread::mutexUnlock()
{
    m_mutex.unlock();
}

/**
 * @brief CommonThread::blockThread
 */
void CommonThread::blockThread()
{
    m_block = false;
    std::unique_lock<std::mutex> lock(m_cvMutex);
    m_cv.wait(lock);
    m_block = false;
}

/**
 * @brief CommonThread::sleepThread
 */
void CommonThread::sleepThread(const uint32_t uSeconds)
{
    // TODO: check accuracy
    std::this_thread::sleep_for(chronoMicroSec(uSeconds));
}

/**
 * @brief CommonThread::isActive
 * @return
 */
bool CommonThread::isActive() const
{
    return m_active;
}

}
