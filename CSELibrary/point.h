#pragma once
namespace CSE
{
    // Point class with an X and Y value.
    class Point
    {
    public:
        Point() : m_x(0), m_y(0) {}
        Point(int x, int y) : m_x(x), m_y(y) {}
        Point(const Point& point) : Point(point.m_x, point.m_y) {}
        inline Point& operator+=(const Point& point) { m_x += point.m_x; m_y += point.m_y; return *this; }
        inline Point& operator-=(const Point& point) { m_x -= point.m_x; m_y -= point.m_y; return *this; }
        inline Point operator+(const Point& point) const { return Point(m_x + point.m_x, m_y + point.m_y); }
        inline Point operator-(const Point& point) const { return Point(m_x - point.m_x, m_y - point.m_y); }
        inline bool operator==(const Point& point) const { return m_x == point.m_x && m_y == point.m_y; }
        inline bool operator!=(const Point& point) const { return m_x != point.m_x || m_y != point.m_y; }

        inline int GetX() const { return m_x; }
        inline int GetY() const { return m_y; }
        inline void SetX(int x) { m_x = x; }
        inline void SetY(int y) { m_y = y; }

    private:
        int m_x;
        int m_y;
    };
}