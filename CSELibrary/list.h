#pragma once
#ifndef MOOSE_LIST_H_
#define MOOSE_LIST_H_

#include "Math.h"

namespace CSE
{
    // Auto resizing list, granting several nice additions not available
    // to a simple c++ array.
    //
    // When the non-sorted option is used, removing an element from the list will
    // replace the item with the last element in the list.  If order is not important
    // it is slightly more efficient to use a non-sorted list.
    template <class T>
    class List
    {
    public:
        // Create a non-sorted list of the default size
        List();

        // Create a non-sorted list of the provided starting size
        //
        // @param defaultSize The size to start the list at
        List(int defaultSize);

        // Create a list of the provided starting size
        //
        // @param defaultSize The size to start the list at
        // @param sorted If true the list will retain its order when items are removed
        List(int defaultSize, bool sorted);

        // Copy constructor for list
        //
        // @param list the list to copy
        List(const List<T>& list);

        // Assignment constructor for list
        //
        // @param list the list to copy
        List<T>& operator=(const List<T>& list);

        // standard destruction
        ~List();

        // Const access operator for the list
        const T& operator[](const int i) const;

        // Access operator for the list
        T& operator[](const int i);

        // Add a new entry to the list
        //
        // @param newEntry The entry to add
        void Add(T newEntry);

        // Remove and entry from the list. Only the first matching entry will be removed
        //
        // @param removeEntry The entry to remove
        // @return True if the entry is found and removed
        bool Remove(const T removeEntry);

        // Remove the entry at the provided index
        //
        // @param index what index to remove at
        void RemoveAt(unsigned int index);

        // Remove all entries from the list
        void Clear();

        // Get the last entry in the list
        //
        // @param the last entry.
        T GetLast() const;

        // Get the current length of the array
        //
        // @return the array length.
        inline int GetLength() const { return m_fillSize; }

        // Check if this list keeps itself sorted on removal
        //
        // @return True if the list will keep itself sorted after removal of an element
        inline bool IsSorted() const { return m_sorted; }

        // Check if there is at least one entry in the list
        //
        // @return true if there is at least one entry
        inline bool IsEmpty() const { return m_fillSize == 0; }

    private:
        T* m_array;
        int m_arraySize;
        int m_fillSize;
        bool m_sorted;

        static const int s_defaultSize = 8;
    };


    template <class T>
    List<T>::List()
        : List(s_defaultSize, false)
    {
    }

    template <class T>
    List<T>::List(int defaultSize)
        : List(defaultSize, false)
    {
    }

    template <class T>
    List<T>::List(int defaultSize, bool sorted)
        : m_fillSize(0),
        m_sorted(sorted)
    {
        defaultSize = Math::Max(defaultSize, s_defaultSize);
        m_arraySize = defaultSize;
        m_array = new T[defaultSize];
    }

    template <class T>
    List<T>::List(const List<T>& list)
        : List(list.m_arraySize, list.m_sorted)
    {
        m_fillSize = list.m_fillSize;

        if (m_fillSize != 0)
        {
            memcpy(m_array, list.m_array, sizeof(T) * m_fillSize);
        }
    }

    template <class T>
    List<T>& List<T>::operator=(const List<T>& list)
    {
        if (this == &list)
        {
            return *this;
        }

        if (m_array != NULL)
        {
            delete[] m_array;
            m_array = NULL;
        }

        m_arraySize = list.m_arraySize;
        m_fillSize = list.m_fillSize;
        m_sorted = list.m_sorted;

        if (m_arraySize != NULL)
        {
            m_array = new T[list.m_arraySize];
            memcpy(m_array, list.m_array, sizeof(T) * m_fillSize);
        }

        return *this;
    }

    template <class T>
    List<T>::~List()
    {
        delete m_array;
    }

    template <class T>
    const T& List<T>::operator[](const int i) const
    {
        return m_array[i];
    }

    template <class T>
    T& List<T>::operator[](const int i)
    {
        return m_array[i];
    }

    template <class T>
    void List<T>::Add(T newEntry)
    {
        if (m_fillSize == m_arraySize)
        {
            m_arraySize *= 2;
            T* newList = new T[m_arraySize];
            memcpy(newList, m_array, sizeof(T) * m_fillSize);
            delete m_array;
            m_array = newList;
        }

        m_array[m_fillSize] = newEntry;
        m_fillSize++;
    }

    template <class T>
    bool List<T>::Remove(const T removeEntry)
    {
        for (int i = 0; i < m_fillSize; ++i)
        {
            if (m_array[i] == removeEntry)
            {
                RemoveAt(i);
                return true;
            }
        }

        return false;
    }

    template <class T>
    void List<T>::RemoveAt(unsigned int index)
    {
        // don't remove out of bounds data
        if (index >= static_cast<unsigned int>(m_fillSize))
        {
            return;
        }

        if (index != m_fillSize - 1)
        {
            if (m_sorted == true)
            {
                memcpy(&m_array[index], &m_array[index + 1], sizeof(T) * (m_fillSize - 1 - index));
            }
            else
            {
                m_array[index] = m_array[m_fillSize - 1];
            }
        }

        m_fillSize--;
    }

    template <class T>
    T List<T>::GetLast() const
    {
        return m_fillSize == 0 ? NULL : m_array[m_fillSize - 1];
    }

    template <class T>
    void List<T>::Clear()
    {
        m_fillSize = 0;
    }

}

#endif