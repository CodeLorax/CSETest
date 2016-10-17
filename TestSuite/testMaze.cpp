#include "testMaze.h"
#include <CSELibrary\grid.h>
#include <CSELibrary\maze.h>

using namespace TestSuite;

template <size_t size>
void FillMaze(const int(&data)[size], CSE::Grid<bool>& maze)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < size; ++i)
    {
        maze[x][y] = data[i] == 0 ? false : true;
        if ((i + 1) % maze.GetSizeX() == 0)
        {
            y++;
            x = 0;
        }
        else
        {
            x++;
        }
    }
}

void TestMaze::RunTestInternal()
{
    logTestName();
    TestOutOfBoundsStart();
    TestOutOfBoundsEnd();
    TestStartAtEnd();
    TestNoBorder();
    TestPath();
    TestMultiPath();
    TestNoEndPath();
    TestLoopPath();
    TestFull();
}

void TestMaze::TestOutOfBoundsStart()
{
    const int mazeWidth = 4;
    const int mazeHeight = 4;
    
    const CSE::Point invalidStart(-1, mazeHeight);
    const CSE::Point validEnd;


    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, invalidStart, validEnd) == 0);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, invalidStart, validEnd, longestPath);
    testExpression(longestPath.GetLength() == 0);
}

void TestMaze::TestOutOfBoundsEnd()
{
    const int mazeWidth = 4;
    const int mazeHeight = 4;

    const CSE::Point invalidEnd(mazeWidth, -1);
    const CSE::Point validStart;

    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, validStart, invalidEnd) == 0);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, validStart, invalidEnd, longestPath);
    testExpression(longestPath.GetLength() == 0);
}

void TestMaze::TestStartAtEnd()
{
    const int mazeWidth = 4;
    const int mazeHeight = 4;

    const CSE::Point validPoint(1, 1);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, validPoint, validPoint) == 1);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, validPoint, validPoint, longestPath);
    testExpression(longestPath.GetLength() == 1);
    testExpression(longestPath[0] == validPoint);
}

void TestMaze::TestNoBorder()
{
    const int mazeWidth = 4;
    const int mazeHeight = 4;

    const CSE::Point start(0, 0);
    const CSE::Point end(3, 3);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 1,
        0, 0, 0, 1
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, start, end) == 7);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, start, end, longestPath);
    testExpression(longestPath.GetLength() == 7);

    testExpression(longestPath[0] == CSE::Point(0, 0));
    testExpression(longestPath[1] == CSE::Point(1, 0));
    testExpression(longestPath[2] == CSE::Point(1, 1));
    testExpression(longestPath[3] == CSE::Point(1, 2));
    testExpression(longestPath[4] == CSE::Point(2, 2));
    testExpression(longestPath[5] == CSE::Point(3, 2));
    testExpression(longestPath[6] == CSE::Point(3, 3));
}

void TestMaze::TestPath()
{
    const int mazeWidth = 4;
    const int mazeHeight = 4;

    const CSE::Point start(1, 1);
    const CSE::Point end(2, 2);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, start, end) == 3);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, start, end, longestPath);
    testExpression(longestPath.GetLength() == 3);

    testExpression(longestPath[0] == CSE::Point(1, 1));
    testExpression(longestPath[1] == CSE::Point(1, 2));
    testExpression(longestPath[2] == CSE::Point(2, 2));
}

void TestMaze::TestMultiPath()
{
    const int mazeWidth = 8;
    const int mazeHeight = 5;

    const CSE::Point start(1, 1);
    const CSE::Point end(6, 3);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 0, 0, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0 
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, start, end) == 10);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, start, end, longestPath);
    testExpression(longestPath.GetLength() == 10);

    testExpression(longestPath[0] == CSE::Point(1, 1));
    testExpression(longestPath[1] == CSE::Point(1, 2));
    testExpression(longestPath[2] == CSE::Point(2, 2));
    testExpression(longestPath[3] == CSE::Point(3, 2));
    testExpression(longestPath[4] == CSE::Point(3, 1));
    testExpression(longestPath[5] == CSE::Point(4, 1));
    testExpression(longestPath[6] == CSE::Point(5, 1));
    testExpression(longestPath[7] == CSE::Point(6, 1));
    testExpression(longestPath[8] == CSE::Point(6, 2));
    testExpression(longestPath[9] == CSE::Point(6, 3));
}

void TestMaze::TestNoEndPath()
{
    const int mazeWidth = 8;
    const int mazeHeight = 5;

    const CSE::Point start(1, 1);
    const CSE::Point end(6, 3);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 1, 1, 1, 1, 0,
        0, 1, 1, 0, 0, 0, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, start, end) == 0);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, start, end, longestPath);
    testExpression(longestPath.GetLength() == 0);
}

void TestMaze::TestLoopPath()
{
    const int mazeWidth = 8;
    const int mazeHeight = 5;

    const CSE::Point start(1, 1);
    const CSE::Point end(3, 1);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 0, 1, 0, 1,
        0, 0, 0, 1, 0, 1, 0, 1,
        0, 0, 0, 1, 1, 1, 1, 1
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, start, end) == 17);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, start, end, longestPath);
    testExpression(longestPath.GetLength() == 17);
}

void TestMaze::TestFull()
{
    const int mazeWidth = 4;
    const int mazeHeight = 4;

    const CSE::Point start(0, 1);
    const CSE::Point end(3, 3);

    const int mazeData[mazeHeight * mazeWidth] =
    {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
    };

    CSE::Grid<bool> maze(mazeWidth, mazeHeight);
    FillMaze(mazeData, maze);

    testExpression(CSE::Maze::LongestPathSteps(maze, start, end) == 16);

    CSE::List<CSE::Point> longestPath;
    CSE::Maze::LongestPath(maze, start, end, longestPath);
    testExpression(longestPath.GetLength() == 16);
}