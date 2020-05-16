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

#include <libKitsunemimiCommon/statemachine.h>
#include <state.h>

namespace Kitsunemimi
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
    std::map<uint32_t, State*>::iterator it;

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
 * @param stateId id of the new state
 * @param stateName name of the new state
 *
 * @return false if state-id already exist, else true
 */
bool
Statemachine::createNewState(const uint32_t stateId,
                             const std::string &stateName)
{
    // check if state already exist
    State* newState = getState(stateId);
    if(newState != nullptr) {
        return false;
    }

    // add new state
    newState = new State(stateId, stateName);
    m_allStates.insert(std::make_pair(stateId, newState));

    // first created state is set as current stat to init the statemachine
    if(m_currentState == nullptr) {
        m_currentState = newState;
    }

    return true;
}

/**
 * @brief set the current state of the statemachine to a specific state
 *
 * @param stateId id of the new state
 *
 * @return false, if state doesn't exist, else true
 */
bool
Statemachine::setCurrentState(const uint32_t stateId)
{
    // check if state already exist
    State* state = getState(stateId);
    if(state == nullptr) {
        return false;
    }

    m_currentState = state;

    return true;
}

/**
 * @brief add a ne transition to another state
 *
 * @param stateId source-state of the transition
 * @param key key-value which identify the transistion
 * @param nextStateId next state with belongs to the spezific key
 *
 * @return false if key already registerd or state or nextState doesn't exist, else true
 */
bool
Statemachine::addTransition(const uint32_t stateId,
                            const uint32_t key,
                            const uint32_t nextStateId)
{
    State* sourceState = getState(stateId);
    State* nextState = getState(nextStateId);

    if(sourceState == nullptr
            || nextState == nullptr)
    {
        return false;
    }

    // add transition
    const bool success =  sourceState->addTransition(key, nextState);

    return success;
}

/**
 * @brief set initial child state
 *
 * @param stateId source-state of the transition
 * @param initialChildStateId
 *
 * @return false, if id doesn't exist, else true
 */
bool
Statemachine::setInitialChildState(const uint32_t stateId,
                                   const uint32_t initialChildStateId)
{
    State* sourceState = getState(stateId);
    State* initialChildState = getState(initialChildStateId);

    if(sourceState == nullptr
            || initialChildState == nullptr)
    {
        return false;
    }

    sourceState->setInitialChildState(initialChildState);

    return true;
}

/**
 * @brief add one state as child state for another one
 *
 * @param stateId source-state of the transition
 * @param childStateId
 *
 * @return false, if id doesn't exist, else true
 */
bool
Statemachine::addChildState(const uint32_t stateId,
                            const uint32_t childStateId)
{
    State* sourceState = getState(stateId);
    State* childState = getState(childStateId);

    if(sourceState == nullptr
            || childState == nullptr)
    {
        return false;
    }

    sourceState->addChildState(childState);

    return true;
}

/**
 * @brief got to the next state, if possible
 *
 * @param nextStateId the identifier of the next state of the statemachine
 * @param requiredPreState
 *
 * @return true, if there was the next requested state
 */
bool
Statemachine::goToNextState(const uint32_t nextStateId,
                            const uint32_t requiredPreState)
{
    bool result = false;
    while(m_state_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    if(requiredPreState == 0
            || requiredPreState == m_currentState->id)
    {
        State* state = m_currentState;
        while(state != nullptr)
        {
            State* nextState = state->next(nextStateId);
            state = state->parent;
            if(nextState != nullptr)
            {
                m_currentState = nextState;
                result = true;
                break;
            }
        }
    }

    m_state_lock.clear(std::memory_order_release);

    return result;
}

/**
 * @brief getter for the current machine-state-id
 *
 * @return the state-id of the statemachine
 */
uint32_t
Statemachine::getCurrentStateId()
{
    uint32_t result = 0;

    while(m_state_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    if(m_currentState != nullptr) {
        result = m_currentState->id;
    }

    m_state_lock.clear(std::memory_order_release);

    return result;
}

/**
 * @brief getter for the current machine-state-name
 *
 * @return the state-name of the statemachine
 */
const std::string
Statemachine::getCurrentStateName()
{
    std::string result = "";

    while(m_state_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    if(m_currentState != nullptr) {
        result = m_currentState->name;
    }

    m_state_lock.clear(std::memory_order_release);

    return result;
}

/**
 * @brief check if in statemachine is in a specific state
 *
 * @param stateId id of the requested state
 *
 * @return true, if in requested state or in a child-state of the requested state, else false
 */
bool
Statemachine::isInState(const uint32_t stateId)
{
    bool result = false;
    while(m_state_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    State* state = m_currentState;
    while(state != nullptr)
    {
        if(state->id == stateId) {
            result = true;
        }
        state = state->parent;
    }

    m_state_lock.clear(std::memory_order_release);

    return result;
}

/**
 * @brief get state by id
 *
 * @param stateId id of the state
 *
 * @return nullptr, if state-id was not found, else pointer to the state
 */
State*
Statemachine::getState(const uint32_t stateId)
{
    State* result = nullptr;
    while(m_state_lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }

    // check and get source-state
    std::map<uint32_t, State*>::iterator it;
    it = m_allStates.find(stateId);
    if(it != m_allStates.end()) {
        result = it->second;
    }

    m_state_lock.clear(std::memory_order_release);

    return result;
}

} // namespace Kitsunemimi
