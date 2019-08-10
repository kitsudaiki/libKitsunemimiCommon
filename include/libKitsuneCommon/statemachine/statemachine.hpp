/**
 *  @file    statemachine.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <vector>
#include <iostream>
#include <map>
#include <utility>

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

    // runtime
    bool goToNextState(const std::string &next);
    std::string getCurrentState() const;

private:
    std::map<std::string, State*> m_allStates;

    State* m_currentState = nullptr;
};

} // namespace Common
} // namespace Kitsune

#endif // STATEMACHINE_HPP
