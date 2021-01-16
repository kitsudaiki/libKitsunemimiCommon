/**
 *  @file    object_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef OBJECT_METHODS_TEST_H
#define OBJECT_METHODS_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class ObjectMethods_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    ObjectMethods_Test();

private:
    void hexlify_test();

    void encodeBase64_test();
    void decodeBase64_test();
};

} // namespace Kitsunemimi

#endif // OBJECT_METHODS_TEST_H
