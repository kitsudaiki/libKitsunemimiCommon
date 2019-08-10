/**
 *  @file    state_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STATE_TEST_HPP
#define STATE_TEST_HPP

#include <testing/test.hpp>

namespace Kitsune
{
namespace Common
{

class State_Test
        : public Kitsune::Common::Test
{
public:
    State_Test();

private:
    void addTransition_test();
    void next_test();

};

} // namespace Common
} // namespace Kitsune

#endif // STATE_TEST_HPP
