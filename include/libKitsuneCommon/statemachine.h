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
    bool createNewState(const std::string &stateName);
    bool setCurrentState(const std::string &stateName);
    bool addTransition(const std::string &stateName,
                       const std::string &key,
                       const std::string &nextStateName);
    bool setInitialChildState(const std::string &stateName,
                              const std::string &initialChildStateName);
    bool addChildState(const std::string &stateName,
                       const std::string &childStateName);

    // runtime
    bool goToNextState(const std::string &nextStateName,
                       const std::string &requiredPreState = "");
    std::string getCurrentState();
    bool isInState(const std::string &stateName);

private:
    std::map<std::string, State*> m_allStates;
    State* m_currentState = nullptr;
    std::atomic_flag m_state_lock = ATOMIC_FLAG_INIT;

    State* getState(const std::string stateName);
};

} // namespace Common
} // namespace Kitsune

#endif // STATEMACHINE_H
