#pragma once
#include "unitTest.h"

namespace TestSuite
{
    // Test class for CSE::Grid
    class TestGrid : public UnitTest
    {
    public:
        TestGrid() {}

    protected:
        virtual void RunTestInternal();

    private:
        void TestEmptyAllocation();
        void TestSizedAllocation();
        void TestCopyAllocation();
        void TestAssignmentAllocation();
        void TestReadAndSet();
        void TestResize();
        void TestFind();
        void TestContains();
    };
}