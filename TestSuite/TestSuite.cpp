#include <iostream>
#include "CSELibrary/math.h"
#include "unitTest.h"
#include "testMath.h"
#include "testList.h"
#include "testPoint.h"
#include "testGrid.h"
#include "testMaze.h"

using namespace TestSuite;

UnitTest* Tests[] =
{
    new TestMath(),
    new TestList(),
    new TestPoint(),
    new TestGrid(),
    new TestMaze()
};

int main()
{
    std::cout << "Running Test Suite\nTests:\n";

    int successCount = 0;
    int failureCount = 0;
    int testCount = CSE::Math::ArraySize(Tests);
    for (int i = 0; i < testCount; ++i)
    {
        if (Tests[i]->RunTest())
        {
            successCount++;
        }
        else
        {
            failureCount++;
        }
    }

    std::cout << "Summary\n\tSuccess: " << successCount << " Failure: " << failureCount << " Total: " << successCount + failureCount;

    std::cin.get();
    return 0;
}
