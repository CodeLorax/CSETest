#include "unitTest.h"
#include <iostream>

using namespace TestSuite;

UnitTest::UnitTest()
    : m_success(true)
{
}

bool UnitTest::RunTest()
{
    RunTestInternal();
    return m_success;
}

void UnitTest::FailCurrentTest(const std::string& expression, const std::string& file, int line)
{
    std::cout << "***ERROR:***\nExpression:" << expression << "\nFile: " << file << "\nLn: " << line << "\n";
    m_success = false;
}

void UnitTest::LogTestName(const std::string& fileName)
{
    std::string className = fileName;
    size_t index = fileName.rfind('\\');
    if (index != -1)
    {
        className = fileName.substr(index + 1, fileName.size() - index - 1);
    }

    std::cout << "   " << className << "\n";
}