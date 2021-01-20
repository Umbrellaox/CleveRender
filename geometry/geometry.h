#pragma once
#ifndef GEOMETRY_H
#define GEOMETEY_H

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#include "qualifier.h"
//#include "matrix_transformation.h"


namespace geo
{
    typedef vec<2, float> vec2;
    typedef vec<3, float> vec3;
    typedef vec<4, float> vec4;

    typedef vec<2, int> vec2i;
    typedef vec<3, int> vec3i;
    typedef vec<4, int> vec4i;

    typedef mat<4, 4, float> mat4;
}


#endif // !GEOMETRY_H
