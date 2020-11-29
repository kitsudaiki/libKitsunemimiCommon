/**
 *  @file       event.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef EVENT_H
#define EVENT_H

#include <chrono>
#include <thread>
#include <stdint.h>

namespace Kitsunemimi
{

//===================================================================
// Event
//===================================================================
class Event
{
public:
    virtual ~Event();

    virtual bool processEvent() = 0;
};

//===================================================================
// SleepEvent
//===================================================================
class SleepEvent
        : public Event
{
public:
    SleepEvent(const uint64_t milliSeconds);
    ~SleepEvent();

    bool processEvent();

private:
    uint64_t m_milliSeconds = 0;
};

}

#endif // EVENT_H
