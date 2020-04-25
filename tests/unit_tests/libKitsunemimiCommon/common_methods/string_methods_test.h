/**
 *  @file    string_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef STRING_METHODS_TEST_H
#define STRING_METHODS_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class StringMethods_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    StringMethods_Test();

private:
    void splitStringByDelimiter_test();
    void splitStringByLength_test();
    void replaceSubstring_test();
    void removeWhitespaces_test();
};

} // namespace Kitsunemimi

#endif // STRINGMETHODS_TEST_H
