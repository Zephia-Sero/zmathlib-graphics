#include "quaternion.hpp"
#include "mathtype.hpp"
#include "matrix.hpp"
#include "vector.hpp"
using namespace ZMathLib_Graphics;

Quaternion Quaternion::Zero()
{
	return Quaternion(0, 0, 0, 0);
}
Quaternion Quaternion::One()
{
	return Quaternion(1, 1, 1, 1);
}
Quaternion Quaternion::R()
{
	return Quaternion(1, 0, 0, 0);
}
Quaternion Quaternion::I()
{
	return Quaternion(0, 1, 0, 0);
}
Quaternion Quaternion::J()
{
	return Quaternion(0, 0, 1, 0);
}
Quaternion Quaternion::K()
{
	return Quaternion(0, 0, 0, 1);
}
Matrix Quaternion::to_row() const
{
	return _vec.to_row();
}
Matrix Quaternion::to_column() const
{
	return _vec.to_column();
}
Vec4 Quaternion::to_vec4() const
{
	return _vec;
}

void Quaternion::conjugate()
{
	_vec = -_vec;
	_vec.x = -_vec.x; // reset
}

Quaternion Quaternion::conjugated() const
{
	Quaternion ret(*this);
	ret._vec.x = -ret._vec.x; // reset
	return ret;
}

Quaternion::Quaternion() : _vec(Vec4(0, 0, 0, 0)) {}
Quaternion::Quaternion(MATHTYPE v) : _vec(Vec4(v, v, v, v)) {}
Quaternion::Quaternion(MATHTYPE r, MATHTYPE i, MATHTYPE j, MATHTYPE k) : _vec(r, i, j, k) {}
Quaternion::Quaternion(Quaternion const &from) : _vec(from._vec) {}
Quaternion::Quaternion(Vec4 const &from) : _vec(from) {}

Quaternion Quaternion::operator+() const
{
	return *this;
}
Quaternion Quaternion::operator-() const
{
	return Quaternion(-_vec);
}

#define QUAT_OP(op, con) \
Quaternion Quaternion::operator op(Quaternion const &other) con \
{ \
	return Quaternion(_vec op other._vec); \
}

QUAT_OP(+,const)
QUAT_OP(-,const)
QUAT_OP(+=,)
QUAT_OP(-=,)

Quaternion Quaternion::operator*(Quaternion const &other) const
{
	/* (a+bi+cj+dk) (e+fi+gj+hk) */
	/* = ae + afi + agj + ahk */
	/* + bie + bifi + bigj + bihk */
	/* + cje + cjfi + cjgj + cjhk */
	/* + dke + dkfi + dkgj + dkhk */
	/* = ae + afi + agj + ahk */
	/* + bei - bf + bgk - bhj */
	/* + cej - cfk - cg + chi */
	/* + dek + dfj - dgi - dh */
	/* = (ae - bf - cg - dh) + (afi + bei + chi - dgi) + (agj - bhj + cej + dfj) + (ahk + bgk - cfk + dek) */
	return Quaternion(
		_vec.x * other._vec.x - _vec.y * other._vec.y - _vec.z * other._vec.z - _vec.w * other._vec.w,
		_vec.x * other._vec.y + _vec.y * other._vec.x + _vec.z * other._vec.w - _vec.w * other._vec.z,
		_vec.x * other._vec.z - _vec.y * other._vec.w + _vec.z * other._vec.x + _vec.w * other._vec.y,
		_vec.x * other._vec.w + _vec.y * other._vec.z - _vec.z * other._vec.y + _vec.w * other._vec.x
	);
}
Quaternion Quaternion::operator*=(Quaternion const &other)
{
	Quaternion ret = *this * other;
	_vec = ret._vec;
	return ret;
}
Quaternion Quaternion::operator/(Quaternion const &other) const
{
	// (A / B) * 1 = (A / B)
	// conj(B) / conj(B) = 1
	// (A / B) * conj(B) / conj(B) = Aconj(B) / (Bconj(B))
	// Bconj(B) = -||B||^2
	// A/B = (A * conjB) / -||B||^2
	MATHTYPE denominator = -other.length_squared();
	Quaternion conjB = other.conjugated();
	return (*this * conjB) / denominator;
}
Quaternion Quaternion::operator/=(Quaternion const &other)
{
	Quaternion ret = *this / other;
	_vec = ret._vec;
	return ret;
}

MATHTYPE Quaternion::r() const { return _vec.x; }
MATHTYPE Quaternion::i() const { return _vec.y; }
MATHTYPE Quaternion::j() const { return _vec.z; }
MATHTYPE Quaternion::k() const { return _vec.w; }

std::ostream &operator<<(std::ostream &os, ZMathLib_Graphics::Quaternion const &quat)
{
	os << "Quaternion(" << quat.r() << ", " << quat.i() << ", " << quat.j() << ", " << quat.k() << ")";
	return os;
}

MATHTYPE Quaternion::length() const
{
	return _vec.length();
}
MATHTYPE Quaternion::length_squared() const
{
	return _vec.length_squared();
}

void Quaternion::normalize()
{
	_vec.normalize();
}
Quaternion Quaternion::normalized() const
{
	Quaternion quat(*this);
	quat.normalize();
	return quat;
}
// Roughly equivalent to `quaternion *= factor`
void Quaternion::scale(MATHTYPE const factor)
{
	_vec.scale(factor);
}
// Equivalent to `quaternion * factor`
Quaternion Quaternion::scaled(MATHTYPE const factor) const
{
	Quaternion ret(*this);
	ret.scale(factor);
	return ret;
}
// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
void Quaternion::limit_length(MATHTYPE const maxLength, MATHTYPE const minLength)
{
	_vec.limit_length(maxLength, minLength);
}
// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
Quaternion Quaternion::limited_length(MATHTYPE const maxLength, MATHTYPE const minLength) const
{
	Quaternion quat(*this);
	quat.limit_length(maxLength, minLength);
	return quat;
}
// Limits each component to [min, max]
void Quaternion::clamp(MATHTYPE const min, MATHTYPE const max)
{
	_vec.clamp(min, max);
}
// Limits each component to [min, max]
Quaternion Quaternion::clamped(MATHTYPE const min, MATHTYPE const max) const
{
	Quaternion ret(*this);
	ret.clamp(min, max);
	return ret;
}

Quaternion Quaternion::operator+(MATHTYPE const other) const
{
	Quaternion ret(*this);
	ret._vec.x += other;
	return ret;
}
Quaternion Quaternion::operator+=(MATHTYPE const other)
{
	_vec.x += other;
	return *this;
}
Quaternion Quaternion::operator-(MATHTYPE const other) const
{
	Quaternion ret(*this);
	ret._vec.x -= other;
	return ret;
}
Quaternion Quaternion::operator-=(MATHTYPE const other)
{
	_vec.x -= other;
	return *this;
}
Quaternion Quaternion::operator*(MATHTYPE const other) const
{
	return Quaternion(_vec * other);
}
Quaternion Quaternion::operator*=(MATHTYPE const other)
{
	return Quaternion(_vec *= other);
}
Quaternion Quaternion::operator/(MATHTYPE const other) const
{
	return Quaternion(_vec / other);
}
Quaternion Quaternion::operator/=(MATHTYPE const other)
{
	return Quaternion(_vec /= other);
}
