/**
 *  @file    string_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef STRING_METHODS_TEST_H
#define STRING_METHODS_TEST_H

#include <libKitsuneCommon/test.h>

namespace Kitsune
{
namespace Common
{

class StringMethods_Test
        : public Kitsune::Common::Test
{
public:
    StringMethods_Test();

private:
    void splitStringByDelimiter_test();
    void splitStringByLength_test();
};

} // namespace Common
} // namespace Kitsune

#endif // STRINGMETHODS_TEST_H
