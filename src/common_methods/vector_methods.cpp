/**
 *  @file       vector_methods.cpp
 *
 *  @brief      often used methods for vector-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/common_methods/vector_methods.h>

namespace Kitsunemimi
{

/**
 * remove from a vector of strings all entries, which contains only a empty string
 */
void
removeEmptyStrings(std::vector<std::string> &inputVector)
{
    // remove items
    inputVector.erase(std::remove_if(inputVector.begin(),
                                     inputVector.end(),
                                     std::mem_fun_ref(&std::string::empty)),
                      inputVector.end());
}

} // namespace Kitsunemimi
