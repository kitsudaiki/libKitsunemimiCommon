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
#include <thread>

namespace Kitsunemimi
{
class Thread;
class Event;

class ThreadHandler
{
public:
    static ThreadHandler* getInstance();

    const std::vector<std::string> getRegisteredNames();
    const std::vector<Thread*> getThreads(const std::string &threadName);
    uint64_t getNewId() const;

private:
    friend Kitsunemimi::Thread;

    ThreadHandler();

    void registerThread(Thread* thread);
    bool unregisterThread(const std::string &threadName, const uint64_t threadId);

    std::map<std::string, std::map<uint64_t, Thread*>> m_allThreads;
    std::mutex m_mutex;
    uint64_t m_counter = 0;

    static ThreadHandler* m_instance;
};

}

#endif // THREAD_HANDLER_CPP
