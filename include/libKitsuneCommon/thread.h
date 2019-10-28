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

namespace Kitsune
{
namespace Common
{

class DataBuffer;

class Thread
{
public:
    Thread(int coreId = -1);
    virtual ~Thread();

    bool startThread();
    void stopThread();
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

    virtual void run() = 0;
};

} // namespace Common
} // namespace Kitsune

#endif // THREAD_H
