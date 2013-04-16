/* HEADER
 *
 * File: r2-vector-2.hpp
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
 *	A mathematical representation of a 2 dimensional vector
 * Depends on:
 *  * r2::Exception::OutOfRange
 *  * SCALAR
 *  * FloatCompare
 * Updates:
 * 
 */
#ifndef R2_VECTOR_2_HPP
#define R2_VECTOR_2_HPP

#include <ostream>
#include <istream>
#include "r2-math-generic.hpp"

namespace r2 {
	namespace Math {
		class Vector2 {
		public:
			/**
			 * Initialize the zero vector
			 */
			Vector2();

			/**
			 * Initialize a vector (p_x, p_y)
			 */
			Vector2(SCALAR p_x, SCALAR p_y);

			/**
			 * Initialize a vector from an array of scalars. Will assume
			 * the array is of at least length 2 and has p_raw_data[0] as
			 * the x component and p_raw_data[1] as the y component.
			 */
			Vector2(const SCALAR* p_raw_data);



			/**
			 * Operators
			 */
			SCALAR& operator[](unsigned int p_index);
			SCALAR operator[](unsigned int p_index) const;
			Vector2& operator-();
			Vector2& operator+=(const Vector2& p_rhs);
			Vector2& operator-=(const Vector2& p_rhs);
			Vector2& operator*=(SCALAR p_rhs);
			Vector2& operator/=(SCALAR p_rhs);

			/**
			 * Calculate the dot product
			 */
			SCALAR Dot(const Vector2& p_rhs) const;

			/**
			 * Calculate the length (magnitude) of the vector
			 */
			SCALAR Length() const;

			/**
			 * Calculate the square of the length (magnitude) of the vector
			 */
			SCALAR LengthSquared() const;

			/**
			 * Normalize the vector and return this
			 */
			Vector2& Normalize();


			/**
			 * The components of the vector
			 */
			union {
				struct {
					SCALAR x;
					SCALAR y;
				};
				
				SCALAR m_data[2];
			};
			

			static const Vector2 K_ZERO;
			static const Vector2 K_AXIS_X;
			static const Vector2 K_AXIS_Y;
		};

		/**
		 * Operators
		 */
		Vector2 operator+(const Vector2& p_lhs, const Vector2& p_rhs);
		Vector2 operator-(const Vector2& p_lhs, const Vector2& p_rhs);
		Vector2 operator*(const Vector2& p_lhs, SCALAR p_rhs);
		Vector2 operator*(SCALAR p_lhs, const Vector2& p_rhs);
		Vector2 operator/(const Vector2& p_lhs, SCALAR p_rhs);
		bool operator==(const Vector2& p_lhs, const Vector2& p_rhs);
		bool operator!=(const Vector2& p_lhs, const Vector2& p_rhs);
		bool operator<(const Vector2& p_lhs, const Vector2& p_rhs);
		bool operator>(const Vector2& p_lhs, const Vector2& p_rhs);
		bool operator<=(const Vector2& p_lhs, const Vector2& p_rhs);
		bool operator>=(const Vector2& p_lhs, const Vector2& p_rhs);
		std::ostream& operator<<(std::ostream& p_lhs, const Vector2& p_rhs);
		std::istream& operator>>(std::istream& p_lhs, Vector2& p_rhs);

		/**
		 * Calculate the dot product
		 */
		SCALAR Dot(const Vector2& p_lhs, const Vector2& p_rhs);

		/**
		 * Calculate the length (magnitude) of the vector
		 */
		SCALAR Length(const Vector2& p_vector);

		/**
		 * Calculate the square of the length (magnitude) of the vector
		 */
		SCALAR LengthSquared(const Vector2& p_vector);

		/**
		 * Get a normalized version of the vector
		 */
		Vector2 GetNormalized(const Vector2& p_vector);

		/**
		 * Get a normal to this vector (there are two vectors pointing 90 degrees in respect to this one).
		 *
		 * The right hand side normal is defined as the normal you're given if you look in the direction of the
		 * vector and take the normal going to the right.
		 */
		Vector2 GetNormal(const Vector2& p_vector, bool p_right_hand);
	}
}

#endif