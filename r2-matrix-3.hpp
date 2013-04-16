/* HEADER
 *
 * File: r2-matrix-3.hpp
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
 *	A mathematical matrix of 3x3 elements
 * Depends on:
 *  * SCALAR
 *  * FloatCompare
 * Updates:
 * 
 */
#ifndef R2_MATRIX_3_HPP
#define R2_MATRIX_3_HPP

#include <ostream>
#include "r2-math-generic.hpp"
#include "r2-vector-3.hpp"
#include "r2-matrix-2.hpp"

namespace r2 {
	namespace Math {
		class Matrix3 {
		public:
			/**
			 * Initialize the zero matrix
			 */
			Matrix3();

			/**
			 * Initialize a matrix with the given parameter as the diagonal elements. The rest
			 * of the elements are set to 0.
			 */
			Matrix3(SCALAR p_diagonal_element);

			/**
			 * Initialize the matrix with the given elements. Row order, so for instance
			 * p_01 will be the first row and the second column.
			 */
			Matrix3(SCALAR p_00, SCALAR p_01, SCALAR p_02,
					SCALAR p_10, SCALAR p_11, SCALAR p_12,
					SCALAR p_20, SCALAR p_21, SCALAR p_22);

			/**
			 * Initialize the matrix from an array of scalars. Will assume the array
			 * is of at least length K_DIMENSIONS * K_DIMENSIONS and has the elements
			 * in row order.
			 */
			Matrix3(SCALAR* p_raw_data);

			/**
			 * Initialize the matrix with the given row vectors
			 */
			Matrix3(const Vector3& p_row_1,
					const Vector3& p_row_2,
					const Vector3& p_row_3);


			/**
			 * Methods for accessing a row or column from the matrix.
			 */
			Vector3 GetRow(int p_row) const;
			Vector3 GetColumn(int p_col) const;

			/**
			 * Methods for setting the rows and the columns of the matrix
			 */
			void SetRow(unsigned int p_row_index, const Vector3& p_row_vector);
			void SetColumn(unsigned int p_column_index, const Vector3& p_column_vector);


			/**
			 * Operators
			 */
			SCALAR& operator()(unsigned int p_row, unsigned int p_col);
			Matrix3 operator-() const;
			Matrix3& operator+=(const Matrix3& p_rhs);
			Matrix3& operator-=(const Matrix3& p_rhs);
			Matrix3& operator*=(SCALAR p_rhs);
			Matrix3& operator*=(const Matrix3& p_rhs);
			Matrix3& operator/=(SCALAR p_rhs);

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
			Matrix3& Transpose();

			/**
			 * Invert this matrix, if possible. If the matrix is
			 * singular, a DivisionByZero exception is raised.
			 */
			Matrix3& Invert();

			/**
			 * Return a minor matrix of this matrix. A minor is constructed by placing
			 * all elements that are not on the row p_row_to_remove and the column p_col_to_remove
			 * into a new, smaller matrix.
			 */
			Matrix2 GetMinorMatrix(unsigned int p_row_to_remove, unsigned int p_col_to_remove) const;


			static const unsigned int K_DIMENSIONS = 3;
			union {
				/**
				 * All data is in row order - i.e. the first array index
				 * in m_elements is the row index.
				 */
				SCALAR m_data[K_DIMENSIONS * K_DIMENSIONS];
				SCALAR m_elements[K_DIMENSIONS][K_DIMENSIONS];
			};

			static const Matrix3 K_ZERO_MATRIX;
			static const Matrix3 K_IDENTITY;
		};

		/**
		 * Operators
		 */
		Matrix3 operator*(const Matrix3& p_lhs, SCALAR p_rhs);
		Matrix3 operator*(SCALAR p_lhs, const Matrix3& p_rhs);
		Matrix3 operator/(const Matrix3& p_lhs, SCALAR p_rhs);
		Matrix3 operator+(const Matrix3& p_lhs, const Matrix3& p_rhs);
		Matrix3 operator-(const Matrix3& p_lhs, const Matrix3& p_rhs);
		Matrix3 operator*(const Matrix3& p_lhs, const Matrix3& p_rhs);
		Vector3 operator*(const Matrix3& p_lhs, const Vector3& p_rhs);
		bool operator==(const Matrix3& p_lhs, const Matrix3& p_rhs);
		bool operator!=(const Matrix3& p_lhs, const Matrix3& p_rhs);
		std::ostream& operator<<(std::ostream& p_lhs, const Matrix3& p_rhs);


		/**
		 * Calculate the trace of the matrix (the sum of the diagonal elements).
		 */
		SCALAR Trace(const Matrix3& p_matrix);

		/**
		 * Calculate the determinant of the matrix.
		 */
		SCALAR Determinant(const Matrix3& p_matrix);

		/**
		 * Get a transpose of the matrix (all elements A_ij are set to A_ji).
		 */
		Matrix3 GetTranspose(const Matrix3& p_matrix);

		/**
		 * Get a matrix that has a minor (the determinant of a minor matrix) with (i, j) row and column
		 * crossed out at position (i, j).
		 */
		Matrix3 GetMatrixOfMinors(const Matrix3& p_matrix);

		/**
		 * Get the matrix of minors, where every elements at (i, j) where i + j is odd
		 * is negative.
		 */
		Matrix3 GetMatrixOfCofactors(const Matrix3& p_matrix);

		/**
		 * The transpose of the matrix of cofactors.
		 */
		Matrix3 GetAdjugate(const Matrix3& p_matrix);

		/**
		 * Get the inverse of the matrix, if possible. If the matrix is
		 * singular, a DivisionByZero exception is raised.
		 */
		Matrix3 GetInverse(const Matrix3& p_matrix);
	}
}

#endif
