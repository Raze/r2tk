#include "r2-matrix-2.hpp"
#include "r2-exception.hpp"
#include <cstring>

namespace r2 {
	namespace Math {
		const Matrix2 Matrix2::K_ZERO_MATRIX;
		const Matrix2 Matrix2::K_IDENTITY(1.0f);

		Matrix2::Matrix2() {
			memset(m_data, 0, sizeof(m_data));
		}

		Matrix2::Matrix2(SCALAR p_diagonal_element) {
			memset(m_data, 0, sizeof(m_data));
			for (int i = 0; i < K_DIMENSIONS; ++i) {
				m_elements[i][i] = p_diagonal_element;
			}
		}

		Matrix2::Matrix2(SCALAR p_00, SCALAR p_01, SCALAR p_10, SCALAR p_11) {
			m_elements[0][0] = p_00;
			m_elements[0][1] = p_01;
			m_elements[1][0] = p_10;
			m_elements[1][1] = p_11;
		}

		Matrix2::Matrix2(const SCALAR* p_raw_data) {
			memcpy(m_data, p_raw_data, sizeof(m_data));
		}

		Matrix2::Matrix2(const Vector2& p_row_1, const Vector2& p_row_2) {
			SetRow(0, p_row_1);
			SetRow(1, p_row_2);
		}

		Vector2 Matrix2::GetRow(unsigned int p_row) const {
			return Vector2(m_elements[p_row]);
		}

		Vector2 Matrix2::GetColumn(unsigned int p_col) const {
			return Vector2(m_elements[0][p_col],
						   m_elements[1][p_col]);
		}

		void Matrix2::SetRow(unsigned int p_row_index, const Vector2& p_row_vector) {
			for (int col = 0; col < K_DIMENSIONS; ++col) {
				m_elements[p_row_index][col] = p_row_vector[col];
			}
		}

		void Matrix2::SetColumn(unsigned int p_column_index, const Vector2& p_column_vector) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				m_elements[row][p_column_index] = p_column_vector[row];
			}
		}

		SCALAR& Matrix2::operator()(unsigned int p_row, unsigned int p_col) {
			return m_elements[p_row][p_col];
		}

		Matrix2 Matrix2::operator-() const {
			Matrix2 result = *this;
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					result.m_elements[row][col] = -result.m_elements[row][col];
				}
			}

			return result;
		}

		Matrix2& Matrix2::operator+=(const Matrix2& p_rhs) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					m_elements[row][col] += p_rhs.m_elements[row][col];
				}
			}

			return *this;
		}

		Matrix2& Matrix2::operator-=(const Matrix2& p_rhs) {
			return *this += (-p_rhs);
		}

		Matrix2& Matrix2::operator*=(SCALAR p_rhs) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					m_elements[row][col] *= p_rhs;
				}
			}

			return *this;
		}

		Matrix2& Matrix2::operator*=(const Matrix2& p_rhs) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				Vector2 temp = GetRow(row);
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					m_elements[row][col] = Dot(temp, p_rhs.GetColumn(col));
				}
			}

			return *this;
		}

		Matrix2& Matrix2::operator/=(SCALAR p_rhs) {
			return *this *= (1.0f / p_rhs);
		}


		SCALAR Matrix2::Trace() const {
			SCALAR trace = 0;
			for (int i = 0; i < K_DIMENSIONS; ++i) {
				trace += m_elements[i][i];
			}

			return trace;
		}

		SCALAR Matrix2::Determinant() const {
			return m_elements[0][0] * m_elements[1][1] - m_elements[0][1] * m_elements[1][0];
		}


		Matrix2& Matrix2::Transpose() {
			SCALAR temp = m_elements[0][1];
			m_elements[0][1] = m_elements[1][0];
			m_elements[1][0] = temp;

			return *this;
		}

		Matrix2& Matrix2::Invert() {
			SCALAR determinant = Determinant();

			if (FloatCompare(determinant, 0.0f)) throw r2ExceptionDivisionByZeroM("Singular matrix cannot be inverted");

			SCALAR temp = m_elements[0][0];
			m_elements[0][0] =  m_elements[1][1];
			m_elements[0][1] = -m_elements[0][1];
			m_elements[1][0] = -m_elements[1][0];
			m_elements[1][1] =  temp;

			return *this;
		}

		bool Matrix2::IsSingular() const {
			return FloatCompare(Determinant(), 0.0f);
		}




		Matrix2 operator*(const Matrix2& p_lhs, SCALAR p_rhs) {
			return (Matrix2(p_lhs) *= p_rhs);
		}

		Matrix2 operator*(SCALAR p_lhs, const Matrix2& p_rhs) {
			return p_rhs * p_lhs;
		}

		Matrix2 operator/(const Matrix2& p_lhs, SCALAR p_rhs) {
			return p_lhs * (1.0f / p_rhs);
		}

		Matrix2 operator+(const Matrix2& p_lhs, const Matrix2& p_rhs) {
			return (Matrix2(p_lhs) += p_rhs);
		}

		Matrix2 operator-(const Matrix2& p_lhs, const Matrix2& p_rhs) {
			return (Matrix2(p_lhs) -= p_rhs);
		}

		Matrix2 operator*(const Matrix2& p_lhs, const Matrix2& p_rhs) {
			return (Matrix2(p_lhs) *= p_rhs);
		}

		Vector2 operator*(const Matrix2& p_lhs, const Vector2& p_rhs) {
			Vector2 result;
			for (int row = 0; row < Matrix2::K_DIMENSIONS; ++row) {
				result[row] = Dot(p_lhs.GetRow(row), p_rhs);
			}

			return result;
		}

		bool operator==(const Matrix2& p_lhs, const Matrix2& p_rhs) {
			for (int row = 0; row < Matrix2::K_DIMENSIONS; ++row) {
				for (int col = 0; col < Matrix2::K_DIMENSIONS; ++col) {
					if (!FloatCompare(p_lhs.m_elements[row][col], p_rhs.m_elements[row][col])) return false;
				}
			}

			return true;
		}

		bool operator!=(const Matrix2& p_lhs, const Matrix2& p_rhs) {
			return !(p_lhs == p_rhs);
		}

		std::ostream& operator<<(std::ostream& p_lhs, const Matrix2& p_rhs) {
			for (int row = 0; row < Matrix2::K_DIMENSIONS; ++row) {
				p_lhs << "[";
				
				for (int col = 0; col < Matrix2::K_DIMENSIONS; ++col) {
					p_lhs << p_rhs.m_elements[row][col];

					if (col != Matrix2::K_DIMENSIONS - 1) p_lhs << ", ";
				}

				p_lhs << "]";
				if (row != Matrix2::K_DIMENSIONS - 1) p_lhs << std::endl;
			}

			return p_lhs;
		}




		SCALAR Trace(const Matrix2& p_matrix) {
			return p_matrix.Trace();
		}

		SCALAR Determinant(const Matrix2& p_matrix) {
			return p_matrix.Determinant();
		}

		Matrix2 GetTranspose(const Matrix2& p_matrix) {
			return Matrix2(p_matrix).Transpose();
		}

		Matrix2 GetInverse(const Matrix2& p_matrix) {
			return Matrix2(p_matrix).Invert();
		}

	}
}