/**
 *  @file    vectorMethodsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef VECTORMETHODSTEST_H
#define VECTORMETHODSTEST_H

#include <testing/commonTest.hpp>

namespace Kitsune
{

class VectorMethodsTest : public Kitsune::CommonTest
{
public:
    VectorMethodsTest();

private:
    void testRemoveEmptyStrings();
};

} // namespace Kitsune

#endif // VECTORMETHODSTEST_H
