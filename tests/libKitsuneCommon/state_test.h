/**
 *  @file    state_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef STATE_TEST_H
#define STATE_TEST_H

#include <libKitsuneCommon/test.h>

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
    enum states
    {
        SOURCE_STATE = 1,
        TARGET_STATE = 2,
        CHILD_STATE = 3,
        NEXT_STATE = 4,
        INITIAL_STATE = 5,
        GO = 6,
        GOGO = 7,
        FAIL = 8,
    };

    void addTransition_test();
    void next_test();
    void setInitialChildState_test();
    void addChildState_test();
};

} // namespace Common
} // namespace Kitsune

#endif // STATE_TEST_H
