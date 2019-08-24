/**
 *  @file    table_item_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */
#include "table_item_test.h"

namespace Kitsune
{
namespace Common
{

TableItem_test::TableItem_test()
    : Kitsune::Common::Test("TableItem_test")
{
    // column
    addColumn_Test();
    renameColume_Test();
    deleteColumn_Test();

    // row
    addRow_Test();
    deleteRow_Test();

    // cell
    setCell_Test();
    getCell_Test();
    deleteCell_Test();

    // size
    getNumberOfColums_Test();
    getNumberOfRows_Test();

    // output
    print_Test();
}

/**
 * @brief addColumn_Test
 */
void
TableItem_test::addColumn_Test()
{
    TableItem testItem;

    UNITTEST(testItem.addColumn("asdf", "ASDF"), true);
    UNITTEST(testItem.addColumn("poi"), true);

    const std::string compare = "+------+-----+\n"
                                "| ASDF | poi |\n"
                                "+------+-----+\n"
                                "+------+-----+\n";
    UNITTEST(testItem.print(), compare);
}

/**
 * @brief renameColume_Test
 */
void
TableItem_test::renameColume_Test()
{
    TableItem testItem;

    testItem.addColumn("asdf", "ASDF");

    UNITTEST(testItem.renameColume("asdf", "XYZ"), true);
    UNITTEST(testItem.renameColume("fail", "XYZ"), false);

    const std::string compare = "+-----+\n"
                                "| XYZ |\n"
                                "+-----+\n"
                                "+-----+\n";
    UNITTEST(testItem.print(), compare);
}

/**
 * @brief deleteColumn_Test
 */
void
TableItem_test::deleteColumn_Test()
{
    TableItem testItem;

    testItem.addColumn("asdf", "ASDF");
    testItem.addColumn("poi");

    UNITTEST(testItem.deleteColumn("asdf"), true);
    UNITTEST(testItem.deleteColumn("fail"), false);

    const std::string compare = "+-----+\n"
                                "| poi |\n"
                                "+-----+\n"
                                "+-----+\n";
    UNITTEST(testItem.print(), compare);
}

/**
 * @brief addRow_Test
 */
void
TableItem_test::addRow_Test()
{
    TableItem testItem;

    testItem.addColumn("asdf", "ASDF");
    testItem.addColumn("poipoipoi");

    std::vector<std::string> newRow;

    newRow.push_back("this is a test");
    newRow.push_back("k");
    UNITTEST(testItem.addRow(newRow), true);

    newRow.clear();
    newRow.push_back("asdf");
    newRow.push_back("qwert");
    UNITTEST(testItem.addRow(newRow), true);

    const std::string compare =
            "+----------------+-----------+\n"
            "| ASDF           | poipoipoi |\n"
            "+----------------+-----------+\n"
            "| this is a test | k         |\n"
            "| asdf           | qwert     |\n"
            "+----------------+-----------+\n";

    UNITTEST(testItem.print(), compare);
}

/**
 * @brief deleteRow_Test
 */
void
TableItem_test::deleteRow_Test()
{
    TableItem testItem = getTestTableItem();

    UNITTEST(testItem.deleteRow(0), true);
    UNITTEST(testItem.deleteRow(1), false);

    const std::string compare =
            "+------+-----------+\n"
            "| ASDF | poipoipoi |\n"
            "+------+-----------+\n"
            "| asdf | qwert     |\n"
            "+------+-----------+\n";

    UNITTEST(testItem.print(), compare);
}

/**
 * @brief setCell_Test
 */
void
TableItem_test::setCell_Test()
{
    TableItem testItem = getTestTableItem();

    UNITTEST(testItem.setCell(1, 1, "hmmm"), true);
    UNITTEST(testItem.setCell(1, 10, "hmmm"), false);
    UNITTEST(testItem.setCell(10, 1, "hmmm"), false);

    const std::string compare =
            "+----------------+-----------+\n"
            "| ASDF           | poipoipoi |\n"
            "+----------------+-----------+\n"
            "| this is a test | k         |\n"
            "| asdf           | hmmm      |\n"
            "+----------------+-----------+\n";

    UNITTEST(testItem.print(), compare);
}

/**
 * @brief getCell_Test
 */
void
TableItem_test::getCell_Test()
{
    TableItem testItem = getTestTableItem();

    UNITTEST(testItem.getCell(0, 1), "asdf");
    UNITTEST(testItem.getCell(10, 1), "");
    UNITTEST(testItem.getCell(0, 10), "");
}

/**
 * @brief deleteCell_Test
 */
void
TableItem_test::deleteCell_Test()
{
    TableItem testItem = getTestTableItem();

    UNITTEST(testItem.deleteCell(0, 1), true);
    UNITTEST(testItem.deleteCell(10, 1), false);
    UNITTEST(testItem.deleteCell(0, 10), false);

    const std::string compare =
            "+----------------+-----------+\n"
            "| ASDF           | poipoipoi |\n"
            "+----------------+-----------+\n"
            "| this is a test | k         |\n"
            "|                | qwert     |\n"
            "+----------------+-----------+\n";

    UNITTEST(testItem.print(), compare);
}

/**
 * @brief getNumberOfColums_Test
 */
void
TableItem_test::getNumberOfColums_Test()
{
    TableItem testItem = getTestTableItem();

    UNITTEST(testItem.getNumberOfColums(), 2);
}

/**
 * @brief getNumberOfRows_Test
 */
void
TableItem_test::getNumberOfRows_Test()
{
    TableItem testItem = getTestTableItem();

    UNITTEST(testItem.getNumberOfRows(), 2);
    testItem.deleteRow(0);
    UNITTEST(testItem.getNumberOfRows(), 1);
}

/**
 * @brief print_Test
 */
void
TableItem_test::print_Test()
{
    TableItem testItem = getTestTableItem();

    const std::string compare =
            "+----------------+-----------+\n"
            "| ASDF           | poipoipoi |\n"
            "+----------------+-----------+\n"
            "| this is a test | k         |\n"
            "| asdf           | qwert     |\n"
            "+----------------+-----------+\n";

    UNITTEST(testItem.print(), compare);
}

/**
 * @brief TableItem_test::getTestTableItem
 * @return
 */
TableItem
TableItem_test::getTestTableItem()
{
    TableItem testItem;

    testItem.addColumn("asdf", "ASDF");
    testItem.addColumn("poipoipoi");

    std::vector<std::string> newRow;

    newRow.push_back("this is a test");
    newRow.push_back("k");
    testItem.addRow(newRow);

    newRow.clear();
    newRow.push_back("asdf");
    newRow.push_back("qwert");
    testItem.addRow(newRow);

    return testItem;
}

}  // namespace Common
}  // namespace Kitsune
