/**
 *  @file    statemachine_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STATEMACHINE_TEST_HPP
#define STATEMACHINE_TEST_HPP

#include <testing/test.hpp>

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

#endif // STATEMACHINE_TEST_HPP
