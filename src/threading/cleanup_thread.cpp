/**
 *  @file       thread_handler.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/threading/cleanup_thread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <cinttypes>
#include <unistd.h>

namespace Kitsunemimi
{

Kitsunemimi::CleanupThread* CleanupThread::m_instance = nullptr;

/**
 * constructor
 */
CleanupThread::CleanupThread()
    : Kitsunemimi::Thread() {}

CleanupThread::~CleanupThread() {}

/**
 * @brief static methode to get instance of the interface
 *
 * @return pointer to the static instance
 */
CleanupThread*
CleanupThread::getInstance()
{
    if(m_instance == nullptr) {
        m_instance = new CleanupThread();
    }

    return m_instance;
}

/**
 * @brief CleanupThread::addSocketForCleanup
 * @param socket
 */
void
CleanupThread::addThreadForCleanup(Thread* thread)
{
    mutexLock();
    m_cleanupQueue.push(thread);
    mutexUnlock();
}

/**
 * @brief CleanupThread::run
 */
void
CleanupThread::run()
{
    while(!m_abort)
    {
        sleepThread(100000);

        mutexLock();
        if(m_cleanupQueue.size() > 0)
        {
            Thread* thread = m_cleanupQueue.front();
            m_cleanupQueue.pop();
            delete thread;
        }
        mutexUnlock();
    }
}

} // namespace Kitsunemimi
