#pragma once
#include "unitTest.h"

namespace TestSuite
{
    // Test class for CSE::List
    class TestList : public UnitTest
    {
    public:
        TestList() {}

    protected:
        virtual void RunTestInternal();

    private:
        void CreateDefaultSizeNonSortedList();
        void CreateSpecificSizeNonSortedList();
        void CreateSortedList();
        void CopyList();
        void AssignList();
        void AddElementToList();
        void AddMultipleElementsToList();
        void RemoveEntryFromList();
        void RemoveFirstCopyOfEntryFromList();
        void RemoveElementThatDoesNotExist();
        void RemoveFromListSorted();
        void RemoveAtFromListNonSorted();
        void RemoveAtFromListSorted();
        void RemoveAtOutOfBounds();
        void RemoveAllFromList();
        void AccessLastEntry();
        void EmptyCheck();
        void SortedCheck();
        void ListGrowsInSize();
        void ClearList();
    };
}