/**
 *  @file    data_buffer_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATA_BUFFER_TEST_H
#define DATA_BUFFER_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class DataBuffer_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    DataBuffer_Test();

private:
    void constructor_test();
    void structSize_test();
    void copyConstructor_test();
    void addObject_DataBuffer_test();
    void getBlock_DataBuffer_test();
    void reset_DataBuffer_test();

    void addData_DataBuffer_test();
    void allocateBlocks_DataBuffer_test();
};

} // namespace Kitsunemimi

#endif // DATABUFFER_TEST_H
