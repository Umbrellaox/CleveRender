#pragma once

#ifndef __VEC2__H
#define __VEC2__H

#include <iostream>

#include "qualifier.h"


namespace geo
{
    template <typename T>
    struct vec<2, T>
    {
        union {
            struct { T x, y; };
            struct { T u, v; };
            T raw[2];
        };
        vec() : x(0), y(0) {}
        vec(T _x, T _y) : x(_x), y(_y){}


        inline vec<2, T> operator+(const vec<2, T>& rhs) const
        {
            return vec<2, T>(x + rhs.x, y + rhs.y);
        }

        inline vec<2, T> operator-(const vec<2, T>& rhs) const
        {
            return vec<2, T>(x - rhs.x, y - rhs.y);
        }

        inline vec<2, T> operator*(float f) const
        {
            return vec<2, T>(x * f, y * f);
        }

        inline vec<2, T> operator+=(const vec<2, T>& rhs) const
        {
            return *this + rhs;
        }


        inline const T& operator[](const int i) const
        {
            return raw[i];
        }

        inline T& operator[](const int i)
        {
            return raw[i];
        }


        float norm() const
        {
            return std::sqrt(x * x + y * y);
        }

        vec<3, T> normalize() const
        {
            float n = norm();
            return vec<3, T>(x / n, y / n);
        }

        template <typename T> friend std::ostream& operator<<(std::ostream& s, const vec<2, T>& V);
    };

    template <typename T> std::ostream& operator<<(std::ostream& s, const vec<2, T>& v) {
        s << "(" << v.x << ", " << v.y << ")\n";
        return s;
    }
}

#endif // !__VEC3__H
