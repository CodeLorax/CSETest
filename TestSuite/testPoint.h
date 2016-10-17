#pragma once
#include "unitTest.h"

namespace TestSuite
{
    // Test class for CSE::Point
    class TestPoint : public UnitTest
    {
    public:
        TestPoint() {}

    protected:
        virtual void RunTestInternal();

    private:
        void TestCreation();
        void TestMathematicalOperators();
        void TestModification();
    };
}