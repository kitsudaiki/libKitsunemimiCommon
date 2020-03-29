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
    void addDataToBuffer_test();
    void addObjectToBuffer_test();
    void getWritePosition_test();
    void getSpaceToEnd_test();
    void getDataPointer_test();
    void moveBufferForward_test();
    void getObjectFromBuffer_test();
};

} // namespace Kitsunemimi

#endif // RING_BUFFER_TEST_H
