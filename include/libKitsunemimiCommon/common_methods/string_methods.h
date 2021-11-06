/**
 *  @file       string_methods.h
 *
 *  @brief      often used methods for string-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef STRING_METHODS_H
#define STRING_METHODS_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace Kitsunemimi
{

void splitStringByDelimiter(std::vector<std::string> &result,
                            const std::string &inputString,
                            const char delim);
void splitStringByLength(std::vector<std::string> &result,
                         const std::string &inputString,
                         const uint64_t splitLength);
void replaceSubstring(std::string& original,
                      const std::string& oldSubstring,
                      const std::string& newSubstring);
void removeWhitespaces(std::string& input);


void ltrim(std::string& original,
           const std::string &chars = "\t\n\v\f\r ");
void rtrim(std::string& original,
           const std::string& chars = "\t\n\v\f\r ");
void trim(std::string& original,
          const std::string& chars = "\t\n\v\f\r ");

void toUpperCase(std::string &original);
void toLowerCase(std::string &original);

} // namespace Kitsunemimi

#endif // STRINGMETHODS_H
