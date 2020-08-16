/**
 *  @file    state_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef STATE_TEST_H
#define STATE_TEST_H

#include <libKitsunemimiCommon/test_helper/memory_leak_test_helper.h>

namespace Kitsunemimi
{

class State_Test
        : public Kitsunemimi::MemoryLeakTestHelpter
{
public:
    State_Test();

private:
    void create_delete_test();
};

} // namespace Kitsunemimi

#endif // STATE_TEST_H
