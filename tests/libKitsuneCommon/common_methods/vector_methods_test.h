/**
 *  @file    vector_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef VECTOR_METHODS_TEST_H
#define VECTOR_METHODS_TEST_H

#include <testing/unit_test.h>

namespace Kitsune
{
namespace Common
{

class TextFile_Test
        : public Kitsune::Common::UnitTest
{
public:
    TextFile_Test();

private:
    void removeEmptyStrings_test();
};

} // namespace Common
} // namespace Kitsune

#endif // VECTORMETHODS_TEST_H
