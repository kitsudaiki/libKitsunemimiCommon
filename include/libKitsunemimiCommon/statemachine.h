/**
 *  @file       statemachine.h
 *
 *  @brief      Its only a simple statemachine in the moment.
 *
 *  @details    Basically its only to change the state and check the current state.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <atomic>

namespace Kitsunemimi
{
struct State;
class Event;

class Statemachine
{
public:
    Statemachine();
    ~Statemachine();

    // init
    bool createNewState(const uint32_t stateId,
                        const std::string &stateName = "");
    bool setCurrentState(const uint32_t stateId);
    bool addTransition(const uint32_t stateId,
                       const uint32_t key,
                       const uint32_t nextStateId);
    bool setInitialChildState(const uint32_t stateId,
                              const uint32_t initialChildStateId);
    bool addChildState(const uint32_t stateId,
                       const uint32_t childStateId);

    bool addEventToState(const uint32_t stateId,
                         Event* event);

    // runtime
    bool goToNextState(const uint32_t nextStateId,
                       const uint32_t requiredPreState = 0);
    uint32_t getCurrentStateId();
    const std::string getCurrentStateName();
    bool isInState(const uint32_t stateId);

private:
    std::map<uint32_t, State*> m_allStates;
    State* m_currentState = nullptr;
    std::atomic_flag m_state_lock = ATOMIC_FLAG_INIT;

    State* getState(const uint32_t stateId);
};

} // namespace Kitsunemimi

#endif // STATEMACHINE_H
