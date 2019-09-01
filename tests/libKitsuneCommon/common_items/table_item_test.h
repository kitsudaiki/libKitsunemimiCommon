/**
 *  @file    table_item_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef TABLE_ITEM_TEST_H
#define TABLE_ITEM_TEST_H

#include <testing/unit_test.h>
#include <common_items/table_item.h>

namespace Kitsune
{
namespace Common
{

class TableItem_test
        : public Kitsune::Common::UnitTest
{
public:
    TableItem_test();

private:
    void copy_contructor_test();
    void assignment_operator_test();
    void clearTable_test();

    // column
    void addColumn_Test();
    void renameColume_Test();
    void deleteColumn_Test();

    // row
    void addRow_Test();
    void deleteRow_Test();

    // cell
    void setCell_Test();
    void getCell_Test();
    void deleteCell_Test();

    // size
    void getNumberOfColums_Test();
    void getNumberOfRows_Test();

    // output
    void toString_test();

    TableItem getTestTableItem();
};

}  // namespace Common
}  // namespace Kitsune

#endif // TABLE_ITEM_TEST_H
