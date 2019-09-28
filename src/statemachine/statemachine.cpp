/**
 *  @file       statemachine.cpp
 *
 *  @brief      Its only a simple statemachine in the moment.
 *
 *  @details    Basically its only to change the state and check the current state.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <statemachine/statemachine.h>
#include <statemachine/state.h>

namespace Kitsune
{
namespace Common
{

/**
 * @brief constructor
 */
Statemachine::Statemachine() {}

/**
 * @brief destructor
 */
Statemachine::~Statemachine()
{
    std::map<std::string, State*>::iterator it;

    // delete all states
    for(it = m_allStates.begin(); it != m_allStates.end(); it++)
    {
        State* tempObj = it->second;
        delete tempObj;
        it->second = nullptr;
    }

    // clear map
    m_allStates.clear();
}

/**
 * @brief add a new state to the state-machine
 *
 * @param stateName name of the new state
 *
 * @return false if state-name already exist, else true
 */
bool
Statemachine::createNewState(const std::string &stateName)
{
    std::map<std::string, State*>::iterator it;

    // check if state already exist
    it = m_allStates.find(stateName);
    if(it != m_allStates.end()) {
        return false;
    }

    // add new state
    State* newState = new State(stateName);
    m_allStates.insert(std::pair<std::string, State*>(stateName, newState));

    // first created state is set as current stat to init the statemachine
    if(m_currentState == nullptr) {
        m_currentState = newState;
    }

    return true;
}

/**
 * @brief set the current state of the statemachine to a specific state
 *
 * @param stateName name of the new state
 *
 * @return false, if state doesn't exist, else true
 */
bool
Statemachine::setCurrentState(const std::string &stateName)
{
    std::map<std::string, State*>::iterator it;

    // check if state already exist
    it = m_allStates.find(stateName);
    if(it == m_allStates.end()) {
        return false;
    }

    m_currentState = it->second;

    return true;
}

/**
 * @brief add a ne transition to another state
 *
 * @param stateName source-state of the transition
 * @param key key-value which identify the transistion
 * @param nextStateName next state with belongs to the spezific key
 *
 * @return false if key already registerd or state or nextState doesn't exist, else true
 */
bool
Statemachine::addTransition(const std::string &stateName,
                            const std::string &key,
                            const std::string &nextStateName)
{
    // init
    State* sourceState = nullptr;
    State* nextState = nullptr;
    std::map<std::string, State*>::iterator it;

    // check and get source-state
    it = m_allStates.find(stateName);
    if(it != m_allStates.end()) {
        sourceState = it->second;
    } else {
        return false;
    }

    // check and get next-state
    it = m_allStates.find(nextStateName);
    if(it != m_allStates.end()) {
        nextState = it->second;
    } else {
        return false;
    }

    // add transition
    const bool success =  sourceState->addTransition(key, nextState);

    return success;
}

/**
 * @brief got to the next state, if possible
 *
 * @param next the identifier of the next state of the statemachine
 *
 * @return true, if there was the next requested state
 */
bool
Statemachine::goToNextState(const std::string &next)
{
    if(m_currentState == nullptr) {
        return false;
    }

    State* state = m_currentState->next(next);
    if(state == nullptr) {
        return false;
    }

    m_currentState = state;

    return true;
}

/**
 * @brief getter for the current machine-state
 *
 * @return the state of the statemachine
 */
std::string
Statemachine::getCurrentState() const
{
    if(m_currentState == nullptr) {
        return "";
    }

    return m_currentState->name;
}

} // namespace Common
} // namespace Kitsune
