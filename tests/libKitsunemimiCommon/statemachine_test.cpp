/**
 *  @file    statemachine_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "statemachine_test.h"

#include <libKitsunemimiCommon/statemachine.h>

namespace Kitsunemimi
{
namespace Common
{

Statemachine_Test::Statemachine_Test()
    : Kitsunemimi::Common::Test("Statemachine_Test")
{
    createNewState_test();
    addTransition_test();
    goToNextState_test();
    setInitialChildState_test();
    addChildState_test();
    getCurrentStateId_test();
    isInState_test();
}

/**
 * createNewState_test
 */
void
Statemachine_Test::createNewState_test()
{
    Statemachine statemachine;

    TEST_EQUAL(statemachine.createNewState(SOURCE_STATE), true);
    TEST_EQUAL(statemachine.createNewState(SOURCE_STATE), false);
}

/**
 * setCurrentState_test
 */
void
Statemachine_Test::setCurrentState_test()
{
    Statemachine statemachine;

    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);

    TEST_EQUAL(statemachine.setCurrentState(SOURCE_STATE), true);
    TEST_EQUAL(statemachine.setCurrentState(FAIL), false);
}

/**
 * addTransition_test
 */
void
Statemachine_Test::addTransition_test()
{
    Statemachine statemachine;

    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);

    TEST_EQUAL(statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE), true);
    TEST_EQUAL(statemachine.addTransition(FAIL, GO, NEXT_STATE), false);
    TEST_EQUAL(statemachine.addTransition(SOURCE_STATE, GO, FAIL), false);
    TEST_EQUAL(statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE), false);
}

/**
 * goToNextState_test
 */
void
Statemachine_Test::goToNextState_test()
{
    Statemachine statemachine;

    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);
    statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE);

    TEST_EQUAL(statemachine.goToNextState(FAIL), false);
    TEST_EQUAL(statemachine.goToNextState(GO), true);
    TEST_EQUAL(statemachine.goToNextState(GO), false);
}

/**
 * setInitialChildState_test
 */
void
Statemachine_Test::setInitialChildState_test()
{
    Statemachine statemachine;

    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);

    TEST_EQUAL(statemachine.setInitialChildState(SOURCE_STATE, NEXT_STATE), true);
    TEST_EQUAL(statemachine.setInitialChildState(FAIL, NEXT_STATE), false);
    TEST_EQUAL(statemachine.setInitialChildState(SOURCE_STATE, FAIL), false);
}

/**
 * addChildState_test
 */
void
Statemachine_Test::addChildState_test()
{
    Statemachine statemachine;

    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);

    TEST_EQUAL(statemachine.addChildState(SOURCE_STATE, NEXT_STATE), true);
    TEST_EQUAL(statemachine.addChildState(FAIL, NEXT_STATE), false);
    TEST_EQUAL(statemachine.addChildState(SOURCE_STATE, FAIL), false);
}

/**
 * getCurrentStateId_test
 */
void
Statemachine_Test::getCurrentStateId_test()
{
    Statemachine statemachine;

    TEST_EQUAL(statemachine.getCurrentStateId(), 0);

    // init state
    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);
    statemachine.createNewState(CHILD_STATE);
    statemachine.createNewState(TARGET_STATE);

    // build state-machine
    statemachine.addChildState(NEXT_STATE, CHILD_STATE);
    statemachine.setInitialChildState(NEXT_STATE, CHILD_STATE);
    statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE);
    statemachine.addTransition(NEXT_STATE, GOGO, TARGET_STATE);

    TEST_EQUAL(statemachine.getCurrentStateId(), SOURCE_STATE);

    statemachine.goToNextState(GO);

    TEST_EQUAL(statemachine.getCurrentStateId(), CHILD_STATE);

    statemachine.goToNextState(GOGO);

    TEST_EQUAL(statemachine.getCurrentStateId(), TARGET_STATE);
}

/**
 * @brief getCurrentStateName_test
 */
void
Statemachine_Test::getCurrentStateName_test()
{
    Statemachine statemachine;

    TEST_EQUAL(statemachine.getCurrentStateId(), 0);

    // init state
    statemachine.createNewState(SOURCE_STATE, "SOURCE_STATE");
    statemachine.createNewState(NEXT_STATE, "NEXT_STATE");
    statemachine.createNewState(CHILD_STATE, "CHILD_STATE");
    statemachine.createNewState(TARGET_STATE, "TARGET_STATE");

    // build state-machine
    statemachine.addChildState(NEXT_STATE, CHILD_STATE);
    statemachine.setInitialChildState(NEXT_STATE, CHILD_STATE);
    statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE);
    statemachine.addTransition(NEXT_STATE, GOGO, TARGET_STATE);

    TEST_EQUAL(statemachine.getCurrentStateId(), SOURCE_STATE);

    statemachine.goToNextState(GO);

    TEST_EQUAL(statemachine.getCurrentStateName(), "CHILD_STATE");

    statemachine.goToNextState(GOGO);

    TEST_EQUAL(statemachine.getCurrentStateName(), "TARGET_STATE");
}

/**
 * isInState_test
 */
void
Statemachine_Test::isInState_test()
{
    Statemachine statemachine;

    TEST_EQUAL(statemachine.getCurrentStateId(), 0);

    // init state
    statemachine.createNewState(SOURCE_STATE);
    statemachine.createNewState(NEXT_STATE);
    statemachine.createNewState(CHILD_STATE);
    statemachine.createNewState(TARGET_STATE);

    // build state-machine
    statemachine.addChildState(NEXT_STATE, CHILD_STATE);
    statemachine.setInitialChildState(NEXT_STATE, CHILD_STATE);
    statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE);
    statemachine.addTransition(NEXT_STATE, GOGO, TARGET_STATE);

    TEST_EQUAL(statemachine.isInState(SOURCE_STATE), true);
    TEST_EQUAL(statemachine.isInState(FAIL), false);

    statemachine.goToNextState(GO);

    TEST_EQUAL(statemachine.isInState(CHILD_STATE), true);
    TEST_EQUAL(statemachine.isInState(NEXT_STATE), true);
    TEST_EQUAL(statemachine.isInState(SOURCE_STATE), false);
}

} // namespace Common
} // namespace Kitsunemimi
