/**
 *  @file    commonThread.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef COMMONTHREAD_H
#define COMMONTHREAD_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <pthread.h>
#include <vector>

namespace Kitsune
{
class CommonDataBuffer;

class CommonThread
{
public:
    CommonThread(int coreId = -1);
    virtual ~CommonThread();

    bool start();
    bool stop();
    bool waitForFinish();

    void continueThread();
    void initBlockThread();

    bool isActive() const;
    bool bindThreadToCore(const int coreId);

protected:
    std::thread* m_thread = nullptr;

    bool m_abort = false;
    bool m_block = false;
    bool m_active = false;

    int m_coreId = -1;

    std::mutex m_mutex;
    std::mutex m_cvMutex;
    std::condition_variable m_cv;

    void blockThread();
    bool sleepThread(const uint32_t uSeconds);

    void mutexLock();
    void mutexUnlock();

    virtual void run() = 0;
};

}

#endif // COMMONTHREAD_H
