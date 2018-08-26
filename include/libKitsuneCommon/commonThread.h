/**
 *  @file    commonThread.h
 *  @author  Tobias Anker
 *
 *  @section DESCRIPTION
 *
 *  TODO: Description
 */

#ifndef COMMONTHREAD_H
#define COMMONTHREAD_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <pthread.h>

namespace Kitsune
{

class CommonThread
{
    typedef std::chrono::microseconds  chronoMicroSec;
    typedef std::chrono::nanoseconds  chronoNanoSec;
    typedef std::chrono::seconds  chronoSec;
    typedef std::chrono::high_resolution_clock::time_point chronoTimePoint;
    typedef std::chrono::high_resolution_clock chronoClock;

public:
    CommonThread();
    virtual ~CommonThread();

    bool start();
    bool stop();

    void continueThread();
    void initBlockThread();

    bool isActive() const;

protected:
    std::thread* m_thread = nullptr;
    uint32_t m_coreId = 0xFFFFFFFF;

    bool m_abort = false;
    bool m_block = false;
    bool m_active = false;

    std::mutex m_mutex;
    std::mutex m_cvMutex;
    std::condition_variable m_cv;

    void blockThread();
    void sleepThread(const uint32_t uSeconds);

    void mutexLock();
    void mutexUnlock();

    virtual void run() = 0;
};

}

#endif // COMMONTHREAD_H
