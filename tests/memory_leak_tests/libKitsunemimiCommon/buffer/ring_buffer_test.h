/**
 *  @file    ring_buffer_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef RING_BUFFER_TEST_H
#define RING_BUFFER_TEST_H

#include <libKitsunemimiCommon/test_helper/memory_leak_test_helper.h>

namespace Kitsunemimi
{

class RingBuffer_Test
        : public Kitsunemimi::MemoryLeakTestHelpter
{
public:
    RingBuffer_Test();

private:
    void create_delete_test();
};

} // namespace Kitsunemimi

#endif // RING_BUFFER_TEST_H
