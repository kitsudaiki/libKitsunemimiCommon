/**
 *  @file    table_item_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "table_item_test.h"

namespace Kitsune
{
namespace Common
{

TableItem_test::TableItem_test()
    : Kitsune::Common::UnitTest("TableItem_test")
{
    copy_contructor_test();
    assignment_operator_test();

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
 * @brief TableItem_test::copy_contructor_test
 */
void
TableItem_test::copy_contructor_test()
{
    TableItem testItem = getTestTableItem();
    TableItem copyItem = testItem;

    UNITTEST(copyItem.print(), testItem.print());
}

/**
 * @brief TableItem_test::assignment_operator_test
 */
void
TableItem_test::assignment_operator_test()
{
    TableItem testItem = getTestTableItem();
    TableItem assignedItem;

    assignedItem = testItem;

    UNITTEST(assignedItem.print(), testItem.print());
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
                                "+======+=====+\n";
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
                                "+=====+\n";
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
                                "+=====+\n";
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

    UNITTEST(testItem.addRow(std::vector<std::string>{"this is a test", "k"}), true);
    UNITTEST(testItem.addRow(std::vector<std::string>{"asdf", "qwert"}), true);

    const std::string compare =
            "+----------------+-----------+\n"
            "| ASDF           | poipoipoi |\n"
            "+================+===========+\n"
            "| this is a test | k         |\n"
            "+----------------+-----------+\n"
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
            "+======+===========+\n"
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
            "+================+===========+\n"
            "| this is a test | k         |\n"
            "+----------------+-----------+\n"
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
            "+================+===========+\n"
            "| this is a test | k         |\n"
            "+----------------+-----------+\n"
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

    // additional multiline test
    testItem.addRow(std::vector<std::string>{"x\ny\nz", " "});
    testItem.addRow(std::vector<std::string>{"y", "abcdefghijklmnopqrst"});


    const std::string compare =
            "+-----------+-----------+\n"
            "| ASDF      | poipoipoi |\n"
            "+===========+===========+\n"
            "| this is a | k         |\n"
            "|  test     |           |\n"
            "+-----------+-----------+\n"
            "| asdf      | qwert     |\n"
            "+-----------+-----------+\n"
            "| x         |           |\n"
            "| y         |           |\n"
            "| z         |           |\n"
            "+-----------+-----------+\n"
            "| y         | abcdefghi |\n"
            "|           | jklmnopqr |\n"
            "|           | st        |\n"
            "+-----------+-----------+\n";

    // test with a maximum cell width of 9
    UNITTEST(testItem.print(9), compare);

    const std::string compareVertical =
            "+-----------+-----------+\n"
            "| ASDF      | this is a |\n"
            "|           |  test     |\n"
            "+-----------+-----------+\n"
            "| poipoipoi | k         |\n"
            "+-----------+-----------+\n";

    UNITTEST(testItem.print(9, true), compareVertical);
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

    testItem.addRow(std::vector<std::string>{"this is a test", "k"});
    testItem.addRow(std::vector<std::string>{"asdf", "qwert"});

    return testItem;
}

}  // namespace Common
}  // namespace Kitsune
