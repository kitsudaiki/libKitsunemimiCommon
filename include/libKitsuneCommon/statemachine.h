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

namespace Kitsune
{
namespace Common
{
struct State;

class Statemachine
{
public:
    Statemachine();
    ~Statemachine();

    // init
    bool createNewState(const uint32_t stateName);
    bool setCurrentState(const uint32_t stateName);
    bool addTransition(const uint32_t stateName,
                       const uint32_t key,
                       const uint32_t nextStateName);
    bool setInitialChildState(const uint32_t stateName,
                              const uint32_t initialChildStateName);
    bool addChildState(const uint32_t stateName,
                       const uint32_t childStateName);

    // runtime
    bool goToNextState(const uint32_t nextStateName,
                       const uint32_t requiredPreState = 0);
    uint32_t getCurrentState();
    bool isInState(const uint32_t stateName);

private:
    std::map<uint32_t, State*> m_allStates;
    State* m_currentState = nullptr;
    std::atomic_flag m_state_lock = ATOMIC_FLAG_INIT;

    State* getState(const uint32_t stateName);
};

} // namespace Common
} // namespace Kitsune

#endif // STATEMACHINE_H
