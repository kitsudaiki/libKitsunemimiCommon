#ifndef BLOCK_BUFFER_TEST_H
#define BLOCK_BUFFER_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class StackBuffer_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    StackBuffer_Test();

private:
    void constructor_test();
    void addNewToStack_test();
    void writeDataIntoBuffer_test();
    void addObjectToBuffer_test();
    void getFirstElement_test();
    void removeFirstFromStack_test();
    void resetBuffer_test();
};

} // namespace Kitsunemimi

#endif // BLOCK_BUFFER_TEST_H
