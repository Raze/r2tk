#include "r2-vector-4.hpp"
#include "r2-exception.hpp"
#include <cmath>
#include <cstring>
#include <limits>

namespace r2
{
	namespace Math
	{
		const Vector4 Vector4::K_ZERO(0, 0, 0, 0);
		const Vector4 Vector4::K_AXIS_X(1, 0, 0, 0);
		const Vector4 Vector4::K_AXIS_Y(0, 1, 0, 0);
		const Vector4 Vector4::K_AXIS_Z(0, 0, 1, 0);
		const Vector4 Vector4::K_AXIS_W(0, 0, 0, 1);

		Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
		Vector4::Vector4(SCALAR p_x, SCALAR p_y, SCALAR p_z, SCALAR p_w) : x(p_x), y(p_y), z(p_z), w(p_w) {}
		Vector4::Vector4(const SCALAR* p_raw_data) {
			memcpy(m_data, p_raw_data, sizeof(m_data));
		}

		SCALAR& Vector4::operator[](unsigned int p_index) {
			return m_data[p_index];
		}

		SCALAR Vector4::operator[](unsigned int p_index) const {
			return m_data[p_index];
		}

		Vector4& Vector4::operator-() {
			x = -x;
			y = -y;
			z = -z;
			w = -w;
			return *this;
		}

		Vector4& Vector4::operator+=(const Vector4& p_rhs) {
			x += p_rhs.x;
			y += p_rhs.y;
			z += p_rhs.z;
			w += p_rhs.w;
			return *this;
		}

		Vector4& Vector4::operator-=(const Vector4& p_rhs) {
			x -= p_rhs.x;
			y -= p_rhs.y;
			z -= p_rhs.z;
			w -= p_rhs.w;
			return *this;
		}

		Vector4& Vector4::operator*=(SCALAR p_rhs) {
			x *= p_rhs;
			y *= p_rhs;
			z *= p_rhs;
			w *= p_rhs;
			return *this;
		}

		Vector4& Vector4::operator/=(SCALAR p_rhs) {
			x /= p_rhs;
			y /= p_rhs;
			z /= p_rhs;
			w /= p_rhs;
			return *this;
		}


		SCALAR Vector4::Dot(const Vector4& p_rhs) const {
			return x * p_rhs.x + y * p_rhs.y + z * p_rhs.z + w * p_rhs.w;
		}

		SCALAR Vector4::Length() const {
			return std::sqrt(LengthSquared());
		}

		SCALAR Vector4::LengthSquared() const {
			return Dot(*this);
		}

		Vector4& Vector4::Normalize() {
			return (*this /= Length());
		}




		Vector4 operator+(const Vector4& p_lhs, const Vector4& p_rhs) {
			return Vector4(p_lhs.x + p_rhs.x,
						   p_lhs.y + p_rhs.y,
						   p_lhs.z + p_rhs.z,
						   p_lhs.w + p_rhs.w);
		}

		Vector4 operator-(const Vector4& p_lhs, const Vector4& p_rhs) {
			return Vector4(p_lhs.x - p_rhs.x,
						   p_lhs.y - p_rhs.y,
						   p_lhs.z - p_rhs.z,
						   p_lhs.w - p_rhs.w);
		}

		Vector4 operator*(const Vector4& p_lhs, SCALAR p_rhs) {
			return (Vector4(p_lhs) *= p_rhs);
		}

		Vector4 operator*(SCALAR p_lhs, const Vector4& p_rhs) {
			return p_rhs * p_lhs;
		}

		Vector4 operator/(const Vector4& p_lhs, SCALAR p_rhs) {
			return p_lhs * (1.0f / p_rhs);
		}

		bool operator==(const Vector4& p_lhs, const Vector4& p_rhs) {
			return FloatCompare(p_lhs.x, p_rhs.x) && FloatCompare(p_lhs.y, p_rhs.y) && FloatCompare(p_lhs.z, p_rhs.z) && FloatCompare(p_lhs.w, p_rhs.w);
		}

		bool operator!=(const Vector4& p_lhs, const Vector4& p_rhs) {
			return !(p_lhs == p_rhs);
		}

		bool operator<(const Vector4& p_lhs, const Vector4& p_rhs) {
			return p_lhs.LengthSquared() < p_rhs.LengthSquared();
		}

		bool operator>(const Vector4& p_lhs, const Vector4& p_rhs) {
			return p_lhs.LengthSquared() > p_rhs.LengthSquared();
		}

		bool operator<=(const Vector4& p_lhs, const Vector4& p_rhs) {
			return p_lhs.LengthSquared() <= p_rhs.LengthSquared();
		}

		bool operator>=(const Vector4& p_lhs, const Vector4& p_rhs) {
			return p_lhs.LengthSquared() >= p_rhs.LengthSquared();
		}

		std::ostream& operator<<(std::ostream& p_lhs, const Vector4& p_rhs) {
			return p_lhs << "(" << p_rhs.x << ", " << p_rhs.y << ", " << p_rhs.z << ", " << p_rhs.w << ")";
		}

		std::istream& operator>>(std::istream& p_lhs, Vector4& p_rhs) {
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), '(');
			p_lhs >> p_rhs.x;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			p_lhs >> p_rhs.y;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			p_lhs >> p_rhs.z;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			p_lhs >> p_rhs.w;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ')');
			return p_lhs;
		}

		SCALAR Dot(const Vector4& p_lhs, const Vector4& p_rhs) {
			return p_lhs.Dot(p_rhs);
		}

		SCALAR Length(const Vector4& p_vector) {
			return p_vector.Length();
		}

		SCALAR LengthSquared(const Vector4& p_vector) {
			return p_vector.LengthSquared();
		}

		Vector4 GetNormalized(const Vector4& p_vector) {
			return p_vector / p_vector.Length();
		}
	}
}