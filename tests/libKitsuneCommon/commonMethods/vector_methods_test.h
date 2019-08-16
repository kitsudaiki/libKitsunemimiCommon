/**
 *  @file    vectorMethods_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef VECTOR_METHODS_TEST_H
#define VECTOR_METHODS_TEST_H

#include <testing/test.h>

namespace Kitsune
{
namespace Common
{

class TextFile_Test
        : public Kitsune::Common::Test
{
public:
    TextFile_Test();

private:
    void removeEmptyStrings_test();
};

} // namespace Common
} // namespace Kitsune

#endif // VECTORMETHODS_TEST_H
