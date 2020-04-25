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

} // namespace Kitsunemimi

#endif // STRINGMETHODS_H
