/**
 *  @file    statemachine_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STATEMACHINE_TEST_H
#define STATEMACHINE_TEST_H

#include <testing/test.h>

namespace Kitsune
{
namespace Common
{

class Statemachine_Test
        : public Kitsune::Common::Test
{
public:
    Statemachine_Test();

private:
    void createNewState_test();
    void setCurrentState_test();
    void addTransition_test();
    void goToNextState_test();
    void getCurrentState_test();
};

} // namespace Common
} // namespace Kitsune

#endif // STATEMACHINE_TEST_H
