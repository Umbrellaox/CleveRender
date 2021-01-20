#pragma once

#ifndef __MATRIX_TRANSFORMATION_H__
#define __MATRIX_TRANSFORMATION_H__

#include "qualifier.h"


namespace geo
{
    /*The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. 
     *(Direct3D clip volume definition)
     */
    template <typename T>
    mat<4, 4, T> perspective_RH_NO_OpenGL(T fovy, T aspect, T zNear, T zFar)
    {
        mat<4, 4, T> Result;
        const T tanHalfFovy = std::tan(fovy / 2);
        Result[0][0] = 1 / (aspect * tanHalfFovy);
        Result[1][1] = 1 / tanHalfFovy;
        Result[2][2] = -(zFar + zNear) / (zFar - zNear);
        Result[2][3] = -static_cast<T>(1);
        Result[3][2] = -static_cast<T>(2) * zFar * zNear / (zFar - zNear);

        return Result;
    }

    template <typename T>
    mat<4, 4, T> perspective_RH(T fovy, T aspect, T zNear, T zFar)
    {
        mat<4, 4, T> Result;
        const T tanHalfFovy = std::tan(radians((float)fovy * 0.5f));
        Result[0][0] = 1 / (aspect * tanHalfFovy);
        Result[1][1] = 1 / tanHalfFovy;
        Result[2][2] = (zNear + zFar) / (zNear - zFar);
        Result[2][3] = static_cast<T>(1);
        Result[3][2] = static_cast<T>(2) * (zFar * zNear) / (zFar - zNear);

        return Result;
    }

    template <typename T>
    mat<4, 4, T> viewport(T width, T height)
    {
        mat<4, 4, T> Result;
        Result[0][0] = width / static_cast<T>(2);
        Result[1][1] = height / static_cast<T>(2);
        Result[2][2] = 1;
        Result[3][3] = 1;
        Result[3][0] = width / static_cast<T>(2);
        Result[3][1] = height / static_cast<T>(2);

        return Result;
    }

    template <typename T>
    mat<4, 4, T> ortho(T right, T left, T top, T bottom, T zNear, T zFar)
    {
        mat<4, 4, T> Result = mat4::identity();
        Result[0][0] = 2 / (right - left);
        Result[1][1] = 2 / (top - bottom);;
        Result[2][2] = 2 / (zNear - zFar);
        Result[3][0] = -(right + left) / 2;
        Result[3][1] = -(top + bottom) / 2;
        Result[3][2] = -(zNear + zFar) / 2;

        return Result;
    }

    template <typename T>
    mat<4, 4, T> persp_ortho(T zNear, T zFar)
    {
        mat<4, 4, T> Result;
        Result[0][0] = zNear;
        Result[1][1] = zNear;
        Result[2][2] = zNear + zFar;
        Result[3][2] = -zNear * zFar;
        Result[2][3] = 1;

        return Result;
    }

    template <typename T>
    mat<4, 4, T> viewMatrix_RH(const vec<3, T>& position, const vec<3, T>& point, const vec<3, T>& up)
    {
        const vec<3, T> g((point - position).normalize());  //line
        const vec<3, T> gxt(cross(g, up).normalize());    //left-line
        const vec<3, T> t(cross(gxt, g).normalize()); //up

        mat<4, 4, T> Result(1);
        Result[0][0] = gxt.x;
        Result[1][0] = gxt.y;
        Result[2][0] = gxt.z;
        Result[0][1] = t.x;
        Result[1][1] = t.y;
        Result[2][1] = t.z;
        Result[0][2] = -g.x;    //转向右手系
        Result[1][2] = -g.y;
        Result[2][2] = -g.z;
        Result[3][0] = -dot(gxt, position);
        Result[3][1] = -dot(t, position);
        Result[3][2] = dot(g, position);
        //Yes! 完全没问题
        //TODO
        return Result;
    }

    template<typename T>
    mat<4, 4, T> viewMatrix_LH(vec<3, T> const& eye, vec<3, T> const& center, vec<3, T> const& up)
    {
        vec<3, T> const g(normalize(center - eye));
        vec<3, T> const gxt(normalize(cross(up, g)));
        vec<3, T> const t(cross(g, gxt));

        mat<4, 4, T> Result(1);
        Result[0][0] = gxt.x;
        Result[1][0] = gxt.y;
        Result[2][0] = gxt.z;
        Result[0][1] = t.x;
        Result[1][1] = t.y;
        Result[2][1] = t.z;
        Result[0][2] = g.x;
        Result[1][2] = g.y;
        Result[2][2] = g.z;
        Result[3][0] = -dot(gxt, eye);
        Result[3][1] = -dot(t, eye);
        Result[3][2] = -dot(g, eye);
        return Result;
    }

}

#endif // !__MATRIX_TRANSFORMATION_H__
