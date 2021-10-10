/**
 *  @file    thread_handler_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "thread_handler_test.h"

#include <libKitsunemimiCommon/threading/thread_handler.h>

namespace Kitsunemimi
{

ThreadHandler_Test::ThreadHandler_Test()
    : Kitsunemimi::CompareTestHelper("ThreadHandler_Test")
{
    all_test();
}

/**
 * @brief all_test
 */
void
ThreadHandler_Test::all_test()
{
    std::vector<std::string> keys = ThreadHandler::getInstance()->getRegisteredThreads();
    TEST_EQUAL(keys.size(), 1);

    DummyThread* testThread = new DummyThread();

    keys = ThreadHandler::getInstance()->getRegisteredThreads();
    TEST_EQUAL(keys.size(), 2);
    sleep(1);
    if(keys.size() < 2) {
        return;
    }

    const bool found = keys.at(0) == "DummyThread"
                       || keys.at(1) == "DummyThread";
    TEST_EQUAL(found, true);

    delete testThread;

    keys = ThreadHandler::getInstance()->getRegisteredThreads();
    TEST_EQUAL(keys.size(), 1);
}

//==================================================================================================
// DummyThread for testing
//==================================================================================================
DummyThread::DummyThread()
    : Kitsunemimi::Thread("DummyThread", true)
{}

void DummyThread::run()
{
    while(m_abort == false) {
        sleepThread(1000000);
    }
}

} // namespace Kitsunemimi
