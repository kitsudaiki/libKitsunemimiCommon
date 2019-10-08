/**
 *  @file    statemachine_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "statemachine_test.h"

#include <libKitsuneCommon/statemachine.h>

namespace Kitsune
{
namespace Common
{

Statemachine_Test::Statemachine_Test()
    : Kitsune::Common::UnitTest("Statemachine_Test")
{
    createNewState_test();
    addTransition_test();
    goToNextState_test();
    setInitialChildState_test();
    addChildState_test();
    getCurrentState_test();
}

/**
 * createNewState_test
 */
void
Statemachine_Test::createNewState_test()
{
    Statemachine statemachine;

    UNITTEST(statemachine.createNewState("state1"), true);
    UNITTEST(statemachine.createNewState("state1"), false);
}

/**
 * setCurrentState_test
 */
void
Statemachine_Test::setCurrentState_test()
{
    Statemachine statemachine;

    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");

    UNITTEST(statemachine.setCurrentState("sourceState"), true);
    UNITTEST(statemachine.setCurrentState("fail"), false);
}

/**
 * addTransition_test
 */
void
Statemachine_Test::addTransition_test()
{
    Statemachine statemachine;

    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");

    UNITTEST(statemachine.addTransition("sourceState", "go", "nextState"), true);
    UNITTEST(statemachine.addTransition("fail", "go", "nextState"), false);
    UNITTEST(statemachine.addTransition("sourceState", "go", "fail"), false);
    UNITTEST(statemachine.addTransition("sourceState", "go", "nextState"), false);
}

/**
 * goToNextState_test
 */
void
Statemachine_Test::goToNextState_test()
{
    Statemachine statemachine;

    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");
    statemachine.addTransition("sourceState", "go", "nextState");

    UNITTEST(statemachine.goToNextState("fail"), false);
    UNITTEST(statemachine.goToNextState("go"), true);
    UNITTEST(statemachine.goToNextState("go"), false);
}

/**
 * setInitialChildState_test
 */
void
Statemachine_Test::setInitialChildState_test()
{
    Statemachine statemachine;

    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");

    UNITTEST(statemachine.setInitialChildState("sourceState", "nextState"), true);
    UNITTEST(statemachine.setInitialChildState("fail", "nextState"), false);
    UNITTEST(statemachine.setInitialChildState("sourceState", "fail"), false);
}

/**
 * addChildState_test
 */
void
Statemachine_Test::addChildState_test()
{
    Statemachine statemachine;

    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");

    UNITTEST(statemachine.addChildState("sourceState", "nextState"), true);
    UNITTEST(statemachine.addChildState("fail", "nextState"), false);
    UNITTEST(statemachine.addChildState("sourceState", "fail"), false);
}

/**
 * getCurrentState_test
 */
void
Statemachine_Test::getCurrentState_test()
{
    Statemachine statemachine;

    UNITTEST(statemachine.getCurrentState(), "");

    // init state
    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");
    statemachine.createNewState("childState");
    statemachine.createNewState("targetState");

    // build state-machine
    statemachine.addChildState("nextState", "childState");
    statemachine.setInitialChildState("nextState", "childState");
    statemachine.addTransition("sourceState", "go", "nextState");
    statemachine.addTransition("nextState", "gogo", "targetState");

    UNITTEST(statemachine.getCurrentState(), "sourceState");

    statemachine.goToNextState("go");

    UNITTEST(statemachine.getCurrentState(), "childState");

    statemachine.goToNextState("gogo");

    UNITTEST(statemachine.getCurrentState(), "targetState");
}

} // namespace Common
} // namespace Kitsune
