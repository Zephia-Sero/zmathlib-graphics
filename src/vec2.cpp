#include "mathtype.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>

using namespace ZMathLib_Graphics;

Vec2 Vec2::Zero() { return Vec2(0, 0); }
Vec2 Vec2::One() { return Vec2(1, 1); }
Vec2 Vec2::X() { return Vec2(1, 0); }
Vec2 Vec2::Y() { return Vec2(0, 1); }

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(MATHTYPE v) : x(v), y(v) {}
Vec2::Vec2(MATHTYPE x, MATHTYPE y) : x(x), y(y) {}
Vec2::Vec2(Vec2 const &from) : x(from.x), y(from.y) {}
Vec2 Vec2::operator=(Vec2 const &from)
{
	return Vec2(from);
}
/* Vec2::Vec2(Matrix const &mtx) */
/* { */
/* 	if (mtx.width != 1) */
/* 		throw std::invalid_argument("Vec2(Matrix) expects matrix with width of 1"); */
/* 	if (mtx.height != 2) */
/* 		throw std::invalid_argument("Vec2(Matrix) expects matrix with height of 2"); */
/* 	x = mtx.get(0, 0); */
/* 	y = mtx.get(0, 1); */
/* } */

MATHTYPE Vec2::shortened() const
{
	return x;
}

Vec3 Vec2::extended(float z) const
{
	return Vec3(x, y, z);
}

Vec2 Vec2::operator+() const
{
	return *this;
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

#define VEC2_VEC_OP(op) \
Vec2 Vec2::operator op(Vec2 const &other) const \
{ \
	return Vec2(x op other.x, y op other.y); \
}

#define VEC2_VEC_OP_CALL(op, call) \
Vec2 Vec2::operator op(Vec2 const &other) const \
{ \
	return Vec2(call(x, other.x), call(y, other.y)); \
}
#define VEC2_VEC_ASSIGN_OP(op) \
Vec2 Vec2::operator op(Vec2 const &other) \
{ \
	return Vec2(x op other.x, y op other.y); \
}

#define VEC2_VEC_ASSIGN_OP_CALL(opn, call) \
Vec2 Vec2::operator opn(Vec2 const &other) \
{ \
	return Vec2(x = call(x, other.x), y = call(y, other.y)); \
}

std::ostream &operator<<(std::ostream &os, Vec2 const &vec)
{
	os << "Vec2(" << vec.x << ", " << vec.y << ")";
	return os;
}

#define VEC2_SCALAR_OP(op) \
Vec2 Vec2::operator op(MATHTYPE const other) const \
{ \
	return Vec2(x op other, y op other); \
}
#define VEC2_SCALAR_ASSIGN_OP(op) \
Vec2 Vec2::operator op(MATHTYPE const other) \
{ \
	return Vec2(x op other, y op other); \
}
#define VEC2_SCALAR_OP_CALL(op, call) \
Vec2 Vec2::operator op(MATHTYPE const other) const \
{ \
	return Vec2(call(x, other), call(y, other)); \
}
#define VEC2_SCALAR_ASSIGN_OP_CALL(opn, call) \
Vec2 Vec2::operator opn(MATHTYPE const other) \
{ \
	return Vec2(x = call(x, other), y = call(y, other)); \
}


VEC2_VEC_OP(+);
VEC2_VEC_OP(-);
VEC2_VEC_OP(*);
VEC2_VEC_OP(/);
VEC2_VEC_OP_CALL(%, fmod);
VEC2_VEC_ASSIGN_OP(+=);
VEC2_VEC_ASSIGN_OP(-=);
VEC2_VEC_ASSIGN_OP(*=);
VEC2_VEC_ASSIGN_OP(/=);
VEC2_VEC_ASSIGN_OP_CALL(%=, fmod);

VEC2_SCALAR_OP(+);
VEC2_SCALAR_OP(-);
VEC2_SCALAR_OP(*);
VEC2_SCALAR_OP(/);
VEC2_SCALAR_OP_CALL(%, fmod);
VEC2_SCALAR_ASSIGN_OP(+=);
VEC2_SCALAR_ASSIGN_OP(-=);
VEC2_SCALAR_ASSIGN_OP(*=);
VEC2_SCALAR_ASSIGN_OP(/=);
VEC2_SCALAR_ASSIGN_OP_CALL(%=, fmod);

MATHTYPE Vec2::length_squared() const
{
	return x * x + y * y;
}
MATHTYPE Vec2::length() const
{
	return std::sqrt(length_squared());
}

void Vec2::normalize()
{
	auto len = length();
	x /= len;
	y /= len;
}
Vec2 Vec2::normalized() const
{
	Vec2 ret(*this);
	ret.normalize();
	return ret;
}
void Vec2::scale(MATHTYPE const factor)
{
	x *= factor;
	y *= factor;
}
Vec2 Vec2::scaled(MATHTYPE const factor) const
{
	Vec2 ret(*this);
	ret.scale(factor);
	return ret;
}
void Vec2::limit_length(MATHTYPE const maxLength, MATHTYPE const minLength)
{
	auto lenSqr = length_squared();
	auto minTgtLenSqr = minLength * minLength;
	auto maxTgtLenSqr = maxLength * maxLength;
	if (lenSqr > maxTgtLenSqr) {
		// sqrt(a^2 / b^2) == sqrt(a^2) / sqrt(b^2); you can save a sqrt this way.
		auto scaleBy = std::sqrt(maxTgtLenSqr / lenSqr);
		scale(scaleBy);
	} else if (lenSqr < minTgtLenSqr) {
		auto scaleBy = std::sqrt(minTgtLenSqr / lenSqr);
		scale(scaleBy);
	}
}
Vec2 Vec2::limited_length(MATHTYPE const maxLength, MATHTYPE const minLength) const
{
	Vec2 ret(*this);
	ret.limit_length(maxLength, minLength);
	return ret;
}
void Vec2::clamp(MATHTYPE const min, MATHTYPE const max)
{
	x = std::clamp(x, min, max);
	y = std::clamp(y, min, max);
}
Vec2 Vec2::clamped(MATHTYPE const min, MATHTYPE const max) const
{
	Vec2 ret(*this);
	ret.clamp(min, max);
	return ret;
}

MATHTYPE Vec2::dot(Vec2 const &other) const
{
	return (x * other.x) + (y * other.y);
}

MATHTYPE Vec2::angle(Vec2 const &other) const
{
	MATHTYPE dotProd = dot(other);
	MATHTYPE magnitudes = std::sqrt(length_squared() * other.length_squared());
	MATHTYPE cosValue = dotProd / magnitudes;
	MATHTYPE angle = std::acos(cosValue);
	return angle;
}

MATHTYPE Vec2::angle() const
{
	return Vec2::angle(Vec2(1, 0));
}

MATHTYPE Vec2::projected_length(Vec2 const &other) const
{
	MATHTYPE magnitude = length();
	MATHTYPE vecAngle = angle(other);
	return magnitude * std::cos(vecAngle);
}

void Vec2::project(Vec2 const &other)
{
	Vec2 projVecCopy = projected(other);
	x = projVecCopy.x;
	y = projVecCopy.y;
}

Vec2 Vec2::projected(Vec2 const &other) const
{
	Vec2 otherNormal = other.normalized();
	MATHTYPE projLength = projected_length(other);
	return otherNormal * projLength;
}

void Vec2::reject(Vec2 const &other)
{
	Vec2 proj = projected(other);
	x -= proj.x;
	y -= proj.y;
}

Vec2 Vec2::rejected(Vec2 const &other) const
{
	return *this - projected(other);
}

#ifndef MIN_ERROR_EQUAL
#define MIN_ERROR_EQUAL 0.0001
#endif
bool Vec2::operator==(Vec2 const &other) const
{
	return (fabs(x - other.x) < (MIN_ERROR_EQUAL)) && (fabs(y - other.y) < (MIN_ERROR_EQUAL));
}

bool Vec2::operator!=(Vec2 const &other) const
{
	return !(*this == other);
}

ZMathLib_Graphics::Vec2 operator+(MATHTYPE const a, ZMathLib_Graphics::Vec2 b)
{
	return b + a;
}
ZMathLib_Graphics::Vec2 operator-(MATHTYPE const a, ZMathLib_Graphics::Vec2 b)
{
	return Vec2(a) - b;
}
ZMathLib_Graphics::Vec2 operator*(MATHTYPE const a, ZMathLib_Graphics::Vec2 b)
{
	return b * a;
}
ZMathLib_Graphics::Vec2 operator/(MATHTYPE const a, ZMathLib_Graphics::Vec2 b)
{
	return Vec2(a) / b;
}
ZMathLib_Graphics::Vec2 operator%(MATHTYPE const a, ZMathLib_Graphics::Vec2 b)
{
	return Vec2(a) % b;
}

// Converts Vec2 to a 2x1 matrix
Matrix Vec2::to_row() const
{
	Matrix ret(2, 1);
	ret.set(0, 0, x);
	ret.set(1, 0, y);
	return ret;
}
// Converts Vec2 to a 1x2 matrix
Matrix Vec2::to_column() const
{
	Matrix ret(1, 2);
	ret.set(0, 0, x);
	ret.set(0, 1, y);
	return ret;
}
// Converts Vec2 to a 3x1 matrix, with z as the rightmost component (defaults to z=0)
Matrix Vec2::to_row3(MATHTYPE z) const
{
	return Vec3(x, y, z).to_row();
}
// Converts Vec2 to a 1x3 matrix, with z as the lowest component (defaults to z=0)
Matrix Vec2::to_column3(MATHTYPE z) const
{
	return Vec3(x, y, z).to_column();
}
// Converts Vec2 to a 4x1 matrix, with w as the rightmost component, z the 2nd-rightmost (defaults to z=0, w=0)
Matrix Vec2::to_row4(MATHTYPE z, MATHTYPE w) const
{
	return Vec4(x, y, z, w).to_row();

}
// Converts Vec2 to a 4x1 matrix, with w as the lowest component, z the 2nd-lowest (defaults to z=0, w=0)
Matrix Vec2::to_column4(MATHTYPE z, MATHTYPE w) const
{
	return Vec4(x, y, z, w).to_column();
}


