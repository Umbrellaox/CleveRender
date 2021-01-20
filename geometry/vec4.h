#pragma once

#ifndef __VEC4__H
#define __VEC4__H

#include <iostream>

#include "qualifier.h"


namespace geo
{
    template <typename T>
    struct vec<4, T>
    {
        union {
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            T raw[4];
        };
        vec() : x(0), y(0), z(0), w(0) {}
        vec(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
        vec(const vec<3, T>& rhs, T _w)
            : x(rhs.x),
            y(rhs.y),
            z(rhs.z),
            w(_w)
        {}

        vec(const vec<4, T>& rhs)
            : x(rhs.x),
            y(rhs.y),
            z(rhs.z),
            w(rhs.w)
        {}


        inline vec<4, T> operator+(const vec<4, T>& rhs) const
        {
            return vec<4, T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        inline vec<4, T> operator-(const vec<4, T>& rhs) const
        {
            return vec<4, T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        inline vec<4, T> operator*(float f) const
        {
            return vec<4, T>(x * f, y * f, z * f, w * f);
        }

        inline vec<4, T> operator/(float f) const
        {
            return vec<4, T>(x / f, y / f, z / f, w / f);
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
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        vec<4, T> normalize() const
        {
            float n = norm();
            return vec<4, T>(x / n, y / n, z / n, w / n);
        }

        template <typename T> friend std::ostream& operator<<(std::ostream& s, const vec<4, T>& V);
    };

    template <typename T> std::ostream& operator<<(std::ostream& s, const vec<4, T>& v) {
        s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")\n";
        return s;
    }
}

#endif // !__VEC4__H
