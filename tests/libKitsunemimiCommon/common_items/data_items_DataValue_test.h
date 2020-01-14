/**
 *  @file    dataItems_DataValue_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATAITEMS_DATAVALUE_TEST_H
#define DATAITEMS_DATAVALUE_TEST_H

#include <libKitsunemimiCommon/test.h>

namespace Kitsunemimi
{
class DataValue;

class DataItems_DataValue_Test
        : public Kitsunemimi::Test
{
public:
    DataItems_DataValue_Test();

private:
    void copy_assingment_constructor_test();
    void copy_assingment_operator_test();
    void operator_test();
    void get_test();
    void getSize_test();
    void remove_test();
    void copy_test();
    void toString_test();
    void getType_test();
    void isValue_isMap_isArray_test();
    void toValue_toMap_toArray_test();
    void getString_getInt_getFloat_getLong_getDouble_getBool_test();

    void getValueType_test();
    void setValue_test();
};

}  // namespace Kitsunemimi

#endif // DATAITEMS_DATAVALUE_TEST_H
