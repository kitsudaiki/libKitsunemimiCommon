/**
 *  @file       event.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/threading/event.h>

namespace Kitsunemimi
{

//===================================================================
// Event
//===================================================================
Event::~Event() {}


//===================================================================
// SleepEvent
//===================================================================
SleepEvent::SleepEvent(const uint64_t milliSeconds)
{
    m_milliSeconds = milliSeconds;
}

SleepEvent::~SleepEvent() {}

bool
SleepEvent::processEvent()
{
    if(m_milliSeconds == 0) {
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(m_milliSeconds));

    return true;
}

}
