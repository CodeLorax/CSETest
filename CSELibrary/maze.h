#pragma once
#include "grid.h"
#include "list.h"
namespace CSE
{
    // Utility functions for processesing maze objects.  A maze is defined as a grid where a path location is
    // equal to true and a wall is false.  A maze is meant to be traversed from start to finish where valid 
    // traversal is left, right, up, and down (not horizontal).  The maze is meant to be traversed from the
    // start to end, while never traversing twice in the same slot
    class Maze
    {
    public:
        // Get the number of steps which represents the longest path from start to end.
        //
        // @param maze The maze to traverse
        // @param start The starting point in the maze
        // @param end The ending point in the maze
        // @return The number of times movement is required to get from start to end include start point
        static int LongestPathSteps(const Grid<bool>& maze, const Point& start, const Point& end);

        // Get all the steps for the longest path through the maze that will go from start to end.
        //
        // @param maze The maze to traverse
        // @param start The starting point in the maze
        // @param end The ending point in the maze
        // @param longestPath The filled in list of points from start to end.  If this list is empty the maze cannot be solved.
        static void LongestPath(const Grid<bool>& maze, const Point& start, const Point& end, List<Point>& longestPath);

    private:
        static bool Maze::IsPointOutOfBounds(const Grid<bool>& maze, const Point& point);

        // Recursive helper function to find the longest path through the maze.
        //
        // @param maze The maze to traverse
        // @param visitedSteps grid marking which parts of the maze have been visited
        // @param currentLocation the position being checked
        // @param end The end goal
        // @param currentSteps The current steps taken so far
        // @param longestSolution The list to fill with the path to the longest solution through the maze
        static void CheckLocation(const Grid<bool>& maze, Grid<bool>& visitedSteps, const Point& currentLocation, const Point& end, List<Point>& currentSteps, List<Point>& longestSolution);
    };
}