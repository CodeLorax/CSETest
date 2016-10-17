#pragma once
#include "math.h"
#include "point.h"
#include <assert.h>
#include <string.h>

namespace CSE
{
    // A resizeable Grid class.
    // The grid will not resize unless asked to do so, during resize elements are presevered if they fit with the new size of the grid.
    template <class T>
    class Grid
    {
    public:
        // Value of X/Y values in the Point object return from a Find call when the object cannot be found
        static const int InvalidIndex = -1;

        // Max size allowed for an array
        static const unsigned int MaxSize = 0xFFF;

        // Standard construction, grid will be sized to 0 in each dimension
        Grid();
        
        // Construct a new object of the sizes provided
        Grid(unsigned int sizeX, unsigned int sizeY);

        // Copy constructor which will take on the size and elements within the grid
        // it is being copied from.
        Grid(const Grid<T>& grid);

        // Destructor. This will clean up only the memory used to store the grid itself.
        // It will not clean up the elements within the grid.
        ~Grid();

        // Assignment constructor which will take on the size and elements within the grid
        // it is being copied from.
        Grid<T> operator=(const Grid<T>& grid) const;

        // Sub class needed in order to allow for [][] operations to be performed on the grid.
        class OperatorProxy
        {
        public:
            OperatorProxy(Grid<T>& grid, unsigned int x) : m_grid(grid), m_x(x) {}
            OperatorProxy(const Grid<T>& grid, unsigned int x) : m_grid(grid), m_x(x) {}

            const T& operator[] (unsigned int y) const;
            T& operator[] (unsigned int y);

        private:
            unsigned int m_x;
            const Grid<T>& m_grid;
        };

        OperatorProxy operator[](unsigned int x) { return OperatorProxy(*this, x); }
        const OperatorProxy operator[](unsigned int x) const { return OperatorProxy(*this, x); }

        // Set the element in the array.  Out of bounds sets are ignored
        void Set(unsigned int x, unsigned int y, T value);

        // Resize the grid.  This will carry over elements from the old grid if they are still present.
        void Resize(unsigned int sizeX, unsigned int sizeY);

        // Check if an element can be found in the grid.
        bool Contains(const T& value) const;

        // Get the x and y indexes of the element in the grid.
        // If the element cannot be found, a point with values of InvalidIndex is returned
        Point Find(const T& value) const;

        inline unsigned int GetSizeX() const { return m_sizeX; }
        inline unsigned int GetSizeY() const { return m_sizeY; }

    private:
        void CopyToGrid(T* source, int sourceSizeX, int sourceSizeY, T* destination, int destionationSizeX, int destinationSizeY);

        T* m_data;

        unsigned int m_sizeX;
        unsigned int m_sizeY;
    };

    template <class T>
    const T& Grid<T>::OperatorProxy::operator[](unsigned int y) const
    {
        assert(m_x < m_grid.m_sizeX || y < m_grid.m_sizeY);
        return m_grid.m_data[m_x * m_grid.m_sizeY + y];
    }

    template <class T>
    T& Grid<T>::OperatorProxy::operator[](unsigned int y)
    {
        assert(m_x < m_grid.m_sizeX || y < m_grid.m_sizeY);
        return m_grid.m_data[m_x * m_grid.m_sizeY + y];
    }

    template <class T>
    Grid<T>::Grid()
        : Grid(0, 0)
    {

    }

    template <class T>
    Grid<T>::Grid(unsigned int sizeX, unsigned int sizeY)
        : m_data(NULL)
    {
        Resize(sizeX, sizeY);
    }

    template <class T>
    Grid<T>::Grid(const Grid<T>& grid)
        : Grid(grid.m_sizeX, grid.m_sizeY)
    {
        CopyToGrid(grid.m_data, grid.m_sizeX, grid.m_sizeY, m_data, m_sizeX, m_sizeY);
    }

    template <class T>
    Grid<T>::~Grid()
    {
        if (m_data != NULL)
        {
            delete[] m_data;
        }
    }

    template <class T>
    Grid<T> Grid<T>::operator=(const Grid<T>& grid) const
    {
        return new Grid(grid);
    }

    template <class T>
    void Grid<T>::Set(unsigned int x, unsigned int y, T value)
    {
        if (x < m_sizeX && y < m_sizeY)
        {
            m_data[x * m_sizeY + y] = value;
        }
    }

    template <class T>
    void Grid<T>::Resize(unsigned int sizeX, unsigned int sizeY)
    {
        T* newData = NULL;
        if (sizeX != 0 && sizeY != 0)
        {
            // The new size needs memory allocated to it. Create the data
            // here, initialize it, and copy over old values
            newData = new T[sizeX * sizeY];
            memset(newData, 0, sizeof(T) * sizeX * sizeY);
            CopyToGrid(m_data, m_sizeX, m_sizeY, newData, sizeX, sizeY);
        }

        if (m_data != NULL)
        {
            delete[] m_data;
        }

        m_data = newData;
        m_sizeX = sizeX;
        m_sizeY = sizeY;
    }

    template <class T>
    void Grid<T>::CopyToGrid(T* source, int sourceSizeX, int sourceSizeY, T* destination, int destinationSizeX, int destinationSizeY)
    {
        if (source == NULL || destination == NULL)
        {
            return;
        }

        int rowsToCopy = Math::Min(sourceSizeX, destinationSizeX);
        int columnsToCopy = Math::Min(sourceSizeY, destinationSizeY);
        for (int i = 0; i < rowsToCopy; ++i)
        {
            memcpy(&destination[i * destinationSizeY], &source[i * sourceSizeY], sizeof(T) * columnsToCopy);
        }
    }

    template <class T>
    bool Grid<T>::Contains(const T& value) const
    {
        Point location = Find(value);
        return location.GetX() != InvalidIndex;
    }

    template <class T>
    Point Grid<T>::Find(const T& value) const
    {
        for (unsigned int x = 0; x < m_sizeX; x++)
        {
            for (unsigned int y = 0; y < m_sizeY; y++)
            {
                if (m_data[x * m_sizeY + y] == value)
                {
                    return Point(x, y);
                }
            }
        }

        return Point(InvalidIndex, InvalidIndex);
    }
}