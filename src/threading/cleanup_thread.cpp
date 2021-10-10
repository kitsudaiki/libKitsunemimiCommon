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

CleanupThread* CleanupThread::m_cleanupThread = nullptr;

/**
 * constructor
 */
CleanupThread::CleanupThread()
    : Kitsunemimi::Thread("Kitsunemimi_CleanupThread", true) {}

/**
 * @brief destructor
 */
CleanupThread::~CleanupThread() {}

/**
 * @brief static methode to get instance of the interface
 *
 * @return pointer to the static instance
 */
CleanupThread*
CleanupThread::getInstance()
{
    if(m_cleanupThread == nullptr) {
        m_cleanupThread = new CleanupThread();
    }
    return m_cleanupThread;
}

/**
 * @brief schedule a thread for delteion
 * @param thread thread, which should be deleted
 */
void
CleanupThread::addThreadForCleanup(Thread* thread)
{
    m_mutex.lock();
    m_cleanupQueue.push(thread);
    m_mutex.unlock();
}

/**
 * @brief loop, which tries to delete all thread
 */
void
CleanupThread::run()
{
    while(m_abort == false)
    {
        sleepThread(100000);

        m_mutex.lock();
        if(m_cleanupQueue.size() > 0)
        {
            Thread* thread = m_cleanupQueue.front();
            m_cleanupQueue.pop();
            delete thread;
        }
        m_mutex.unlock();
    }
}

} // namespace Kitsunemimi
