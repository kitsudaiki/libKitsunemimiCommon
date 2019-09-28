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

namespace Kitsune
{
namespace Common
{

/**
 * @brief sptrit a string at a specific delimiter
 *
 * @param inputString string, which sould be splitted
 * @param delim delimiter to identify the points to split
 *
 * @return vector with the string parts
 */
inline std::vector<std::string>
splitStringByDelimiter(const std::string &inputString,
                       const char delim)
{
    // precheck
    if(inputString.length() == 0) {
        return std::vector<std::string>();
    }

    // init variables
    std::stringstream inputStream(inputString);
    std::string item;
    std::vector<std::string> result;

    // split
    while(std::getline(inputStream, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

/**
 * @brief split a string into part with a maximum length
 *
 * @param inputString string, which sould be splitted
 * @param splitLength max length of the single substrings
 *
 * @return vector with the string parts
 */
inline std::vector<std::string>
splitStringByLength(const std::string &inputString,
                    const uint64_t splitLength)
{
    const uint64_t numberOfSubstrings = inputString.length() / splitLength;
    std::vector<std::string> result;

    // split string
    // number of string +1 to handle leftovers
    for(uint64_t i = 0; i < numberOfSubstrings + 1; i++)
    {
        result.push_back(inputString.substr(i * splitLength, splitLength));
    }

    return result;
}

} // namespace Common
} // namespace Kitsune

#endif // STRINGMETHODS_H
