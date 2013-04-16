#include "r2-vector-2.hpp"
#include "r2-exception.hpp"
#include <cmath>
#include <cstring>
#include <limits>

namespace r2
{
	namespace Math
	{
		const Vector2 Vector2::K_ZERO(0, 0);
		const Vector2 Vector2::K_AXIS_X(1, 0);
		const Vector2 Vector2::K_AXIS_Y(0, 1);

		Vector2::Vector2() : x(0), y(0) {}
		Vector2::Vector2(SCALAR p_x, SCALAR p_y) : x(p_x), y(p_y) {}
		Vector2::Vector2(const SCALAR* p_raw_data) {
			memcpy(m_data, p_raw_data, sizeof(m_data));
		}

		SCALAR& Vector2::operator[](unsigned int p_index) {
			return m_data[p_index];
		}

		SCALAR Vector2::operator[](unsigned int p_index) const {
			return m_data[p_index];
		}

		Vector2& Vector2::operator-() {
			x = -x;
			y = -y;
			return *this;
		}

		Vector2& Vector2::operator+=(const Vector2& p_rhs) {
			x += p_rhs.x;
			y += p_rhs.y;
			return *this;
		}

		Vector2& Vector2::operator-=(const Vector2& p_rhs) {
			x -= p_rhs.x;
			y -= p_rhs.y;
			return *this;
		}

		Vector2& Vector2::operator*=(SCALAR p_rhs) {
			x *= p_rhs;
			y *= p_rhs;
			return *this;
		}

		Vector2& Vector2::operator/=(SCALAR p_rhs) {
			x /= p_rhs;
			y /= p_rhs;
			return *this;
		}

		SCALAR Vector2::Dot(const Vector2& p_rhs) const
		{
			return x * p_rhs.x + y * p_rhs.y;
		}

		SCALAR Vector2::Length() const
		{
			return std::sqrt(LengthSquared());
		}

		SCALAR Vector2::LengthSquared() const
		{
			return Dot(*this);
		}

		Vector2& Vector2::Normalize()
		{
			return (*this /= Length());
		}




		Vector2 operator+(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return Vector2(p_lhs.x + p_rhs.x,
						   p_lhs.y + p_rhs.y);
		}

		Vector2 operator-(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return Vector2(p_lhs.x - p_rhs.x,
						   p_lhs.y - p_rhs.y);
		}

		Vector2 operator*(const Vector2& p_lhs, SCALAR p_rhs)
		{
			return (Vector2(p_lhs) *= p_rhs);
		}

		Vector2 operator*(SCALAR p_lhs, const Vector2& p_rhs)
		{
			return p_rhs * p_lhs;
		}

		Vector2 operator/(const Vector2& p_lhs, SCALAR p_rhs)
		{
			return p_lhs * (1.0f / p_rhs);
		}

		bool operator==(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return FloatCompare(p_lhs.x, p_rhs.x) && FloatCompare(p_lhs.y, p_rhs.y);
		}

		bool operator!=(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return !(p_lhs == p_rhs);
		}

		bool operator<(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return p_lhs.LengthSquared() < p_rhs.LengthSquared();
		}

		bool operator>(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return p_lhs.LengthSquared() > p_rhs.LengthSquared();
		}

		bool operator<=(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return p_lhs.LengthSquared() <= p_rhs.LengthSquared();
		}

		bool operator>=(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return p_lhs.LengthSquared() >= p_rhs.LengthSquared();
		}

		std::ostream& operator<<(std::ostream& p_lhs, const Vector2& p_rhs) {
			return p_lhs << "(" << p_rhs.x << ", " << p_rhs.y << ")";
		}

		std::istream& operator>>(std::istream& p_lhs, Vector2& p_rhs) {
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), '(');
			p_lhs >> p_rhs.x;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			p_lhs >> p_rhs.y;
			p_lhs.ignore(std::numeric_limits<std::streamsize>::max(), ')');
			return p_lhs;
		}





		SCALAR Dot(const Vector2& p_lhs, const Vector2& p_rhs)
		{
			return p_lhs.Dot(p_rhs);
		}

		SCALAR Length(const Vector2& p_vector)
		{
			return p_vector.Length();
		}

		SCALAR LengthSquared(const Vector2& p_vector)
		{
			return p_vector.LengthSquared();
		}

		Vector2 GetNormalized(const Vector2& p_vector)
		{
			return p_vector / p_vector.Length();
		}

		Vector2 GetNormal(const Vector2& p_vector, bool p_right_hand)
		{
			if (p_right_hand) return Vector2(p_vector.y, -p_vector.x);
			else			  return Vector2(-p_vector.y, p_vector.x);
		}
	}
}