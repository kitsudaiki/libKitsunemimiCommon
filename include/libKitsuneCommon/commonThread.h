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
    ~CommonThread();

    bool start();
    bool stop();

    void continueThread();
    void initBlockThread();

    bool isActive() const;

    virtual void run() = 0;

protected:
    std::thread* m_thread = nullptr;
    bool m_abort = false;
    bool m_block = false;
    bool m_active = false;

    std::mutex m_mutex;
    std::mutex m_cvMutex;
    std::condition_variable m_cv;

    void blockThread();
    void sleepThread(const uint32_t seconrs);

    void mutexLock();
    void mutexUnlock();
};

}

#endif // COMMONTHREAD_H
