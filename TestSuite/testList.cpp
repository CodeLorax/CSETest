#include "testList.h"
#include <CSELibrary\list.h>
#include <iostream>
#include <string>

using namespace TestSuite;

void TestList::RunTestInternal()
{
    logTestName();

    CreateDefaultSizeNonSortedList();
    CreateSpecificSizeNonSortedList();
    CreateSortedList();
    CopyList();
    AssignList();
    AddElementToList();
    AddMultipleElementsToList();
    RemoveEntryFromList();
    RemoveFirstCopyOfEntryFromList();
    RemoveElementThatDoesNotExist();
    RemoveFromListSorted();
    RemoveAtFromListNonSorted();
    RemoveAtFromListSorted();
    RemoveAtOutOfBounds();
    RemoveAllFromList();
    AccessLastEntry();
    EmptyCheck();
    SortedCheck();
    ListGrowsInSize();
    ClearList();
}

void TestList::CreateDefaultSizeNonSortedList()
{
    CSE::List<int> list;
    testExpression(list.GetLength() == 0);
}

void TestList::CreateSpecificSizeNonSortedList()
{
    const int expectedSize = 20;
    CSE::List<int> list(expectedSize);
    testExpression(list.GetLength() == 0);
}

void TestList::CreateSortedList()
{
    const int expectedSize = 20;
    CSE::List<int> list(expectedSize, true);
    testExpression(list.GetLength() == 0);
}

void TestList::CopyList()
{
    CSE::List<int> listA;
    listA.Add(1);
    listA.Add(2);
    listA.Add(3);

    CSE::List<int> listB(listA);

    testExpression(listB[0] == listA[0]);
    testExpression(listB[1] == listA[1]);
    testExpression(listB[2] == listA[2]);

    testExpression(listB.GetLength() == 3);
}

void TestList::AssignList()
{
    CSE::List<int> listA;
    listA.Add(1);
    listA.Add(2);
    listA.Add(3);

    CSE::List<int> listB(10, true);
    
    listB = listA;
    testExpression(listB[0] == listA[0]);
    testExpression(listB[1] == listA[1]);
    testExpression(listB[2] == listA[2]);

    testExpression(listB.GetLength() == 3);
    testExpression(listB.IsSorted() == false);
}

void TestList::AddElementToList()
{
    const int expectedResult = 15;
    CSE::List<int> list;
    list.Add(expectedResult);

    testExpression(list[0] == expectedResult);
    testExpression(list.GetLength() == 1);
}

void TestList::AddMultipleElementsToList()
{
    CSE::List<int> list;
    list.Add(10);
    list.Add(20);

    testExpression(list[0] == 10);
    testExpression(list[1] == 20);

    testExpression(list.GetLength() == 2);
}

void TestList::RemoveEntryFromList()
{
    CSE::List<int> list;
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    list.Remove(20); // last element takes the place of the removed one, making new order {10, 40, 30}
    testExpression(list[0] == 10);
    testExpression(list[1] == 40);
    testExpression(list[2] == 30);

    testExpression(list.GetLength() == 3);
}

void TestList::RemoveFirstCopyOfEntryFromList()
{
    CSE::List<int> list;
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(20);
    list.Add(40);

    list.Remove(20);

    testExpression(list[0] == 10);
    testExpression(list[1] == 40);
    testExpression(list[2] == 30);
    testExpression(list[3] == 20);

    testExpression(list.GetLength() == 4);
}

void TestList::RemoveElementThatDoesNotExist()
{
    CSE::List<int> list;
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    list.Remove(50);

    testExpression(list[0] == 10);
    testExpression(list[1] == 20);
    testExpression(list[2] == 30);
    testExpression(list[3] == 40);

    testExpression(list.GetLength() == 4);
}

void TestList::RemoveFromListSorted()
{
    CSE::List<int> list(0, true);
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    list.Remove(20);

    testExpression(list[0] == 10);
    testExpression(list[1] == 30);
    testExpression(list[2] == 40);

    testExpression(list.GetLength() == 3);
}

void TestList::RemoveAtFromListNonSorted()
{
    CSE::List<int> list(0, false);
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    list.RemoveAt(1);

    testExpression(list[0] == 10);
    testExpression(list[1] == 40);
    testExpression(list[2] == 30);

    testExpression(list.GetLength() == 3);
}

void TestList::RemoveAtFromListSorted()
{
    CSE::List<int> list(0, true);
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    list.RemoveAt(1);

    testExpression(list[0] == 10);
    testExpression(list[1] == 30);
    testExpression(list[2] == 40);

    testExpression(list.GetLength() == 3);
}

void TestList::RemoveAtOutOfBounds()
{
    CSE::List<int> list(0, false);
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    list.RemoveAt(-1);
    list.RemoveAt(4);
    list.RemoveAt(100);

    testExpression(list[0] == 10);
    testExpression(list[1] == 20);
    testExpression(list[2] == 30);
    testExpression(list[3] == 40);

    testExpression(list.GetLength() == 4);
}

void TestList::RemoveAllFromList()
{
    CSE::List<int> list(0, false);
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    while (!list.IsEmpty())
    {
        list.RemoveAt(list.GetLength() - 1);
    }

    testExpression(list.GetLength() == 0);
    testExpression(list.IsEmpty() == true);
}

void TestList::AccessLastEntry()
{
    CSE::List<int> list(0, false);
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);

    testExpression(list.GetLast() == 40);
}

void TestList::EmptyCheck()
{
    CSE::List<int> list(0, false);
    testExpression(list.IsEmpty() == true);
    list.Add(1);
    testExpression(list.IsEmpty() == false);
    list.RemoveAt(0);
    testExpression(list.IsEmpty() == true);
}

void TestList::ListGrowsInSize()
{
    const int listSize = 100;
    CSE::List<int> list(0, false);

    for (int i = 0; i < listSize; ++i)
    {
        list.Add(i);
    }

    for (int i = 0; i < listSize; ++i)
    {
        testExpression(list[i] == i);
    }

    testExpression(list.GetLength() == listSize);
}

void TestList::SortedCheck()
{
    CSE::List<int> listA(0, false);
    testExpression(listA.IsSorted() == false);

    CSE::List<int> listB(0, true);
    testExpression(listB.IsSorted() == true);

    CSE::List<int> listC(listB);
    testExpression(listC.IsSorted() == true);

    CSE::List<int> listD(listA);
    testExpression(listD.IsSorted() == false);

    CSE::List<int> listE = listA;
    testExpression(listE.IsSorted() == false);

    CSE::List<int> listF = listB;
    testExpression(listF.IsSorted() == true);
}

void TestList::ClearList()
{
    CSE::List<bool> list;
    list.Add(1);
    list.Add(1);
    list.Add(1);
    testExpression(list.GetLength() == 3);

    list.Clear();
    testExpression(list.GetLength() == 0);

    list.Add(1);
    testExpression(list.GetLength() == 1);
}