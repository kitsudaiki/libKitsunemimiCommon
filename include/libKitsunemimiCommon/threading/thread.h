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

#define ADD_EVENT Kitsunemimi::addEvent

namespace Kitsunemimi
{
class DataBuffer;
class Event;
class ThreadHandler;

class Thread
{
public:
    Thread(int coreId = -1);
    virtual ~Thread();

    bool startThread();
    bool scheduleThreadForDeletion();

    void continueThread();
    void initBlockThread();

    bool isActive() const;
    bool bindThreadToCore(const int coreId);

    void addEventToQueue(Event* newEvent);

    static Kitsunemimi::ThreadHandler* m_threadHandler;

protected:
    std::thread* m_thread = nullptr;

    bool m_abort = false;
    bool m_block = false;
    bool m_active = false;
    bool m_scheduledForDeletion = false;
    int m_coreId = -1;

    // lock variables
    std::atomic_flag m_spin_lock = ATOMIC_FLAG_INIT;
    std::mutex m_mutex;
    std::mutex m_cvMutex;
    std::condition_variable m_cv;

    // lock methods
    void blockThread();
    void sleepThread(const uint32_t microSeconds);
    void mutexLock();
    void mutexUnlock();
    void spinLock();
    void spinUnlock();

    // cleanup
    void stopThread();
    bool waitForFinish();

    // event-queue
    std::atomic_flag m_eventQueue_lock = ATOMIC_FLAG_INIT;
    std::deque<Event*> m_eventQueue;
    Event* getEventFromQueue();

    virtual void run() = 0;
};

} // namespace Kitsunemimi

#endif // THREAD_H
