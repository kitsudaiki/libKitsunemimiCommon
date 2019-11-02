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
    State sourceState(SOURCE_STATE);
    State nextState(NEXT_STATE);

    UNITTEST(sourceState.addTransition(GO, &nextState), true);
    UNITTEST(sourceState.addTransition(GOGO, &nextState), true);
    UNITTEST(sourceState.addTransition(GO, &nextState), false);

    UNITTEST(sourceState.nextStates.size(), 2);
}

/**
 * next_test
 */
void
State_Test::next_test()
{
    State sourceState(SOURCE_STATE);
    State nextState(NEXT_STATE);
    State* selctedState = nullptr;
    bool isNullptr = false;

    sourceState.addTransition(GO, &nextState);

    selctedState = sourceState.next(GO);
    isNullptr = selctedState == nullptr;
    UNITTEST(isNullptr, false);
    UNITTEST(selctedState->id, NEXT_STATE);

    selctedState = sourceState.next(FAIL);
    isNullptr = selctedState == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * setInitialChildState_test
 */
void
State_Test::setInitialChildState_test()
{
    State sourceState(SOURCE_STATE);
    State initialState(INITIAL_STATE);

    sourceState.setInitialChildState(&initialState);
    UNITTEST(sourceState.initialChild->id, INITIAL_STATE);
}

/**
 * addChildState_test
 */
void
State_Test::addChildState_test()
{
    State sourceState(SOURCE_STATE);
    State childState(CHILD_STATE);

    sourceState.addChildState(&childState);
    UNITTEST(childState.parent->id, SOURCE_STATE);
}

} // namespace Common
} // namespace Kitsune
