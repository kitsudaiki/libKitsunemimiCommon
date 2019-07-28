/**
 *  @file    vectorMethods_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef VECTORMETHODSTEST_HPP
#define VECTORMETHODSTEST_HPP

#include <testing/commonTest.hpp>

namespace Kitsune
{

class VectorMethods_Test
        : public Kitsune::CommonTest
{
public:
    VectorMethods_Test();

private:
    void testRemoveEmptyStrings();
};

} // namespace Kitsune

#endif // VECTORMETHODSTEST_HPP
