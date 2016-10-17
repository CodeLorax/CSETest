#pragma once
#include "unitTest.h"

namespace TestSuite
{
    // Test class for CSE::Maze
    class TestMaze : public UnitTest
    {
    public:
        TestMaze() {}

    protected:
        virtual void RunTestInternal();

    private:
        void TestOutOfBoundsStart();
        void TestOutOfBoundsEnd();
        void TestStartAtEnd();
        void TestNoBorder();
        void TestPath();
        void TestMultiPath();
        void TestNoEndPath();
        void TestLoopPath();
        void TestFull();
    };
}