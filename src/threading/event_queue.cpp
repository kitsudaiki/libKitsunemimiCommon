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
 *
 * @param deleteEventObj set to true, to delete the event-object after it was processed
 */
EventQueue::EventQueue(const std::string &threadName,
                       const bool deleteEventObj)
    : Thread(threadName)
{
    m_deleteEventObj = deleteEventObj;
}

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
            event->processEvent();
            if(m_deleteEventObj) {
                delete event;
            }
        }
    }
}

}  // namespace Kitsunemimi
