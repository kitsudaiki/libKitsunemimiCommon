/**
 *  @file    state.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief state for the statemachine
 *
 *  @detail This state-objects are for the internal usage of the statemachine. They save all
 *          defined transitions.
 */

#ifndef STATE_H
#define STATE_H

#include <map>
#include <vector>
#include <utility>

namespace Kitsune
{
namespace Common
{

struct State
{
    std::map<std::string, State*> nextStates;
    std::string name = "";
    State* parent = nullptr;
    State* initialChild = nullptr;

    /**
     * @brief constructor
     */
    State(const std::string name)
    {
        this->name = name;
    }

    /**
     * @brief add a ne transition to another state
     *
     * @param key key-value which identify the transistion
     * @param nextState next state with belongs to the spezific key
     *
     * @retrun false if key already registerd, else true
     */
    bool
    addTransition(const std::string &key, State* nextState)
    {
        std::map<std::string, State*>::iterator it;
        it = nextStates.find(key);

        if(it != nextStates.end()) {
            return false;
        }

        nextStates.insert(std::pair<std::string, State*>(key, nextState));

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
    next(const std::string &key)
    {
        std::map<std::string, State*>::iterator it;
        it = nextStates.find(key);

        if(it != nextStates.end())
        {
            State* tempState = it->second;
            while(tempState->initialChild != nullptr)
            {
                tempState = tempState->initialChild;
            }
            return tempState;
        }
        else
        {
            if(parent != nullptr) {
                return parent->next(key);
            }
        }

        return nullptr;
    }
};

} // namespace Common
} // namespace Kitsune

#endif // STATE_H
