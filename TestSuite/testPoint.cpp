#include "testPoint.h"
#include <CSELibrary\point.h>

using namespace TestSuite;

void TestPoint::RunTestInternal()
{
    logTestName();
    TestCreation();
    TestMathematicalOperators();
    TestModification();
}

void TestPoint::TestCreation()
{
    CSE::Point point1;
    testExpression(point1.GetX() == 0);
    testExpression(point1.GetY() == 0);

    CSE::Point point2(5, 10);
    testExpression(point2.GetX() == 5);
    testExpression(point2.GetY() == 10);

    CSE::Point point3(point2);
    testExpression(point3.GetX() == 5);
    testExpression(point3.GetY() == 10);

    CSE::Point point4 = point3;
    testExpression(point4.GetX() == 5);
    testExpression(point4.GetY() == 10);
}

void TestPoint::TestMathematicalOperators()
{
    CSE::Point point1(10, 10);
    CSE::Point point2(5, -1);

    point1 += point2;
    testExpression(point1.GetX() == 15);
    testExpression(point1.GetY() == 9);

    point1 -= point2;
    testExpression(point1.GetX() == 10);
    testExpression(point1.GetY() == 10);

    CSE::Point point3 = point1 + point2;
    testExpression(point3.GetX() == 15);
    testExpression(point3.GetY() == 9);

    point3 = point1 - point2;
    testExpression(point3.GetX() == 5);
    testExpression(point3.GetY() == 11);

    testExpression(point1 != point2);
    testExpression((point1 != point1) == false);

    testExpression(point1 == point1);
    testExpression((point1 == point2) == false);
}

void TestPoint::TestModification()
{
    CSE::Point point1;
    point1.SetX(-16);
    point1.SetY(7);
    testExpression(point1.GetX() == -16);
    testExpression(point1.GetY() == 7);
}
