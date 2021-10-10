/**
 *  @file       thread_handler.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef KITSUNEMIMI_CLEANUP_THREAD_H
#define KITSUNEMIMI_CLEANUP_THREAD_H

#include <queue>

#include <libKitsunemimiCommon/threading/thread.h>

namespace Kitsunemimi
{

class CleanupThread
        : public Kitsunemimi::Thread
{
public:
    static CleanupThread* getInstance();

    void addThreadForCleanup(Thread* thread);

protected:
    void run();

private:
    CleanupThread();
    ~CleanupThread();

    std::queue<Thread*> m_cleanupQueue;
    std::mutex m_mutex;
    static CleanupThread* m_cleanupThread;
};

} // namespace Kitsunemimi

#endif // KITSUNEMIMI_CLEANUP_THREAD_H
