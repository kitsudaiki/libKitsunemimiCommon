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

Kitsunemimi::ThreadHandler* ThreadHandler::m_instance = new ThreadHandler();

ThreadHandler::ThreadHandler() {}

/**
 * @brief static methode to get instance of the interface
 *
 * @return pointer to the static instance
 */
ThreadHandler*
ThreadHandler::getInstance()
{
    return m_instance;
}

/**
 * @brief get names of all registered threads
 *
 * @return list of names of all registred threads
 */
const std::vector<std::string>
ThreadHandler::getRegisteredThreads()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    std::vector<std::string> result;
    std::map<std::string, Thread*>::const_iterator it;
    for(it = m_allThreads.begin();
        it != m_allThreads.end();
        it++)
    {
        result.push_back(it->first);
    }

    return result;
}

/**
 * @brief get a registered thread by name
 *
 * @param threadName name of the requested thread
 *
 * @return nullptr if no thread was found, else pointer to the thread
 */
Thread*
ThreadHandler::getThread(const std::string &threadName)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    std::map<std::string, Thread*>::iterator it;
    it = m_allThreads.find(threadName);
    if(it != m_allThreads.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief add thread to thread-handler
 *
 * @param thread pointer to the thread-
 *
 * @return false if name already registered, else true
 */
bool
ThreadHandler::registerThread(Thread* thread)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    std::map<std::string, Thread*>::iterator it;
    it = m_allThreads.find(thread->getThreadName());
    if(it != m_allThreads.end()) {
        return false;
    }

    m_allThreads.insert(std::make_pair(thread->getThreadName(), thread));

    return true;
}

/**
 * @brief remove thread from thead-handler
 *
 * @return false, if thread-id doesn't exist, else true
 */
bool
ThreadHandler::unregisterThread(const std::string &threadName)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    std::map<std::string, Thread*>::iterator it;
    it = m_allThreads.find(threadName);
    if(it != m_allThreads.end())
    {
        m_allThreads.erase(it);
        return true;
    }

    return false;
}

}
