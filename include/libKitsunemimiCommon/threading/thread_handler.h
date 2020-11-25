/**
 *  @file       thread_handler.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef THREAD_HANDLER_CPP
#define THREAD_HANDLER_CPP

#include <map>
#include <thread>

namespace Kitsunemimi
{
class Thread;
class Event;

class ThreadHandler
{
private:
    friend Kitsunemimi::Thread;

    ThreadHandler();

    void registerThread(Thread* thread);
    bool unregisterThread();

    std::map<std::thread::id, Thread*> m_allThreads;
};

}

#endif // THREAD_HANDLER_CPP
