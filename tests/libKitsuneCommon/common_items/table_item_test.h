/**
 *  @file    table_item_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef TABLE_ITEM_TEST_H
#define TABLE_ITEM_TEST_H

#include <testing/test.h>
#include <common_items/table_item.h>

namespace Kitsune
{
namespace Common
{

class TableItem_test
        : public Kitsune::Common::Test
{
public:
    TableItem_test();

private:
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
    void print_Test();

    TableItem getTestTableItem();
};

}  // namespace Common
}  // namespace Kitsune

#endif // TABLE_ITEM_TEST_H
