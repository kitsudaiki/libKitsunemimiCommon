/**
 *  @file    statemachine_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef STATEMACHINE_TEST_H
#define STATEMACHINE_TEST_H

#include <libKitsuneCommon/unit_test.h>

namespace Kitsune
{
namespace Common
{

class Statemachine_Test
        : public Kitsune::Common::UnitTest
{
public:
    Statemachine_Test();

private:
    void createNewState_test();
    void setCurrentState_test();
    void addTransition_test();
    void goToNextState_test();
    void getCurrentState_test();
    void setInitialChildState_test();
    void addChildState_test();
};

} // namespace Common
} // namespace Kitsune

#endif // STATEMACHINE_TEST_H
