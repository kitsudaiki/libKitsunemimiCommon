/**
 *  @file    state_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef STATE_TEST_H
#define STATE_TEST_H

#include <libKitsuneCommon/unit_test.h>

namespace Kitsune
{
namespace Common
{

class State_Test
        : public Kitsune::Common::UnitTest
{
public:
    State_Test();

private:
    void addTransition_test();
    void next_test();
    void setInitialChildState_test();
    void addChildState_test();
};

} // namespace Common
} // namespace Kitsune

#endif // STATE_TEST_H
