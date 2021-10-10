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
#include <string>
#include <vector>
#include <mutex>

namespace Kitsunemimi
{
class Thread;
class Event;

class ThreadHandler
{
public:
    static ThreadHandler* getInstance();

    const std::vector<std::string> getRegisteredThreads();
    Thread* getThread(const std::string &threadName);

private:
    friend Kitsunemimi::Thread;

    ThreadHandler();

    bool registerThread(Thread* thread);
    bool unregisterThread(const std::string &threadName);

    std::map<std::string, Thread*> m_allThreads;
    std::mutex m_mutex;

    static ThreadHandler* m_instance;
};

}

#endif // THREAD_HANDLER_CPP
