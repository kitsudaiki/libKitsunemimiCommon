/**
 *  @file    statemachine_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "statemachine_test.h"

#include <libKitsunemimiCommon/statemachine.h>
#include <libKitsunemimiCommon/threading/event.h>

namespace Kitsunemimi
{

Statemachine_Test::Statemachine_Test()
    : Kitsunemimi::MemoryLeakTestHelpter("Statemachine_Test")
{
    create_delete_test();
}

/**
 * @brief create_delete_test
 */
void
Statemachine_Test::create_delete_test()
{
    REINIT_TEST();

    Statemachine* testMachine = new Statemachine();
    testMachine->createNewState(1);
    testMachine->createNewState(2);
    testMachine->addEventToState(1, new SleepEvent(10000));
    testMachine->addEventToState(2, new SleepEvent(10000));
    delete testMachine;

    CHECK_MEMORY();
}


} // namespace Kitsunemimi
