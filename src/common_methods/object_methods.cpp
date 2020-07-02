/**
 *  @file       object_methods.cpp
 *
 *  @brief      often used methods for object-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/common_methods/object_methods.h>

namespace Kitsunemimi
{

/**
 * @brief hexlify an object into a string
 *
 * @param object pointer to the object, which should be hexlified
 * @param size size of the object
 *
 * @return hex-version of the input-object as string
 */
void
hexlify(std::string &outputString,
        void* object,
        const uint64_t size)
{
    uint8_t* bytestream = static_cast<uint8_t*>(object);
    std::stringstream stream;

    // iterate over all bytes of the object
    for(uint64_t i = size; i != 0; i--)
    {
        // special rul to fix the length
        if(bytestream[i - 1] < 16) {
            stream << "0";
        }
        stream << std::hex << (int)bytestream[i - 1];
    }

    outputString = stream.str();
}

} // namespace Kitsunemimi
