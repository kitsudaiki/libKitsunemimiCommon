/**
 *  @file    stringMethods_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STRINGMETHODS_TEST_HPP
#define STRINGMETHODS_TEST_HPP

#include <testing/test.hpp>

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
    void splitString_test();
};

} // namespace Common
} // namespace Kitsune

#endif // STRINGMETHODS_TEST_HPP
