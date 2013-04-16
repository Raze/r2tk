/* HEADER
 *
 * File: r2-matrix-2.hpp
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
 *	A mathematical matrix of 2x2 elements
 * Depends on:
 *  * SCALAR
 *  * FloatCompare
 * Updates:
 * 
 */
#ifndef R2_MATRIX_2_HPP
#define R2_MATRIX_2_HPP

#include <ostream>
#include "r2-math-generic.hpp"
#include "r2-vector-2.hpp"

namespace r2 {
	namespace Math {
		class Matrix2 {
		public:
			/**
			 * Initialize the zero matrix
			 */
			Matrix2();

			/**
			 * Initialize a matrix with the given parameter as the diagonal elements. The rest
			 * of the elements are set to 0.
			 */
			Matrix2(SCALAR p_diagonal_element);

			/**
			 * Initialize the matrix with the given elements. Row order, so for instance
			 * p_01 will be the first row and the second column.
			 */
			Matrix2(SCALAR p_00, SCALAR p_01, SCALAR p_10, SCALAR p_11);

			/**
			 * Initialize the matrix from an array of scalars. Will assume the array
			 * is of at least length K_DIMENSIONS * K_DIMENSIONS and has the elements
			 * in row order.
			 */
			Matrix2(const SCALAR* p_raw_data);

			/**
			 * Initialize the matrix with the given row vectors
			 */
			Matrix2(const Vector2& p_row_1,
					const Vector2& p_row_2);


			/**
			 * Methods for accessing a row or column from the matrix.
			 */
			Vector2 GetRow(unsigned int p_row) const;
			Vector2 GetColumn(unsigned int p_col) const;

			/**
			 * Methods for setting the rows and the columns of the matrix
			 */
			void SetRow(unsigned int p_row_index, const Vector2& p_row_vector);
			void SetColumn(unsigned int p_column_index, const Vector2& p_column_vector);


			/**
			 * Operators
			 */
			SCALAR& operator()(unsigned int p_row, unsigned int p_col);
			Matrix2 operator-() const;
			Matrix2& operator+=(const Matrix2& p_rhs);
			Matrix2& operator-=(const Matrix2& p_rhs);
			Matrix2& operator*=(SCALAR p_rhs);
			Matrix2& operator*=(const Matrix2& p_rhs);
			Matrix2& operator/=(SCALAR p_rhs);

			/**
			 * Calculate the trace of the matrix (the sum of the diagonal elements).
			 */
			SCALAR Trace() const;

			/**
			 * Calculate the determinant of the matrix.
			 */
			SCALAR Determinant() const;

			/**
			 * Transpose this matrix (all elements A_ij are set to A_ji).
			 */
			Matrix2& Transpose();

			/**
			 * Invert this matrix, if possible. If the matrix is
			 * singular, a DivisionByZero exception is raised.
			 */
			Matrix2& Invert();

			/**
			 * True if this matrix is singular and has no inverse (i.e. the
			 * determinant of this matrix is 0).
			 */
			bool IsSingular() const;



			static const unsigned int K_DIMENSIONS = 2;
			union {
				/**
				 * All data is in row order - i.e. the first array index
				 * in m_elements is the row index.
				 */
				SCALAR m_data[K_DIMENSIONS * K_DIMENSIONS];
				SCALAR m_elements[K_DIMENSIONS][K_DIMENSIONS];
			};

			static const Matrix2 K_ZERO_MATRIX;
			static const Matrix2 K_IDENTITY;
		};

		/**
		 * Operators
		 */
		Matrix2 operator*(const Matrix2& p_lhs, SCALAR p_rhs);
		Matrix2 operator*(SCALAR p_lhs, const Matrix2& p_rhs);
		Matrix2 operator/(const Matrix2& p_lhs, SCALAR p_rhs);
		Matrix2 operator+(const Matrix2& p_lhs, const Matrix2& p_rhs);
		Matrix2 operator-(const Matrix2& p_lhs, const Matrix2& p_rhs);
		Matrix2 operator*(const Matrix2& p_lhs, const Matrix2& p_rhs);
		Vector2 operator*(const Matrix2& p_lhs, const Vector2& p_rhs);
		bool operator==(const Matrix2& p_lhs, const Matrix2& p_rhs);
		bool operator!=(const Matrix2& p_lhs, const Matrix2& p_rhs);
		std::ostream& operator<<(std::ostream& p_lhs, const Matrix2& p_rhs);

		/**
		 * Calculate the trace of the matrix (the sum of the diagonal elements).
		 */
		SCALAR Trace(const Matrix2& p_matrix);

		/**
		 * Calculate the determinant of the matrix.
		 */
		SCALAR Determinant(const Matrix2& p_matrix);

		/**
		 * Get a transpose of the matrix (all elements A_ij are set to A_ji).
		 */
		Matrix2 GetTranspose(const Matrix2& p_matrix);

		/**
		 * Get the inverse of the matrix, if possible. If the matrix is
		 * singular, a DivisionByZero exception is raised.
		 */
		Matrix2 GetInverse(const Matrix2& p_matrix);
	}
}

#endif