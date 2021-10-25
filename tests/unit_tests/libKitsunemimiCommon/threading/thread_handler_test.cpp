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
    std::vector<std::string> keys = ThreadHandler::getInstance()->getRegisteredNames();
    TEST_EQUAL(keys.size(), 0);

    DummyThread* testThread = new DummyThread();
    testThread->startThread();

    keys = ThreadHandler::getInstance()->getRegisteredNames();
    TEST_EQUAL(keys.size(), 1);
    sleep(1);
    if(keys.size() < 1) {
        return;
    }

    TEST_EQUAL(keys.at(0), "DummyThread");

    delete testThread;

    keys = ThreadHandler::getInstance()->getRegisteredNames();
    TEST_EQUAL(keys.size(), 0);
}

//==================================================================================================
// DummyThread for testing
//==================================================================================================
DummyThread::DummyThread()
    : Kitsunemimi::Thread("DummyThread")
{}

void DummyThread::run()
{
    while(m_abort == false) {
        sleepThread(1000000);
    }
}

} // namespace Kitsunemimi
