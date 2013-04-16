#include "r2-matrix-3.hpp"
#include "r2-exception.hpp"
#include <cstring>

namespace r2
{
	namespace Math
	{
		const Matrix3 Matrix3::K_ZERO_MATRIX;
		const Matrix3 Matrix3::K_IDENTITY(1.0f);

		Matrix3::Matrix3() {
			memset(m_data, 0, sizeof(m_data));
		}

		Matrix3::Matrix3(SCALAR p_diagonal_element) {
			memset(m_data, 0, sizeof(m_data));
			for (int i = 0; i < K_DIMENSIONS; ++i) {
				m_elements[i][i] = p_diagonal_element;
			}
		}

		Matrix3::Matrix3(SCALAR p_00, SCALAR p_01, SCALAR p_02, SCALAR p_10, SCALAR p_11, SCALAR p_12, SCALAR p_20, SCALAR p_21, SCALAR p_22) {
			m_elements[0][0] = p_00;
			m_elements[0][1] = p_01;
			m_elements[0][2] = p_02;

			m_elements[1][0] = p_10;
			m_elements[1][1] = p_11;
			m_elements[1][2] = p_12;

			m_elements[2][0] = p_20;
			m_elements[2][1] = p_21;
			m_elements[2][2] = p_22;
		}

		Matrix3::Matrix3(SCALAR* p_raw_data) {
			memcpy(m_data, p_raw_data, sizeof(m_data));
		}

		Matrix3::Matrix3(const Vector3& p_row_1, const Vector3& p_row_2, const Vector3& p_row_3) {
			SetRow(0, p_row_1);
			SetRow(1, p_row_2);
			SetRow(2, p_row_3);
		}


		Vector3 Matrix3::GetRow(int p_row) const {
			return Vector3(m_elements[p_row]);
		}

		Vector3 Matrix3::GetColumn(int p_col) const {
			return Vector3(m_elements[0][p_col],
						   m_elements[1][p_col],
						   m_elements[2][p_col]);
		}

		void Matrix3::SetRow(unsigned int p_row_index, const Vector3& p_row_vector) {
			for (int col = 0; col < K_DIMENSIONS; ++col) {
				m_elements[p_row_index][col] = p_row_vector[col];
			}
		}

		void Matrix3::SetColumn(unsigned int p_column_index, const Vector3& p_column_vector) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				m_elements[row][p_column_index] = p_column_vector[row];
			}
		}

		SCALAR& Matrix3::operator()(unsigned int p_row, unsigned int p_col) {
			return m_elements[p_row][p_col];
		}

		Matrix3 Matrix3::operator-() const {
			Matrix3 result;
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					result.m_elements[row][col] = -result.m_elements[row][col];
				}
			}

			return result;
		}

		Matrix3& Matrix3::operator+=(const Matrix3& p_rhs) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					m_elements[row][col] += p_rhs.m_elements[row][col];
				}
			}

			return *this;
		}

		Matrix3& Matrix3::operator-=(const Matrix3& p_rhs) {
			return *this += (-p_rhs);
		}

		Matrix3& Matrix3::operator*=(SCALAR p_rhs) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					m_elements[row][col] *= p_rhs;
				}
			}

			return *this;
		}

		Matrix3& Matrix3::operator*=(const Matrix3& p_rhs) {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				Vector3 temp = GetRow(row);
				for (int col = 0; col < K_DIMENSIONS; ++col) {
					m_elements[row][col] = Dot(temp, p_rhs.GetColumn(col));
				}
			}

			return *this;
		}

		Matrix3& Matrix3::operator/=(SCALAR p_rhs) {
			return *this *= (1.0f / p_rhs);
		}


		SCALAR Matrix3::Trace() const {
			SCALAR trace = 0;
			for (int i = 0; i < K_DIMENSIONS; ++i) {
				trace += m_elements[i][i];
			}

			return trace;
		}

		SCALAR Matrix3::Determinant() const {
			SCALAR determinant = 0;
			for (int i = 0; i < K_DIMENSIONS; ++i) {
				determinant += ((i % 2 == 0) ? 1.0f : -1.0f) * m_elements[0][i] * GetMinorMatrix(0, i).Determinant();
			}

			return determinant;
		}


		Matrix3& Matrix3::Transpose() {
			for (int row = 0; row < K_DIMENSIONS; ++row) {
				for (int col = row + 1; col < K_DIMENSIONS; ++col) {
					SCALAR temp = m_elements[col][row];
					m_elements[col][row] = m_elements[row][col];
					m_elements[row][col] = temp;
				}
			}
			
			return *this;
		}

		Matrix3& Matrix3::Invert() {
			SCALAR determinant = Determinant();

			if (FloatCompare(determinant, 0.0f)) throw r2ExceptionDivisionByZeroM("Singular matrix cannot be inverted");

			*this = GetAdjugate(*this) / determinant;
			return *this;
		}

		Matrix2 Matrix3::GetMinorMatrix(unsigned int p_row_to_remove, unsigned int p_col_to_remove) const {
			Matrix2 minor;
		
			int minorRow = 0;
			for (int i = 0; i < K_DIMENSIONS; ++i) {
				if (i == p_row_to_remove) continue;

				int minorCol = 0;
				for (int k = 0; k < K_DIMENSIONS; ++k) {
					if (k == p_col_to_remove) continue;

					minor.m_elements[minorRow][minorCol] = m_elements[i][k];
					++minorCol;
				}

				++minorRow;
			}

			return minor;
		}

		Matrix3 operator*(const Matrix3& p_lhs, SCALAR p_rhs) {
			return (Matrix3(p_lhs) *= p_rhs);
		}

		Matrix3 operator*(SCALAR p_lhs, const Matrix3& p_rhs) {
			return p_rhs * p_lhs;
		}

		Matrix3 operator/(const Matrix3& p_lhs, SCALAR p_rhs) {
			return p_lhs * (1.0f / p_rhs);
		}

		Matrix3 operator+(const Matrix3& p_lhs, const Matrix3& p_rhs) {
			return (Matrix3(p_lhs) += p_rhs);
		}

		Matrix3 operator-(const Matrix3& p_lhs, const Matrix3& p_rhs) {
			return (Matrix3(p_lhs) -= p_rhs);
		}

		Matrix3 operator*(const Matrix3& p_lhs, const Matrix3& p_rhs) {
			return (Matrix3(p_lhs) *= p_rhs);
		}

		Vector3 operator*(const Matrix3& p_lhs, const Vector3& p_rhs) {
			Vector3 result;
			for (int row = 0; row < Matrix2::K_DIMENSIONS; ++row) {
				result[row] = Dot(p_lhs.GetRow(row), p_rhs);
			}

			return result;
		}

		bool operator==(const Matrix3& p_lhs, const Matrix3& p_rhs) {
			for (int row = 0; row < Matrix3::K_DIMENSIONS; ++row) {
				for (int col = 0; col < Matrix3::K_DIMENSIONS; ++col) {
					if (!FloatCompare(p_lhs.m_elements[row][col], p_rhs.m_elements[row][col])) return false;
				}
			}

			return true;
		}

		bool operator!=(const Matrix3& p_lhs, const Matrix3& p_rhs) {
			return !(p_lhs == p_rhs);
		}

		std::ostream& operator<<(std::ostream& p_lhs, const Matrix3& p_rhs) {
			for (int row = 0; row < Matrix3::K_DIMENSIONS; ++row) {
				p_lhs << "[";
				
				for (int col = 0; col < Matrix3::K_DIMENSIONS; ++col) {
					p_lhs << p_rhs.m_elements[row][col];

					if (col != Matrix3::K_DIMENSIONS - 1) p_lhs << ", ";
				}

				p_lhs << "]";
				if (row != Matrix3::K_DIMENSIONS - 1) p_lhs << std::endl;
			}

			return p_lhs;
		}




		SCALAR Trace(const Matrix3& p_matrix) {
			return p_matrix.Trace();
		}

		SCALAR Determinant(const Matrix3& p_matrix) {
			return p_matrix.Determinant();
		}

		Matrix3 GetTranspose(const Matrix3& p_matrix) {
			return Matrix3(p_matrix).Transpose();
		}

		Matrix3 GetMatrixOfMinors(const Matrix3& p_matrix) {
			Matrix3 result;
			for (int row = 0; row < Matrix3::K_DIMENSIONS; ++row) {
				for (int col = 0; col < Matrix3::K_DIMENSIONS; ++col) {
					result.m_elements[row][col] = p_matrix.GetMinorMatrix(row, col).Determinant();
				}
			}

			return result;
		}

		Matrix3 GetMatrixOfCofactors(const Matrix3& p_matrix) {
			Matrix3 result = GetMatrixOfMinors(p_matrix);
			for (int row = 0; row < Matrix3::K_DIMENSIONS; ++row) {
				for (int col = 0; col < Matrix3::K_DIMENSIONS; ++col) {
					if (!IsEven(row + col)) result.m_elements[row][col] = -result.m_elements[row][col];
				}
			}

			return result;
		}

		Matrix3 GetAdjugate(const Matrix3& p_matrix) {
			return GetMatrixOfCofactors(p_matrix).Transpose();
		}

		Matrix3 GetInverse(const Matrix3& p_matrix) {
			return Matrix3(p_matrix).Invert();
		}
	}
}