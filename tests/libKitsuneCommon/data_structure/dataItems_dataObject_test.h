/**
 *  @file    dataItems_DataObject_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATAITEMS_DATAOBJECT_TEST_H
#define DATAITEMS_DATAOBJECT_TEST_H

#include <testing/test.h>

namespace Kitsune
{
namespace Common
{
class DataObject;

class DataItems_DataObject_Test
        : public Kitsune::Common::Test
{
public:
    DataItems_DataObject_Test();

private:
    void operator_test();
    void get_test();
    void getSize_test();
    void remove_test();
    void copy_test();
    void print_test();
    void getType_test();
    void isValue_isObject_isArray_test();
    void toValue_toObject_toArray_test();
    void toString_toInt_toFloat_test();

    void insert_test();
    void getString_getInt_getFloat_test();
    void getKeys_test();
    void getValues_test();
    void contains_test();

    DataObject initTestObject();
};

}  // namespace Common
}  // namespace Kitsune

#endif // DATAITEMS_DATAOBJECT_TEST_H
