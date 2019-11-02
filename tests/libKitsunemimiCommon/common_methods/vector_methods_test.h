/**
 *  @file    vector_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef VECTOR_METHODS_TEST_H
#define VECTOR_METHODS_TEST_H

#include <libKitsunemimiCommon/test.h>

namespace Kitsunemimi
{
namespace Common
{

class TextFile_Test
        : public Kitsunemimi::Common::Test
{
public:
    TextFile_Test();

private:
    void removeEmptyStrings_test();
};

} // namespace Common
} // namespace Kitsunemimi

#endif // VECTORMETHODS_TEST_H
