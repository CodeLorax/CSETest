#pragma once
#include "unitTest.h"

namespace TestSuite
{
    // Test class for CSE::Math
    class TestMath : public UnitTest
    {
    public:
        TestMath() {}

    protected:
        virtual void RunTestInternal();

    private:
        void TestMin();
        void TestMax();
        void TestClamp();
        void TestArraySize();
    };
}