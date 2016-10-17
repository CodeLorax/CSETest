#include "maze.h"

using namespace CSE;

int Maze::LongestPathSteps(const Grid<bool>& maze, const Point& start, const Point& end)
{
    List<Point> longestPath;
    LongestPath(maze, start, end, longestPath);
    return longestPath.GetLength();
}

void Maze::LongestPath(const Grid<bool>& maze, const Point& start, const Point& end, List<Point>& longestPath)
{
    longestPath.Clear();

    if (maze.GetSizeX() == 0 || 
        maze.GetSizeY() == 0 ||
        IsPointOutOfBounds(maze, start) ||
        IsPointOutOfBounds(maze, end))
    {
        return;
    }

    List<Point> currentSteps(maze.GetSizeX() * maze.GetSizeY());
    Grid<bool> visitedSteps(maze.GetSizeX(), maze.GetSizeY());
    CheckLocation(maze, visitedSteps, start, end, currentSteps, longestPath);
}

void Maze::CheckLocation(const Grid<bool>& maze, Grid<bool>& visitedSteps, const Point& currentLocation, const Point& end, List<Point>& currentSteps, List<Point>& longestSolution)
{
    if (IsPointOutOfBounds(maze, currentLocation) ||
        maze[currentLocation.GetX()][currentLocation.GetY()] == false)
    {
        // new position is not traversable
        return;
    }
    else if (visitedSteps[currentLocation.GetX()][currentLocation.GetY()])
    {
        // location has already been visited
        return;
    }

    visitedSteps[currentLocation.GetX()][currentLocation.GetY()] = true;
    currentSteps.Add(currentLocation);

    if (currentLocation == end)
    {
        if (currentSteps.GetLength() > longestSolution.GetLength())
        {
            longestSolution = currentSteps;
        }
    }
    else
    {
        Point up(currentLocation.GetX(), currentLocation.GetY() - 1);
        CheckLocation(maze, visitedSteps, up, end, currentSteps, longestSolution);

        Point down(currentLocation.GetX(), currentLocation.GetY() + 1);
        CheckLocation(maze, visitedSteps, down, end, currentSteps, longestSolution);

        Point left(currentLocation.GetX() - 1, currentLocation.GetY());
        CheckLocation(maze, visitedSteps, left, end, currentSteps, longestSolution);

        Point right(currentLocation.GetX() + 1, currentLocation.GetY());
        CheckLocation(maze, visitedSteps, right, end, currentSteps, longestSolution);
    }

    visitedSteps[currentLocation.GetX()][currentLocation.GetY()] = false;
    currentSteps.Remove(currentLocation);
}

bool Maze::IsPointOutOfBounds(const Grid<bool>& maze, const Point& point)
{
    return point.GetX() < 0 || 
        point.GetY() < 0 || 
        static_cast<unsigned int>(point.GetX()) >= maze.GetSizeX() || 
        static_cast<unsigned int>(point.GetY()) >= maze.GetSizeY();
}
