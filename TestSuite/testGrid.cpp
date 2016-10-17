#include "testGrid.h"
#include <CSELibrary\grid.h>

using namespace TestSuite;

void TestGrid::RunTestInternal()
{
    logTestName();
    TestEmptyAllocation();
    TestSizedAllocation();
    TestCopyAllocation();
    TestAssignmentAllocation();
    TestReadAndSet();
    TestResize();
    TestFind();
    TestContains();
}

void TestGrid::TestEmptyAllocation()
{
    CSE::Grid<int> grid;
    testExpression(grid.GetSizeX() == 0);
    testExpression(grid.GetSizeY() == 0);
}

void TestGrid::TestSizedAllocation()
{
    CSE::Grid<int> grid(5, 4);
    testExpression(grid.GetSizeX() == 5);
    testExpression(grid.GetSizeY() == 4);
    testExpression(grid[1][2] == 0);

    grid.Set(1, 2, 5);
    testExpression(grid[1][2] == 5);
}

void TestGrid::TestCopyAllocation()
{
    CSE::Grid<int> emptyGrid;
    CSE::Grid<int> fullGrid(10, 11);
    fullGrid.Set(6, 3, 100);

    CSE::Grid<int> copyFromEmpty(emptyGrid);
    CSE::Grid<int> copyFromFull(fullGrid);

    testExpression(copyFromEmpty.GetSizeX() == 0);
    testExpression(copyFromEmpty.GetSizeY() == 0);
    testExpression(copyFromFull.GetSizeX() == 10);
    testExpression(copyFromFull.GetSizeY() == 11);
    testExpression(copyFromFull[6][3] == 100);
}

void TestGrid::TestAssignmentAllocation()
{
    CSE::Grid<int> emptyGrid;
    CSE::Grid<int> fullGrid(10, 11);
    fullGrid.Set(6, 3, 100);

    CSE::Grid<int> copyFromEmpty = emptyGrid;
    CSE::Grid<int> copyFromFull = fullGrid;

    testExpression(copyFromEmpty.GetSizeX() == 0);
    testExpression(copyFromEmpty.GetSizeY() == 0);
    testExpression(copyFromFull.GetSizeX() == 10);
    testExpression(copyFromFull.GetSizeY() == 11);
    testExpression(copyFromFull[6][3] == 100);
}

void TestGrid::TestReadAndSet()
{
    const int sizeX = 10;
    const int sizeY = 5;
    CSE::Grid<CSE::Point> fullGrid(sizeX, sizeY);
    
    for (int x = 0; x < sizeX; ++x)
    {
        for (int y = 0; y < sizeY; ++y)
        {
            fullGrid.Set(x, y, CSE::Point(x, y));
        }
    }

    for (int x = 0; x < sizeX; ++x)
    {
        for (int y = 0; y < sizeY; ++y)
        {
            testExpression(fullGrid[x][y] == CSE::Point(x, y));
        }
    }
}

void TestGrid::TestResize()
{
    CSE::Grid<int> grid;
    grid.Resize(5, 10);
    grid[0][0] = 8;
    grid[0][6] = 10;
    grid[2][2] = -10;

    grid.Resize(5, 10);
    testExpression(grid[0][0] == 8);
    testExpression(grid[0][6] == 10);
    testExpression(grid[2][2] == -10);
    testExpression(grid.GetSizeX() == 5);
    testExpression(grid.GetSizeY() == 10);

    grid.Resize(100, 100);
    testExpression(grid[0][0] == 8);
    testExpression(grid[0][6] == 10);
    testExpression(grid[2][2] == -10);
    testExpression(grid.GetSizeX() == 100);
    testExpression(grid.GetSizeY() == 100);

    grid.Resize(1, 1);
    testExpression(grid[0][0] == 8);
    testExpression(grid.GetSizeX() == 1);
    testExpression(grid.GetSizeY() == 1);

    grid.Resize(0, 0);
    testExpression(grid.GetSizeX() == 0);
    testExpression(grid.GetSizeY() == 0);
}

void TestGrid::TestFind()
{
    CSE::Grid<int> emptyGrid;
    testExpression(emptyGrid.Find(20) == CSE::Point(CSE::Grid<int>::InvalidIndex, CSE::Grid<int>::InvalidIndex));

    CSE::Grid<int> grid(10, 10);
    grid[5][5] = 20;

    testExpression(grid.Find(20) == CSE::Point(5, 5));
    testExpression(grid.Find(25) == CSE::Point(CSE::Grid<int>::InvalidIndex, CSE::Grid<int>::InvalidIndex));
}

void TestGrid::TestContains()
{
    CSE::Grid<int> emptyGrid;
    testExpression(emptyGrid.Contains(20) == false);

    CSE::Grid<int> grid(10, 10);
    grid[5][5] = 20;

    testExpression(grid.Contains(20) == true);
    testExpression(grid.Contains(25) == false);
}