#pragma once

#ifndef __MAT3__H
#define __MAT3__H

#include "qualifier.h"
#include <stdexcept>

namespace geo
{
    template <typename T>
    struct mat<3, 3, T>
    {
        //regarding mat as 3 column of vec3, it means it's column order
        //this order also meet matrix's real meaning : linear transformation
        //regard every matrix you met as a linear transformation
        typedef vec<3, T> column_type;
        column_type value[3];

        mat(const mat<3, 3, T>& rhs)
            : value{ rhs[0], rhs[1], rhs[2] }
        {
        }

        mat(std::initializer_list<T> list)
        {
            if (list.size() != 9)
            {
                throw std::exception("wrong input");
            }
            auto iter = list.begin();
            this->value[0] = column_type(iter[0], iter[3], iter[6]);
            this->value[1] = column_type(iter[1], iter[4], iter[7]);
            this->value[2] = column_type(iter[2], iter[5], iter[8]);
        }

        static mat<3, 3, T> identity()
        {
            mat<3, 3, T> Result;
            for (int i = 0; i < 3; i++)
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


        template <class T> friend std::ostream& operator<<(std::ostream& os, const mat<3, 3, T>& rhs);

    };
    template<class T>
    std::ostream& operator<<(std::ostream& os, const mat<3, 3, T>& rhs)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                std::cout << rhs[j][i] << " ";
            }
            std::cout << std::endl;
        }

        // TODO: insert return statement here
        return os;
    }
}

#endif // !__MAT3__H
