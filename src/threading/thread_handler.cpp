/**
 *  @file       thread_handler.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/threading/thread_handler.h>

#include <libKitsunemimiCommon/threading/event.h>
#include <libKitsunemimiCommon/threading/thread.h>

namespace Kitsunemimi
{

/**
 * @brief private constructor
 */
ThreadHandler::ThreadHandler() {}

/**
 * @brief add thread to thread-handler
 *
 * @param thread pointer to the thread-object
 */
void
ThreadHandler::registerThread(Thread* thread)
{
    m_allThreads.insert(std::make_pair(std::this_thread::get_id(), thread));
}

/**
 * @brief remove thread from thead-handler
 *
 * @return false, if thread-id doesn't exist, else true
 */
bool
ThreadHandler::unregisterThread()
{
    std::map<std::thread::id, Thread*>::iterator it;
    it = m_allThreads.find(std::this_thread::get_id());
    if(it != m_allThreads.end())
    {
        m_allThreads.erase(it);
        return true;
    }

    return false;
}

}
