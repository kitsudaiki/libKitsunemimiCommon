/**
 *  @file    thread_handler_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef THREADHANDLER_TEST_H
#define THREADHANDLER_TEST_H

#include <unistd.h>

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>
#include <libKitsunemimiCommon/threading/thread.h>

namespace Kitsunemimi
{

class ThreadHandler_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    ThreadHandler_Test();

private:
    void all_test();
};

//==================================================================================================
// DummyThread for testing
//==================================================================================================
class DummyThread
        : public Kitsunemimi::Thread
{
public:
    DummyThread();

protected:
    void run();
};

} // namespace Kitsunemimi

#endif // THREADHANDLER_TEST_H
