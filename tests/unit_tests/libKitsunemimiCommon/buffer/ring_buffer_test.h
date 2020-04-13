#ifndef RING_BUFFER_TEST_H
#define RING_BUFFER_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class RingBuffer_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    RingBuffer_Test();

private:
    void addData_RingBuffer_test();
    void addObject_RingBuffer_test();
    void getWritePosition_RingBuffer_test();
    void getSpaceToEnd_RingBuffer_test();
    void getDataPointer_RingBuffer_test();
    void moveForward_RingBuffer_test();
    void getObject_RingBuffer_test();
};

} // namespace Kitsunemimi

#endif // RING_BUFFER_TEST_H
