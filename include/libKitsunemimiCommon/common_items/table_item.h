/**
 *  @file       table_items.cpp
 *
 *  @brief      Data-handling object for tables.
 *
 *  @details    This was created to print data as table on the command-line. Its primary to make
 *              data better visible for the user. Internally it uses the the data-items of this
 *              library. So its possible to easily convert json-items of libKitsuneJson into this
 *              table-output for example in REST-API responses.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef TABLE_ITEM_H
#define TABLE_ITEM_H

#include <iostream>
#include <vector>

namespace Kitsunemimi
{
class DataArray;
class DataMap;
class DataValue;

class TableItem
{
public:
    TableItem();
    TableItem(const TableItem &other);
    TableItem(DataArray* body,
              DataArray* header = nullptr);
    ~TableItem();
    TableItem& operator=(const TableItem& other);

    void clearTable();

    // column
    bool addColumn(const std::string &internalName,
                   const std::string &shownName = "");
    bool renameColume(const std::string &internalName,
                      const std::string &newShownName);
    bool deleteColumn(const uint64_t x,
                      const bool withBody = false);
    bool deleteColumn(const std::string &internalName,
                      const bool withBody = false);

    // row
    bool addRow(const std::vector<std::string> rowContent);
    bool deleteRow(const uint64_t y);

    // cell
    bool setCell(const uint32_t column,
                 const uint32_t row,
                 const std::string &newValue);
    const std::string getCell(const uint32_t column,
                              const uint32_t row);
    bool deleteCell(const uint32_t column,
                    const uint32_t row);

    // size
    uint64_t getNumberOfColums();
    uint64_t getNumberOfRows();

    // getter complete
    DataArray* getHeader() const;
    DataArray* getBody() const;
    DataMap* stealContent();
    DataMap* getRow(const uint32_t row, const bool copy) const;

    // output
    const std::string toString(const uint32_t maxColumnWidth = 500,
                               const bool withoutHeader = false);
    const std::string toJsonString();

private:
    DataArray* m_body = nullptr;
    DataArray* m_header = nullptr;

    // internal typedefs to make cleaner code
    typedef std::vector<std::string> TableCell;
    typedef std::vector<TableCell> TableRow;
    typedef std::vector<TableRow> TableBodyAll;

    // helper functions for the output
    const std::vector<std::string> getInnerName();
    const std::string getLimitLine(const std::vector<uint64_t> &sizes,
                                   const bool bigLine = false);

    // content-converter for easier output-handline
    void convertCellForOutput(TableCell &convertedCell,
                              const std::string &cellContent,
                              uint64_t &width,
                              const uint32_t maxColumnWidth);
    void convertHeaderForOutput(TableRow &convertedHeader,
                                std::vector<uint64_t> &xSizes,
                                const uint32_t maxColumnWidth);
    void convertBodyForOutput(TableBodyAll &convertedBody,
                              std::vector<uint64_t> &xSizes,
                              std::vector<uint64_t> &ySizes,
                              const std::vector<std::string> &columeInnerNames,
                              const uint32_t maxColumnWidth);

    // output of single lines of the output
    const std::string printHeaderLine(const std::vector<uint64_t> &xSizes);
    const std::string printBodyLine(TableRow &rowContent,
                                    const std::vector<uint64_t> &xSizes,
                                    const uint64_t rowHeigh);
    const std::string printHeaderBodyLine(TableRow &headerContent,
                                          TableRow &rowContent,
                                          const std::vector<uint64_t> &xSizes,
                                          const uint64_t rowHeigh,
                                          const uint64_t y);

    // final output of the two different versions
    const std::string printNormalTable(TableBodyAll &convertedBody,
                                       std::vector<uint64_t> &xSizes,
                                       std::vector<uint64_t> &ySizes,
                                       const bool withoutHeader);
};

}  // namespace Kitsunemimi

#endif // TABLE_ITEM_H
