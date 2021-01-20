#pragma once

#ifndef __VEC3__H
#define __VEC3__H

#include <iostream>

#include "qualifier.h"


namespace geo
{
    template <typename T>
    struct vec<3, T>
    {
        union {
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T u, v, w; };
            T raw[3];
        };
        vec() : x(0), y(0), z(0) {}
        vec(T _x, T _y, T _z) : x(_x), y(_y), z(_z){}
        vec(const vec<4, T>& rhs)
            : x(rhs.x),
            y(rhs.y),
            z(rhs.z)
        {}

        vec(const vec<2, T>& rhs)
            : x(rhs.x),
            y(rhs.y),
            z(static_cast<T>(1))
        {}

        vec(const vec<2, T>& rhs, T w_)
            : x(rhs.x),
            y(rhs.y),
            z(w_)
        {}




        inline vec<3, T> operator+(const vec<3, T>& rhs) const
        {
            return vec<3, T>(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        inline vec<3, T> operator-(const vec<3, T>& rhs) const
        {
            return vec<3, T>(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        inline vec<3, T> operator*(float f) const
        {
            return vec<3, T>(x * f, y * f, z * f);
        }

        inline vec<3, T> operator/(float f) const
        {
            return vec<3, T>(x / f, y / f, z / f);
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
            return std::sqrt(x * x + y * y + z * z);
        }

        vec<3, T> normalize() const
        {
            float n = norm();
            return vec<3, T>(x / n, y / n, z / n);
        }

        template <typename T> friend std::ostream& operator<<(std::ostream& s, const vec<3, T>& V);
    };

    template <typename T> std::ostream& operator<<(std::ostream& s, const vec<3, T>& v) {
        s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
        return s;
    }
}

#endif // !__VEC3__H
