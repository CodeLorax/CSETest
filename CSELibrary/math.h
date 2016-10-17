#pragma once
namespace CSE
{
    // Common math realted functions.
    class Math
    {
    public:
        // Return the minimum of the two values provided
        template<typename T>
        static inline T Min(const T& x, const T& y) { return x < y ? x : y; }

        // Return the maxium of the two values provided
        template<typename T>
        static inline T Max(const T& x, const T& y) { return x > y ? x : y; }

        // Clamp the value provided so that it is between the min and max
        template<typename T>
        static inline T Clamp(const T& value, const T& min, const T& max)
        { 
            if (value > max)
            {
                return max;
            }
            else if (value < min)
            {
                return min;
            }

            return value;
        }

        // Get the size of the array
        template<typename T, unsigned S>
        static unsigned int ArraySize(const T(&v)[S]) { return S; }
    };
}