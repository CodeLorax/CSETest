#pragma once
#include <string>

namespace TestSuite
{
    class UnitTest
    {
    public:
        UnitTest();
        bool RunTest();

    protected:
        virtual void RunTestInternal() = 0;
        void FailCurrentTest(const std::string& expression, const std::string& file, int line);
        void LogTestName(const std::string& fileName);

    private:
        // Protect against copy/assignment
        UnitTest(const UnitTest&);
        UnitTest& operator=(const UnitTest&);

        bool m_success;
    };

#define testExpression(Expression)                                      \
    {                                                                   \
        if (!(Expression))                                              \
        {                                                               \
            FailCurrentTest(#Expression, __FILE__, __LINE__);           \
        }                                                               \
    }      

#define logTestName() { LogTestName(__FILE__); }
}