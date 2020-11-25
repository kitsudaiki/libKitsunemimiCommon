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

//==================================================================================================
// Event
//==================================================================================================
Event::~Event() {}


//==================================================================================================
// SleepEvent
//==================================================================================================

/**
 * @brief constructor
 * @param milliSeconds time in milli-seconds, which the event should sleep
 */
SleepEvent::SleepEvent(const uint64_t milliSeconds)
{
    m_milliSeconds = milliSeconds;
}

/**
 * @brief destructor
 */
SleepEvent::~SleepEvent() {}

/**
 * @brief process sleep-event
 * @return false, if invalid time was set of zero milliseconds was set, else true
 */
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
