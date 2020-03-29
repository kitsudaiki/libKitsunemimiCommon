/**
 *  @file    vector_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef VECTOR_METHODS_TEST_H
#define VECTOR_METHODS_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class TextFile_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    TextFile_Test();

private:
    void removeEmptyStrings_test();
};

} // namespace Kitsunemimi

#endif // VECTORMETHODS_TEST_H
