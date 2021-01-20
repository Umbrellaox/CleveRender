#pragma once

#ifndef __QUALIFIER__H
#define __QUALIFIER__H

#include <cmath>

namespace geo
{


	template<int L, typename T> struct vec;
	template<int C, int R, typename T> struct mat;
	template<typename T> struct qua;




	namespace detail
	{
		//----------------dot product---------------
		//V means vector, T means Type of Vector
		template <typename V, typename T>
		struct compute_dot {};

		template <typename T>
		struct compute_dot<vec<2, T>, T>
		{
			static T call(const vec<2, T>& lhs, const vec<2, T>& rhs)
			{
				return lhs.x * rhs.x + lhs.y * rhs.y;
			}
		};


		template <typename T>
		struct compute_dot<vec<3, T>, T>
		{
			static T call(const vec<3, T>& lhs, const vec<3, T>& rhs)
			{
				return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
			}
		};

		template <typename T>
		struct compute_dot<vec<4, T>, T>
		{
			static T call(const vec<4, T>& lhs, const vec<4, T>& rhs)
			{
				return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
			}
		};

		//---------------cross product-----------------
		template <typename V, typename T>
		struct compute_cross {};

		template <typename T>
		struct compute_cross<vec<3, T>, T>
		{
			static vec<3, T> call(const vec<3, T>& lhs, const vec<3, T>& rhs)
			{
				return vec<3, T>{
					lhs.y * rhs.z - lhs.z * rhs.y,
					lhs.z * rhs.x - lhs.x * rhs.z,
					lhs.x * rhs.y - lhs.y * rhs.x
				};
			}
		};

		//---------------normalize----------------

		template <int L, typename T>
		struct compute_normalize
		{
			static vec<L, T> call(const vec<L, T>& v)
			{
				return v / std::sqrt(dot(v, v));
			}
		};
	}
	

	template<int L, typename T>
	T dot(const vec<L, T>& lhs, const vec<L, T>& rhs)
	{
		return detail::compute_dot<vec<L, T>, T>::call(lhs, rhs);
	}

	template<int L, typename T>
	vec<L, T> cross(const vec<L, T>& lhs, const vec<L, T>& rhs)
	{
		return detail::compute_cross<vec<L, T>, T>::call(lhs, rhs);
	}

	template<int L, typename T>
	vec<L, T> normalize(const vec<L, T>& v)
	{
		return detail::compute_normalize<L, T>::call(v);
	}


	template <typename T>
	inline constexpr T radians(T degrees)
	{
		return degrees * static_cast<T>(0.01745329251994329576923690768489);
	}

	template <typename T>
	mat<4, 4, T> scale(const mat<4, 4, T>& m, const vec<3, T>& v)
	{
		//This is not an operation between Matrix and Vector
		//This is a operation between Two Matrix!
		mat<4, 4, T> Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];

		return Result;
	}

	template <typename T>
	T clamp(const T& val, const T& min, const T& max)
	{
		T result(val);
		if (val > max)
		{
			result = max;
		}

		if (val < min)
		{
			result = min;
		}
		
		return result;
	}

	template <typename T>
	geo::vec<2, T> vec2_min(const geo::vec<2, T>& a, const geo::vec<2, T>& b){
		float x = std::min(a.x, b.x);
		float y = std::min(a.y, b.y);
		return { x, y };
	}

	template <typename T>
	geo::vec<2, T> vec2_max(const geo::vec<2, T>& a, const geo::vec<2, T>& b) {
		float x = std::max(a.x, b.x);
		float y = std::max(a.y, b.y);
		return { x, y };
	}

	template <typename T>
	mat<4, 4, T> translate(const mat<4, 4, T>& m, const vec<3, T>& v)
	{
		//This is not an operation between Matrix and Vector
		//This is a operation between Two Matrix!
		mat<4, 4, T> Result(m);
		//std::cout << Result << std::endl;

		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];

		return Result;
	}

	template <typename T>
	mat<4, 4, T> rotate(const mat<4, 4, T>& m, T angle, const vec<3, T>& v)
	{
		//Ratation Matrix;
		//Rodrigues's Rotation Formula
		const T a = angle;
		const T c = std::cos(a);
		const T s = std::sin(a);

		vec<3, T> axis(normalize(v));
		vec<3, T> temp(axis * (T(1) - c));

		mat<4, 4, T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];


		//Return new matrix
		mat<4, 4, T> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];

		return Result;
	}



}

#endif // !__QUALIFIER__H
