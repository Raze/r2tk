#include "r2-vector-3.hpp"
#include "r2-exception.hpp"
#include <cmath>
#include <cstring>
#include <limits>

namespace r2
{
	namespace Math
	{
		const Vector3 Vector3::K_ZERO(0, 0, 0);
		const Vector3 Vector3::K_AXIS_X(1, 0, 0);
		const Vector3 Vector3::K_AXIS_Y(0, 1, 0);
		const Vector3 Vector3::K_AXIS_Z(0, 0, 1);

		Vector3::Vector3() : x(0), y(0), z(0) {}
		Vector3::Vector3(SCALAR p_x, SCALAR p_y, SCALAR p_z) : x(p_x), y(p_y), z(p_z) {}
		Vector3::Vector3(const SCALAR* p_raw_data) {
			memcpy(m_data, p_raw_data, sizeof(m_data));
		}


		SCALAR& Vector3::operator[](unsigned int p_index) {
			return m_data[p_index];
		}

		SCALAR Vector3::operator[](unsigned int p_index) const {
			return m_data[p_index];
		}

		Vector3& Vector3::operator-() {
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		Vector3& Vector3::operator+=(const Vector3& p_rhs) {
			x += p_rhs.x;
			y += p_rhs.y;
			z += p_rhs.z;
			return *this;
		}

		Vector3& Vector3::operator-=(const Vector3& p_rhs) {
			x -= p_rhs.x;
			y -= p_rhs.y;
			z -= p_rhs.z;
			return *this;
		}

		Vector3& Vector3::operator*=(SCALAR p_rhs) {
			x *= p_rhs;
			y *= p_rhs;
			z *= p_rhs;
			return *this;
		}

		Vector3& Vector3::operator/=(SCALAR p_rhs) {
			x /= p_rhs;
			y /= p_rhs;
			z /= p_rhs;
			return *this;
		}


		SCALAR Vector3::Dot(const Vector3& p_rhs) const {
			return x * p_rhs.x + y * p_rhs.y + z * p_rhs.z;
		}

		Vector3 Vector3::Cross(const Vector3& p_rhs) const {
			return Vector3(y * p_rhs.z - z * p_rhs.y,
						   z * p_rhs.x - x * p_rhs.z,
						   x * p_rhs.y - y * p_rhs.x);
		}

		SCALAR Vector3::Length() const {
			return std::sqrt(LengthSquared());
		}

		SCALAR Vector3::LengthSquared() const {
			return Dot(*this);
		}

		Vector3& Vector3::Normalize() {
			return (*this /= Length());
		}



		Vector3 operator+(const Vector3& p_lhs, const Vector3& p_rhs) {
			return Vector3(p_lhs.x + p_rhs.x,
						   p_lhs.y + p_rhs.y,
						   p_lhs.z + p_rhs.z);
		}

		Vector3 operator-(const Vector3& p_lhs, const Vector3& p_rhs) {
			return Vector3(p_lhs.x - p_rhs.x,
						   p_lhs.y - p_rhs.y,
						   p_lhs.z - p_rhs.z);
		}

		Vector3 operator*(const Vector3& p_lhs, SCALAR p_rhs) {
			return (Vector3(p_lhs) *= p_rhs);
		}

		Vector3 operator*(SCALAR p_lhs, const Vector3& p_rhs) {
			return p_rhs * p_lhs;
		}

		Vector3 operator/(const Vector3& p_lhs, SCALAR p_rhs) {
			return p_lhs * (1.0f / p_rhs);
		}

		bool operator==(const Vector3& p_lhs, const Vector3& p_rhs) {
			return FloatCompare(p_lhs.x, p_rhs.x) && FloatCompare(p_lhs.y, p_rhs.y) && FloatCompare(p_lhs.z, p_rhs.z);
		}

		bool operator!=(const Vector3& p_lhs, const Vector3& p_rhs) {
			return !(p_lhs == p_rhs);
		}

		bool operator<(const Vector3& p_lhs, const Vector3& p_rhs) {
			return p_lhs.LengthSquared() < p_rhs.LengthSquared();
		}

		bool operator>(const Vector3& p_lhs, const Vector3& p_rhs) {
			return p_lhs.LengthSquared() > p_rhs.LengthSquared();
		}

		bool operator<=(const Vector3& p_lhs, const Vector3& p_rhs) {
			return p_lhs.LengthSquared() <= p_rhs.LengthSquared();
		}

		bool operator>=(const Vector3& p_lhs, const Vector3& p_rhs) {
			return p_lhs.LengthSquared() >= p_rhs.LengthSquared();
		}

		std::ostream& operator<<(std::ostream& p_lhs, const Vector3& p_rhs) {
			return p_lhs << "(" << p_rhs.x << ", " << p_rhs.y << ", " << p_rhs.z << ")";
		}

		std::istream& operator>>(std::istream& p_lhs, Vector3& p_rhs) {
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), '(');
			p_lhs >> p_rhs.x;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			p_lhs >> p_rhs.y;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			p_lhs >> p_rhs.z;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ')');
			return p_lhs;
		}


		SCALAR Dot(const Vector3& p_lhs, const Vector3& p_rhs) {
			return p_lhs.Dot(p_rhs);
		}

		Vector3 Cross(const Vector3& p_lhs, const Vector3& p_rhs) {
			return p_lhs.Cross(p_rhs);
		}

		SCALAR Length(const Vector3& p_vector) {
			return p_vector.Length();
		}

		SCALAR LengthSquared(const Vector3& p_vector) {
			return p_vector.LengthSquared();
		}

		Vector3 GetNormalized(const Vector3& p_vector) {
			return p_vector / p_vector.Length();
		}


	}
}