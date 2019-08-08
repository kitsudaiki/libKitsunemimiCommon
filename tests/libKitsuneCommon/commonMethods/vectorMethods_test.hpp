/**
 *  @file    vectorMethods_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef VECTORMETHODS_TEST_HPP
#define VECTORMETHODS_TEST_HPP

#include <testing/test.hpp>

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

#endif // VECTORMETHODS_TEST_HPP
