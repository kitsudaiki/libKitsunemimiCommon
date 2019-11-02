/**
 *  @file       state.h
 *
 *  @brief      This state-objects are for the internal usage of the statemachine.
 *
 *  @details    They save all defined transitions.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef STATE_H
#define STATE_H

#include <map>
#include <vector>
#include <utility>

namespace Kitsunemimi
{
namespace Common
{

struct State
{
    std::map<uint32_t, State*> nextStates;
    std::string name = "";
    uint32_t id = 0;
    State* parent = nullptr;
    State* initialChild = nullptr;

    /**
     * @brief constructor
     */
    State(const uint32_t id,
          const std::string &name = "")
    {
        this->id = id;
        this->name = name;
    }

    /**
     * @brief add a ne transition to another state
     *
     * @param key key-value which identify the transistion
     * @param nextState next state with belongs to the spezific key
     *
     * @return false if key already registerd, else true
     */
    bool
    addTransition(const uint32_t &key, State* nextState)
    {
        std::map<uint32_t, State*>::iterator it;
        it = nextStates.find(key);

        if(it != nextStates.end()) {
            return false;
        }

        nextStates.insert(std::pair<uint32_t, State*>(key, nextState));

        return true;
    }

    /**
     * @brief get the next requested state
     *
     * @param key identifier-key for the next state
     *
     * @return pointer to the next state or the next state of the parent,
     *         returns null-pointer if the key is unknown
     */
    State*
    next(const uint32_t &key)
    {
        std::map<uint32_t, State*>::iterator it;
        it = nextStates.find(key);

        if(it != nextStates.end())
        {
            State* tempState = it->second;
            if(tempState->initialChild != nullptr) {
                tempState = tempState->initialChild;
            }
            return tempState;
        }

        return nullptr;
    }

    /**
     * @brief set the initial child state
     *
     * @param child initial child state
     */
    void
    setInitialChildState(State* child)
    {
        this->initialChild = child;
    }

    /**
     * @brief add child state
     *
     * @param child new child state
     */
    void
    addChildState(State* child)
    {
        child->parent = this;
    }
};

} // namespace Common
} // namespace Kitsunemimi

#endif // STATE_H
