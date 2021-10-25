﻿/**
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
ThreadHandler::getRegisteredNames()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    std::vector<std::string> result;
    std::map<std::string, std::map<uint64_t, Thread*>>::const_iterator it;
    for(it = m_allThreads.begin();
        it != m_allThreads.end();
        it++)
    {
        result.push_back(it->first);
    }

    return result;
}

/**
 * @brief get all registered thread by a specific name
 *
 * @param threadName name of the requested thread
 *
 * @return list with all threads, which were registered under the name
 */
const std::vector<Thread*>
ThreadHandler::getThreads(const std::string &threadName)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    std::vector<Thread*> result;

    // iterate over names
    std::map<std::string, std::map<uint64_t, Thread*>>::iterator it;
    it = m_allThreads.find(threadName);
    if(it != m_allThreads.end())
    {
        // iterate over ids
        std::map<uint64_t, Thread*>::iterator thread_it;
        for(thread_it = it->second.begin();
            thread_it != it->second.end();
            thread_it++)
        {
            result.push_back(thread_it->second);
        }
    }

    return result;
}

/**
 * @brief request a new id
 *
 * @return new id
 */
uint64_t
ThreadHandler::getNewId()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_instance->m_counter++;
    return m_counter;
}

/**
 * @brief add thread to thread-handler
 *
 * @param thread pointer to the new thread to register
 */
void
ThreadHandler::registerThread(Thread* thread)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    // if name is already registered then add this to the name
    std::map<std::string, std::map<uint64_t, Thread*>>::iterator it;
    it = m_allThreads.find(thread->getThreadName());
    if(it != m_allThreads.end())
    {
        it->second.insert(std::make_pair(thread->getThreadId(), thread));
        return;
    }

    // if name is not even registered, ass a complete new entry
    std::map<uint64_t, Thread*> newEntry;
    newEntry.insert(std::make_pair(thread->getThreadId(), thread));
    m_allThreads.insert(std::make_pair(thread->getThreadName(), newEntry));

    return;
}

/**
 * @brief remove thread from thead-handler
 *
 * @param threadName name of the group of the thread
 * @param threadId id of the thread
 *
 * @return true, if found and unregistered, else false
 */
bool
ThreadHandler::unregisterThread(const std::string &threadName,
                                const uint64_t threadId)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    bool found = false;

    // iterate over names
    std::map<std::string, std::map<uint64_t, Thread*>>::iterator name_it;
    name_it = m_allThreads.find(threadName);
    if(name_it != m_allThreads.end())
    {
        // iterate over ids
        std::map<uint64_t, Thread*>::iterator id_it;
        id_it = name_it->second.find(threadId);
        if(id_it != name_it->second.end())
        {
            name_it->second.erase(id_it);
            found = true;
        }

        // if there are no more threads with the name, then remove the whole entry
        // to avoid a memory-leak
        if(name_it->second.size() == 0) {
            m_allThreads.erase(name_it);
        }
    }

    return found;
}

}
