/**
 *  @file    state_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "state_test.h"

#include <state.h>

namespace Kitsune
{
namespace Common
{

State_Test::State_Test()
    : Kitsune::Common::UnitTest("State_Test")
{
    addTransition_test();
    next_test();
    setInitialChildState_test();
    addChildState_test();
}

/**
 * addTransition_test
 */
void
State_Test::addTransition_test()
{
    State sourceState("source");
    State nextState("next");

    UNITTEST(sourceState.addTransition("go", &nextState), true);
    UNITTEST(sourceState.addTransition("go_now", &nextState), true);
    UNITTEST(sourceState.addTransition("go", &nextState), false);

    UNITTEST(sourceState.nextStates.size(), 2);
}

/**
 * next_test
 */
void
State_Test::next_test()
{
    State sourceState("source");
    State nextState("next");
    State* selctedState = nullptr;
    bool isNullptr = false;

    sourceState.addTransition("go", &nextState);

    selctedState = sourceState.next("go");
    isNullptr = selctedState == nullptr;
    UNITTEST(isNullptr, false);
    UNITTEST(selctedState->name, "next");

    selctedState = sourceState.next("fail");
    isNullptr = selctedState == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * setInitialChildState_test
 */
void
State_Test::setInitialChildState_test()
{
    State sourceState("source");
    State initialState("initial");

    sourceState.setInitialChildState(&initialState);
    UNITTEST(sourceState.initialChild->name, "initial");
}

/**
 * addChildState_test
 */
void
State_Test::addChildState_test()
{
    State sourceState("source");
    State childState("child");

    sourceState.addChildState(&childState);
    UNITTEST(childState.parent->name, "source");
}

} // namespace Common
} // namespace Kitsune
