/* HEADER
 *
 * File: r2-vector-3.hpp
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
 *	A mathematical representation of a 3 dimensional vector
 * Depends on:
 *  * r2::Exception::OutOfRange
 *  * SCALAR
 *  * FloatCompare
 * Updates:
 * 
 */
#ifndef R2_VECTOR_3_HPP
#define R2_VECTOR_3_HPP

#include <ostream>
#include <istream>
#include "r2-math-generic.hpp"

namespace r2 {
	namespace Math {
		class Vector3 {
		public:
			/**
			 * Initialize the zero vector
			 */
			Vector3();

			/**
			 * Initialize a vector (p_x, p_y, p_z)
			 */
			Vector3(SCALAR p_x, SCALAR p_y, SCALAR p_z);

			/**
			 * Initialize a vector from an array of scalars. Will assume
			 * the array is of at least length 3 and has p_raw_data[0] as
			 * the x component, p_raw_data[1] as the y component and
			 * p_raw_data[2] as the z component.
			 */
			Vector3(const SCALAR* p_raw_data);


			/**
			 * Operators
			 */
			SCALAR& operator[](unsigned int p_index);
			SCALAR operator[](unsigned int p_index) const;
			Vector3& operator-();
			Vector3& operator+=(const Vector3& p_rhs);
			Vector3& operator-=(const Vector3& p_rhs);
			Vector3& operator*=(SCALAR p_rhs);
			Vector3& operator/=(SCALAR p_rhs);

			/**
			 * Calculate the dot product
			 */
			SCALAR Dot(const Vector3& p_rhs) const;

			/**
			 * Calculate the cross product between two vectors, yielding a new
			 * vector perpendicular to both.
			 */
			Vector3 Cross(const Vector3& p_rhs) const;

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
			Vector3& Normalize();


			/**
			 * The components of the vector
			 */
			union {
				struct {
					SCALAR x;
					SCALAR y;
					SCALAR z;
				};

				SCALAR m_data[3];
			};
			
			

			static const Vector3 K_ZERO;
			static const Vector3 K_AXIS_X;
			static const Vector3 K_AXIS_Y;
			static const Vector3 K_AXIS_Z;
		};

		/**
		 * Operators
		 */
		Vector3 operator+(const Vector3& p_lhs, const Vector3& p_rhs);
		Vector3 operator-(const Vector3& p_lhs, const Vector3& p_rhs);
		Vector3 operator*(const Vector3& p_lhs, SCALAR p_rhs);
		Vector3 operator*(SCALAR p_lhs, const Vector3& p_rhs);
		Vector3 operator/(const Vector3& p_lhs, SCALAR p_rhs);
		bool operator==(const Vector3& p_lhs, const Vector3& p_rhs);
		bool operator!=(const Vector3& p_lhs, const Vector3& p_rhs);
		bool operator<(const Vector3& p_lhs, const Vector3& p_rhs);
		bool operator>(const Vector3& p_lhs, const Vector3& p_rhs);
		bool operator<=(const Vector3& p_lhs, const Vector3& p_rhs);
		bool operator>=(const Vector3& p_lhs, const Vector3& p_rhs);
		std::ostream& operator<<(std::ostream& p_lhs, const Vector3& p_rhs);
		std::istream& operator>>(std::istream& p_lhs, Vector3& p_rhs);

		/**
		 * Calculate the dot product
		 */
		SCALAR Dot(const Vector3& p_lhs, const Vector3& p_rhs);

		/**
		 * Calculate the cross product between two vectors, yielding a new
		 * vector perpendicular to both.
		 */
		Vector3 Cross(const Vector3& p_lhs, const Vector3& p_rhs);

		/**
		 * Calculate the length (magnitude) of the vector
		 */
		SCALAR Length(const Vector3& p_vector);

		/**
		 * Calculate the square of the length (magnitude) of the vector
		 */
		SCALAR LengthSquared(const Vector3& p_vector);

		/**
		 * Get a normalized version of the vector
		 */
		Vector3 GetNormalized(const Vector3& p_vector);
	}
}

#endif
