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

class TextFile_Test
        : public Kitsune::CommonTest
{
public:
    TextFile_Test();

private:
    void removeEmptyStrings_test();
};

} // namespace Kitsune

#endif // VECTORMETHODSTEST_HPP
