/* HEADER
 *
 * File: r2-math-generic.hpp
 * Created by: Lars Woxberg (Rarosu)
 * Created on: November 14, 2011
 *
 * License:
 *   Copyright (C) 2010 Lars Woxberg
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Comments:
 *	General mathematical tools
 * Depends on:
 *
 * Updates:
 * 
 */
#ifndef R2_MATH_GENERIC_HPP
#define R2_MATH_GENERIC_HPP

namespace r2
{
	namespace Math
	{
		typedef float SCALAR;
		
		
		
		const double K_ERROR_TOLERANCE = 10e-6;
		
		const SCALAR K_PI_2 = 1.5707963267948966192313216916398;
		const SCALAR K_PI = 3.1415926535897932384626433832795;
		const SCALAR K_3PI_2 = 4.7123889803846898576939650749193;
		const SCALAR K_2PI = 6.283185307179586476925286766559;

		const SCALAR K_E = 2.7182818284590452353602874713527;

		const SCALAR K_SQRT_2 = 1.4142135623730950488016887242097;
		const SCALAR K_SQRT_3 = 1.7320508075688772935274463415059;
		const SCALAR K_SQRT_5 = 2.2360679774997896964091736687313;
		const SCALAR K_SQRT_PI = 1.7724538509055160272981674833411;

		const SCALAR K_DEGREE_TO_RADIAN = 0.01745329251994329576923690768489;
		const SCALAR K_RADIAN_TO_DEGREE = 57.295779513082320876798154814105;
		
		
		
		inline bool FloatCompare(float x, float y, float p_tolerance = K_ERROR_TOLERANCE);
		inline bool FloatCompare(double x, double y, double p_tolerance = K_ERROR_TOLERANCE);
		inline bool FloatCompare(float x, double y, double p_tolerance = K_ERROR_TOLERANCE);
		inline bool FloatCompare(double x, float y, double p_tolerance = K_ERROR_TOLERANCE);

		/**
		 * Check if an integer type is even
		 */
		template <typename T>
		inline bool IsEven(T x);


		/**
		 * IMPLEMENTATION
		 */
		inline bool FloatCompare(float x, float y, float p_tolerance)
		{
			return (y >= x - p_tolerance) && (y <= x + p_tolerance);
		}

		inline bool FloatCompare(double x, double y, float p_tolerance)
		{
			return (y >= x - p_tolerance) && (y <= x + p_tolerance);
		}

		inline bool FloatCompare(float x, double y, float p_tolerance)
		{
			return FloatCompare(static_cast<double>(x), y, p_tolerance);
		}

		inline bool FloatCompare(double x, float y, float p_tolerance)
		{
			return FloatCompare(x, static_cast<double>(y), p_tolerance);
		}


		template <typename T>
		inline bool IsEven(T x) {
			return (x & 1) == 0;
		}

	}
}

#endif
