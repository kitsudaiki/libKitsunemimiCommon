/**
 *  @file       event_queue.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <libKitsunemimiCommon/threading/thread.h>

namespace Kitsunemimi
{

class EventQueue
        : public Kitsunemimi::Thread
{

public:
    EventQueue(const std::string &threadName);

protected:
    void run();

};

}  // namespace Kitsunemimi

#endif // EVENTQUEUE_H
