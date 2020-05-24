/**
 *  @file       string_methods.cpp
 *
 *  @brief      often used methods for string-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/common_methods/string_methods.h>

namespace Kitsunemimi
{

/**
 * @brief sptrit a string at a specific delimiter
 *
 * @param result reference to the resulting list with the splitted content
 * @param inputString string, which sould be splitted
 * @param delim delimiter to identify the points to split
 */
void
splitStringByDelimiter(std::vector<std::string> &result,
                       const std::string &inputString,
                       const char delim)
{
    // precheck
    if(inputString.length() == 0) {
        return;
    }

    // init variables
    std::stringstream inputStream(inputString);
    std::string item;

    // split
    while(std::getline(inputStream, item, delim))
    {
        result.push_back(item);
    }

    return;
}

/**
 * @brief split a string into part with a maximum length
 *
 * @param result reference to the resulting list with the splitted content
 * @param inputString string, which sould be splitted
 * @param splitLength max length of the single substrings
 */
void
splitStringByLength(std::vector<std::string> &result,
                    const std::string &inputString,
                    const uint64_t splitLength)
{
    const uint64_t numberOfSubstrings = inputString.length() / splitLength;

    // split string
    // number of string +1 to handle leftovers
    for(uint64_t i = 0; i < numberOfSubstrings + 1; i++)
    {
        result.push_back(inputString.substr(i * splitLength, splitLength));
    }

    return;
}

/**
 * @brief replace a substring with another substring
 *
 * @param original original string, which should be changed
 * @param oldSubstring old substring, which should be replace
 * @param newSubstring new substring to replace the old one
 */
void
replaceSubstring(std::string& original,
                 const std::string& oldSubstring,
                 const std::string& newSubstring)
{
    std::string::size_type pos = 0u;
    while((pos = original.find(oldSubstring, pos)) != std::string::npos)
    {
        original.replace(pos, oldSubstring.length(), newSubstring);
        pos += newSubstring.length();
    }
}

/**
 * @brief remove whitespaces from a string
 *
 * @param input input-string, from which the whitespaces should be removed
 */
void
removeWhitespaces(std::string& input)
{
    input.erase(std::remove_if(input.begin(), input.end(), isspace),
                               input.end());
}

/**
 * @brief trim string on the left side
 *
 * @param original string, which should be changed
 * @param chars chars to remove
 */
void
ltrim(std::string& original,
      const std::string &chars)
{
    original.erase(0, original.find_first_not_of(chars));
}

/**
 * @brief trim string on the right side
 *
 * @param original string, which should be changed
 * @param chars chars to remove
 */
void
rtrim(std::string& original,
      const std::string& chars)
{
    original.erase(original.find_last_not_of(chars) + 1);
}

/**
 * @brief trim string on both sides
 *
 * @param original string, which should be changed
 * @param chars chars to remove
 */
void
trim(std::string& original,
     const std::string& chars)
{
    ltrim(original, chars);
    rtrim(original, chars);
}


} // namespace Kitsunemimi
