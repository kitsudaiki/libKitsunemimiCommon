/**
 *  @file    data_items_DataMap_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATAITEMS_DATAMAP_TEST_H
#define DATAITEMS_DATAMAP_TEST_H

#include <libKitsunemimiCommon/test.h>

namespace Kitsunemimi
{
namespace Common
{
class DataMap;

class DataItems_DataMap_Test
        : public Kitsunemimi::Common::Test
{
public:
    DataItems_DataMap_Test();

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
    void getString_getInt_getFloat_test();

    void insert_test();
    void getStringByKey_getIntByKey_getFloatByKey_test();
    void getKeys_test();
    void getValues_test();
    void contains_test();

    DataMap initTestObject();
};

}  // namespace Common
}  // namespace Kitsunemimi

#endif // DATAITEMS_DATAMAP_TEST_H
