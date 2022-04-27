/**
 *  @file       event_queue.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/threading/event_queue.h>

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiCommon/threading/event.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 */
EventQueue::EventQueue(const std::string &threadName)
    : Thread(threadName)
{}

/**
 * @brief run event-processing thread
 */
void
EventQueue::EventQueue::run()
{
    while(m_abort == false)
    {
        // get event
        Event* event = getEventFromQueue();
        if(event == nullptr)
        {
            // sleep if no event exist in the queue
            sleepThread(10000);
        }
        else
        {
            LOG_DEBUG("process messaging event");
            event->processEvent();
            delete event;
        }
    }
}

}  // namespace Kitsunemimi
