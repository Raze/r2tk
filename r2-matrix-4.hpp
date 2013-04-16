/* HEADER
 *
 * File: r2-matrix-4.hpp
 * Created by: Lars Woxberg (Rarosu)
 * Created on: December 18, 2011
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
 *	A mathematical matrix of 4x4 elements
 * Depends on:
 *  * SCALAR
 *  * FloatCompare
 * Updates:
 * 
 */
#ifndef R2_MATRIX_4_HPP
#define R2_MATRIX_4_HPP

#include <ostream>
#include "r2-math-generic.hpp"
#include "r2-vector-4.hpp"
#include "r2-matrix-3.hpp"

namespace r2 {
	namespace Math {
		class Matrix4 {
		public:
			/**
			 * Initialize the zero matrix
			 */
			Matrix4();

			/**
			 * Initialize a matrix with the given parameter as the diagonal elements. The rest
			 * of the elements are set to 0.
			 */
			Matrix4(SCALAR p_diagonal_element);

			/**
			 * Initialize the matrix with the given elements. Row order, so for instance
			 * p_01 will be the first row and the second column.
			 */
			Matrix4(SCALAR p_00, SCALAR p_01, SCALAR p_02, SCALAR p_03,
					SCALAR p_10, SCALAR p_11, SCALAR p_12, SCALAR p_13,
					SCALAR p_20, SCALAR p_21, SCALAR p_22, SCALAR p_23,
					SCALAR p_30, SCALAR p_31, SCALAR p_32, SCALAR p_33);

			/**
			 * Initialize the matrix from an array of scalars. Will assume the array
			 * is of at least length K_DIMENSIONS * K_DIMENSIONS and has the elements
			 * in row order.
			 */
			Matrix4(SCALAR* p_raw_data);

			/**
			 * Initialize the matrix with the given row vectors
			 */
			Matrix4(const Vector4& p_row_1,
					const Vector4& p_row_2,
					const Vector4& p_row_3,
					const Vector4& p_row_4);


			/**
			 * Methods for accessing a row or column from the matrix.
			 */
			Vector4 GetRow(int p_row) const;
			Vector4 GetColumn(int p_col) const;

			/**
			 * Methods for setting the rows and the columns of the matrix
			 */
			void SetRow(unsigned int p_row_index, const Vector4& p_row_vector);
			void SetColumn(unsigned int p_column_index, const Vector4& p_column_vector);

			/**
			 * Operators
			 */
			SCALAR& operator()(unsigned int p_row, unsigned int p_col);
			Matrix4 operator-() const;
			Matrix4& operator+=(const Matrix4& p_rhs);
			Matrix4& operator-=(const Matrix4& p_rhs);
			Matrix4& operator*=(SCALAR p_rhs);
			Matrix4& operator*=(const Matrix4& p_rhs);
			Matrix4& operator/=(SCALAR p_rhs);



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
			Matrix4& Transpose();

			/**
			 * Invert this matrix, if possible. If the matrix is
			 * singular, a DivisionByZero exception is raised.
			 */
			Matrix4& Invert();

			/**
			 * Return a minor matrix of this matrix. A minor is constructed by placing
			 * all elements that are not on the row p_row_to_remove and the column p_col_to_remove
			 * into a new, smaller matrix.
			 */
			Matrix3 GetMinorMatrix(unsigned int p_row_to_remove, unsigned int p_col_to_remove) const;


			static const unsigned int K_DIMENSIONS = 4;
			union {
				/**
				 * All data is in row order - i.e. the first array index
				 * in m_elements is the row index.
				 */
				SCALAR m_data[K_DIMENSIONS * K_DIMENSIONS];
				SCALAR m_elements[K_DIMENSIONS][K_DIMENSIONS];
			};

			static const Matrix4 K_ZERO_MATRIX;
			static const Matrix4 K_IDENTITY;
		};

		/**
		 * Operators
		 */
		Matrix4 operator*(const Matrix4& p_lhs, SCALAR p_rhs);
		Matrix4 operator*(SCALAR p_lhs, const Matrix4& p_rhs);
		Matrix4 operator/(const Matrix4& p_lhs, SCALAR p_rhs);
		Matrix4 operator+(const Matrix4& p_lhs, const Matrix4& p_rhs);
		Matrix4 operator-(const Matrix4& p_lhs, const Matrix4& p_rhs);
		Matrix4 operator*(const Matrix4& p_lhs, const Matrix4& p_rhs);
		Vector4 operator*(const Matrix4& p_lhs, const Vector4& p_rhs);
		bool operator==(const Matrix4& p_lhs, const Matrix4& p_rhs);
		bool operator!=(const Matrix4& p_lhs, const Matrix4& p_rhs);
		std::ostream& operator<<(std::ostream& p_lhs, const Matrix4& p_rhs);

		/**
		 * Calculate the trace of the matrix (the sum of the diagonal elements).
		 */
		SCALAR Trace(const Matrix4& p_matrix);

		/**
		 * Calculate the determinant of the matrix.
		 */
		SCALAR Determinant(const Matrix4& p_matrix);

		/**
		 * Get a transpose of the matrix (all elements A_ij are set to A_ji).
		 */
		Matrix4 GetTranspose(const Matrix4& p_matrix);

		/**
		 * Get a matrix that has a minor (the determinant of a minor matrix) with (i, j) row and column
		 * crossed out at position (i, j).
		 */
		Matrix4 GetMatrixOfMinors(const Matrix4& p_matrix);

		/**
		 * Get the matrix of minors, where every elements at (i, j) where i + j is odd
		 * is negative.
		 */
		Matrix4 GetMatrixOfCofactors(const Matrix4& p_matrix);

		/**
		 * The transpose of the matrix of cofactors.
		 */
		Matrix4 GetAdjugate(const Matrix4& p_matrix);

		/**
		 * Get the inverse of the matrix, if possible. If the matrix is
		 * singular, a DivisionByZero exception is raised.
		 */
		Matrix4 GetInverse(const Matrix4& p_matrix);
	}
}


#endif