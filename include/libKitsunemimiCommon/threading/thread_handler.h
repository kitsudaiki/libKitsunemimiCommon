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
public:
    static ThreadHandler* getInstance();

private:
    friend Kitsunemimi::Thread;

    ThreadHandler();

    void registerThread(Thread* thread);
    bool unregisterThread();

    std::map<std::thread::id, Thread*> m_allThreads;

    static ThreadHandler* m_instance;
};

}

#endif // THREAD_HANDLER_CPP
