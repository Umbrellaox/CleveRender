#pragma once

#ifndef __MAT4__H
#define __MAT4__H

#include "qualifier.h"
#include <stdexcept>

namespace geo
{
    template <typename T>
    struct mat<4, 4, T>
    {
        //regarding mat as 4 column of vec4, it means it's column order
        //this order also meet matrix's real meaning : linear transformation
        //regard every matrix you met as a linear transformation
        typedef vec<4, T> column_type;
        column_type value[4];


        mat()
            :value()
        {}

        mat(const mat<4, 4, T>& rhs)
            : value{rhs[0], rhs[1], rhs[2], rhs[3]}
        {
        }

        mat(std::initializer_list<T> list)
        {
            if (list.size() != 16)
            {
                throw std::exception("wrong input");
            }
            auto iter = list.begin();
            this->value[0] = column_type(iter[0], iter[4], iter[8], iter[12]);
            this->value[1] = column_type(iter[1], iter[5], iter[9], iter[13]);
            this->value[2] = column_type(iter[2], iter[6], iter[10], iter[14]);
            this->value[3] = column_type(iter[3], iter[7], iter[11], iter[15]);
        }

        mat(T _v)
            : value()
        {
            for (int i = 0; i < 4; i++)
            {
                value[i][i] = _v;
            }
        }

        static mat<4, 4, T> identity()
        {
            mat<4, 4, T> Result;
            for (int i = 0; i < 4; i++)
            {
                Result[i][i] = 1;
            }


            return Result;
        }


        column_type& operator[](int i)
        {
            return value[i];
        }

        const column_type& operator[](int i) const
        {
            return value[i];
        }

        mat<4, 4, T> operator*(const mat<4, 4, T>& rhs)
        {
            //本质是新的基向量又经过一次变换变成了更新的基向量
            mat<4, 4, T> Result;
            Result[0] = value[0] * rhs[0][0] + value[1] * rhs[0][1] + value[2] * rhs[0][2] + value[3] * rhs[0][3];
            Result[1] = value[0] * rhs[1][0] + value[1] * rhs[1][1] + value[2] * rhs[1][2] + value[3] * rhs[1][3];
            Result[2] = value[0] * rhs[2][0] + value[1] * rhs[2][1] + value[2] * rhs[2][2] + value[3] * rhs[2][3];
            Result[3] = value[0] * rhs[3][0] + value[1] * rhs[3][1] + value[2] * rhs[3][2] + value[3] * rhs[3][3];

            return Result;
        }

        vec<4, T> operator*(const vec<4, T>& v)
        {
            return vec<4, T>( value[0] * v[0] + value[1] * v[1] + value[2] * v[2] + value[3] * v[3]);
        }

        vec<4, T> operator*(const vec<3, T>& v)
        {
            return vec<4, T>(value[0] * v[0] + value[1] * v[1] + value[2] * v[2] + value[3] * (T)1.0);
        }

        template <class T> friend std::ostream& operator<<(std::ostream& os, const mat<4, 4, T>& rhs);

    };
    template<class T>
    std::ostream& operator<<(std::ostream& os, const mat<4, 4, T>& rhs)
    {
        for (int i = 0; i < 4; i++)
        {   
            for (int j = 0; j < 4; j++)
            {
                std::cout << rhs[j][i] << " ";
            }
            std::cout << std::endl;
        }

        // TODO: insert return statement here
        return os;
    }
}

#endif // !__MAT4__H
