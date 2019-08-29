/**
 *  @file    table_items.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief data-handling object for tables
 *
 *  @detail This was created to print data as table on the command-line. Its primary to make
 *          data better visible for the user. Internally it uses the the data-items of this
 *          library. So its possible to easily convert json-items of libKitsuneJson
 *          into this table-output for example in REST-API responses.
 */

#ifndef TABLE_ITEM_H
#define TABLE_ITEM_H

#include <iostream>
#include <vector>

namespace Kitsune
{
namespace Common
{
class DataArray;
class DataObject;
class DataValue;

class TableItem
{
public:
    TableItem();
    TableItem(const TableItem &other);
    TableItem(DataArray* body,
              DataArray* header=nullptr);
    ~TableItem();
    TableItem& operator=(const TableItem& other);

    // column
    bool addColumn(const std::string &internalName,
                   const std::string &shownName="");
    bool renameColume(const std::string &internalName,
                      const std::string &newShownName);
    bool deleteColumn(const uint64_t x,
                      const bool withBody=false);
    bool deleteColumn(const std::string &internalName,
                      const bool withBody=false);

    // row
    bool addRow(const std::vector<std::string> rowContent);
    bool deleteRow(const uint64_t y);

    // cell
    bool setCell(const uint32_t x,
                 const uint32_t y,
                 const std::string &newValue);
    std::string getCell(const uint32_t x,
                        const uint32_t y);
    bool deleteCell(const uint32_t x,
                    const uint32_t y);

    // size
    uint64_t getNumberOfColums();
    uint64_t getNumberOfRows();

    // output
    std::string print();

private:
    DataArray* m_body = nullptr;
    DataArray* m_header = nullptr;

    const std::string getLimitLine(const std::vector<uint64_t> &sizes,
                                   const bool bigLine=false);
    const std::string printHeaderLine(const std::vector<uint64_t> &sizes);
    const std::string printBodyLine(const std::vector<uint64_t> &xSizes,
                                    const uint64_t rowHeight,
                                    const uint64_t y);

    const std::pair<uint64_t, uint64_t> getHeaderCellSize(const uint64_t x);
    const std::pair<uint64_t, uint64_t> getBodyCellSize(const uint64_t x,
                                                        const uint64_t y);
};

}  // namespace Common
}  // namespace Kitsune

#endif // TABLE_ITEM_H
