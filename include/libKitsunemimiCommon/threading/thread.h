/**
 *  @file       thread.h
 *
 *  @brief      Common Thead-class.
 *
 *  @details    This class is only a collection of some thread-function like blocking and so on
 *              which I often use. This makes the creation of threads more easy for me. Additionally
 *              this class provides the ability to bind a new one of this thread to a specific
 *              cpu-thread.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef THREAD_H
#define THREAD_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <pthread.h>
#include <vector>
#include <atomic>
#include <deque>

namespace Kitsunemimi
{
struct DataBuffer;
class Event;
class ThreadHandler;

class Thread
{
public:
    Thread(const std::string &threadName);
    virtual ~Thread();

    bool startThread();

    bool scheduleThreadForDeletion();

    void continueThread();
    void initBlockThread();

    bool isActive() const;
    bool bindThreadToCores(const std::vector<uint64_t> coreIds);
    bool bindThreadToCore(const uint64_t coreId);
    const std::vector<uint64_t> getCoreIds() const;
    const std::string getThreadName() const;
    uint64_t getThreadId() const;

    void addEventToQueue(Event* newEvent);
    void clearEventQueue();

protected:
    bool m_abort = false;
    bool m_block = false;

    // lock methods
    void blockThread();
    void sleepThread(const uint32_t microSeconds);
    void spinLock();
    void spinUnlock();

    // event-queue
    Event* getEventFromQueue();

    virtual void run() = 0;

private:
    void stopThread();

    // generial variables
    std::thread* m_thread = nullptr;
    const std::string m_threadName = "";
    const uint64_t m_threadId = 0;

    bool m_active = false;
    bool m_scheduledForDeletion = false;
    std::vector<uint64_t> m_coreIds;

    // event-queue-variables
    std::deque<Event*> m_eventQueue;
    std::atomic_flag m_eventQueue_lock = ATOMIC_FLAG_INIT;

    // lock variables
    std::atomic_flag m_spin_lock = ATOMIC_FLAG_INIT;
    std::mutex m_cvMutex;
    std::condition_variable m_cv;
};

} // namespace Kitsunemimi

#endif // THREAD_H
