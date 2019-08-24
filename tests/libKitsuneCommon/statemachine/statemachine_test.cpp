/**
 *  @file    statemachine_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "statemachine_test.h"

#include <statemachine/statemachine.h>

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
 * getCurrentState_test
 */
void
Statemachine_Test::getCurrentState_test()
{
    Statemachine statemachine;

    UNITTEST(statemachine.getCurrentState(), "");

    statemachine.createNewState("sourceState");
    statemachine.createNewState("nextState");

    UNITTEST(statemachine.getCurrentState(), "sourceState");

    statemachine.addTransition("sourceState", "go", "nextState");
    statemachine.goToNextState("go");

    UNITTEST(statemachine.getCurrentState(), "nextState");
}

} // namespace Common
} // namespace Kitsune
