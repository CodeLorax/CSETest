#include "testMath.h"
#include "unitTest.h"
#include <CSELibrary/math.h>

using namespace TestSuite;

void TestMath::RunTestInternal()
{
    logTestName();
    TestMin();
    TestMax();
    TestClamp();
    TestArraySize();
}

void TestMath::TestMin()
{
    testExpression(CSE::Math::Min(1, 1) == 1);
    testExpression(CSE::Math::Min(-10, -10) == -10);
    testExpression(CSE::Math::Min(5, 8) == 5);
    testExpression(CSE::Math::Min(-5, 8) == -5);
    testExpression(CSE::Math::Min(6.7F, 10.666F) == 6.7F);
}

void TestMath::TestMax()
{
    testExpression(CSE::Math::Max(1, 1) == 1);
    testExpression(CSE::Math::Max(-10, -10) == -10);
    testExpression(CSE::Math::Max(5, 8) == 8);
    testExpression(CSE::Math::Max(-5, 8) == 8);
    testExpression(CSE::Math::Max(6.7F, 10.666F) == 10.666F);
}

void TestMath::TestClamp()
{
    testExpression(CSE::Math::Clamp(1, 1, 10) == 1);
    testExpression(CSE::Math::Clamp(10, 1, 10) == 10);
    testExpression(CSE::Math::Clamp(-5, -3, 10) == -3);
    testExpression(CSE::Math::Clamp(15, -3, 10) == 10);
    testExpression(CSE::Math::Clamp(7.7F, 7.8F, 11.0F) == 7.8F);
}

void TestMath::TestArraySize()
{
    int testArray1[] = { 1, 2, 3 };
    char* testArray2[5];
    testExpression(CSE::Math::ArraySize(testArray1) == 3);
    testExpression(CSE::Math::ArraySize(testArray2) == 5);
}
