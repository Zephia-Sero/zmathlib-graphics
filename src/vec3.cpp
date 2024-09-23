#include "matrix.hpp"
#include "vector.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>

using namespace ZMathLib_Graphics;

Vec3 Vec3::Zero() { return Vec3(0, 0, 0); }
Vec3 Vec3::One() { return Vec3(1, 1, 1); }
Vec3 Vec3::X() { return Vec3(1, 0, 0); }
Vec3 Vec3::Y() { return Vec3(0, 1, 0); }
Vec3 Vec3::Z() { return Vec3(0, 0, 1); }

Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(MATHTYPE v) : x(v), y(v), z(v) {}
Vec3::Vec3(MATHTYPE x, MATHTYPE y, MATHTYPE z) : x(x), y(y), z(z) {}
Vec3::Vec3(Vec3 const &from) : x(from.x), y(from.y), z(from.z) {}
Vec3 Vec3::operator=(Vec3 const &from)
{
	return Vec3(from);
}
/* Vec3::Vec3(Matrix const &mtx) */
/* { */
/* 	if (mtx.width != 1) */
/* 		throw std::invalid_argument("Vec3(Matrix) expects matrix with width of 1"); */
/* 	if (mtx.height != 3) */
/* 		throw std::invalid_argument("Vec3(Matrix) expects matrix with height of 3"); */
/* 	x = mtx.get(0, 0); */
/* 	y = mtx.get(0, 1); */
/* 	z = mtx.get(0, 2); */
/* } */

/* Vec3 Vec3::RadialXY(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleY) */
/* { */
/* 	return Vec3( */
/* 		length *  std::cos(angleX) * -std::sin(angleY), */
/* 		length * -std::sin(angleX), */
/* 		length *  std::cos(angleX) *  std::cos(angleY) */
/* 	); */
/* } */
/* Vec3 Vec3::RadialXZ(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleZ) */
/* { */
/* 	return Vec3( */
/* 		length *  std::cos(angleX) * -std::sin(angleZ), */
/* 		length * -std::sin(angleX) *  std::cos(angleZ), */
/* 		length *  std::cos(angleX) */
/* 	); */
/* } */
/* Vec3 Vec3::RadialYZ(MATHTYPE length, MATHTYPE angleY, MATHTYPE angleZ) */
/* { */
/* 	return Vec3( */
/* 		length *  */
/* 	); */
/* } */

Vec3 Vec3::operator+() const
{
	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

#define VEC3_VEC_OP(op) \
Vec3 Vec3::operator op(Vec3 const &other) const \
{ \
	return Vec3(x op other.x, y op other.y, z op other.z); \
}

#define VEC3_VEC_OP_CALL(op, call) \
Vec3 Vec3::operator op(Vec3 const &other) const \
{ \
	return Vec3(call(x, other.x), call(y, other.y), call(z, other.z)); \
}
#define VEC3_VEC_ASSIGN_OP(op) \
Vec3 Vec3::operator op(Vec3 const &other) \
{ \
	return Vec3(x op other.x, y op other.y, z op other.z); \
}

#define VEC3_VEC_ASSIGN_OP_CALL(opn, call) \
Vec3 Vec3::operator opn(Vec3 const &other) \
{ \
	return Vec3(x = call(x, other.x), y = call(y, other.y), z = call(z, other.z)); \
}

#define VEC3_SCALAR_OP(op) \
Vec3 Vec3::operator op(MATHTYPE const other) const \
{ \
	return Vec3(x op other, y op other, z op other); \
}
#define VEC3_SCALAR_ASSIGN_OP(op) \
Vec3 Vec3::operator op(MATHTYPE const other) \
{ \
	return Vec3(x op other, y op other, z op other); \
}
#define VEC3_SCALAR_OP_CALL(op, call) \
Vec3 Vec3::operator op(MATHTYPE const other) const \
{ \
	return Vec3(call(x, other), call(y, other), call(z, other)); \
}
#define VEC3_SCALAR_ASSIGN_OP_CALL(opn, call) \
Vec3 Vec3::operator opn(MATHTYPE const other) \
{ \
	return Vec3(x = call(x, other), y = call(y, other), z = call(z, other)); \
}


VEC3_VEC_OP(+);
VEC3_VEC_OP(-);
VEC3_VEC_OP(*);
VEC3_VEC_OP(/);
VEC3_VEC_OP_CALL(%, fmod);
VEC3_VEC_ASSIGN_OP(+=);
VEC3_VEC_ASSIGN_OP(-=);
VEC3_VEC_ASSIGN_OP(*=);
VEC3_VEC_ASSIGN_OP(/=);
VEC3_VEC_ASSIGN_OP_CALL(%=, fmod);

VEC3_SCALAR_OP(+);
VEC3_SCALAR_OP(-);
VEC3_SCALAR_OP(*);
VEC3_SCALAR_OP(/);
VEC3_SCALAR_OP_CALL(%, fmod);
VEC3_SCALAR_ASSIGN_OP(+=);
VEC3_SCALAR_ASSIGN_OP(-=);
VEC3_SCALAR_ASSIGN_OP(*=);
VEC3_SCALAR_ASSIGN_OP(/=);
VEC3_SCALAR_ASSIGN_OP_CALL(%=, fmod);

MATHTYPE Vec3::length_squared() const
{
	return x * x + y * y + z * z;
}
MATHTYPE Vec3::length() const
{
	return std::sqrt(length_squared());
}

void Vec3::normalize()
{
	auto len = length();
	x /= len;
	y /= len;
	z /= len;
}
Vec3 Vec3::normalized() const
{
	Vec3 ret(*this);
	ret.normalize();
	return ret;
}
void Vec3::scale(MATHTYPE const factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
}
Vec3 Vec3::scaled(MATHTYPE const factor) const
{
	Vec3 ret(*this);
	ret.scale(factor);
	return ret;
}
void Vec3::limit_length(MATHTYPE const maxLength, MATHTYPE const minLength)
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
Vec3 Vec3::limited_length(MATHTYPE const maxLength, MATHTYPE const minLength) const
{
	Vec3 ret(*this);
	ret.limit_length(maxLength, minLength);
	return ret;
}
void Vec3::clamp(MATHTYPE const min, MATHTYPE const max)
{
	x = std::clamp(x, min, max);
	y = std::clamp(y, min, max);
	z = std::clamp(z, min, max);
}
Vec3 Vec3::clamped(MATHTYPE const min, MATHTYPE const max) const
{
	Vec3 ret(*this);
	ret.clamp(min, max);
	return ret;
}

MATHTYPE Vec3::dot(Vec3 const &other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

MATHTYPE Vec3::angle(Vec3 const &other) const
{
	MATHTYPE dotProd = dot(other);
	MATHTYPE magnitudes = std::sqrt(length_squared() * other.length_squared());
	MATHTYPE cosValue = dotProd / magnitudes;
	MATHTYPE angle = std::acos(cosValue);
	return angle;
}

MATHTYPE Vec3::projected_length(Vec3 const &other) const
{
	MATHTYPE magnitude = length();
	MATHTYPE vecAngle = angle(other);
	return magnitude * std::cos(vecAngle);
}

void Vec3::project(Vec3 const &other)
{
	Vec3 projVecCopy = projected(other);
	x = projVecCopy.x;
	y = projVecCopy.y;
	z = projVecCopy.z;
}

Vec3 Vec3::projected(Vec3 const &other) const
{
	Vec3 otherNormal = other.normalized();
	MATHTYPE projLength = projected_length(other);
	return otherNormal * projLength;
}

void Vec3::reject(Vec3 const &other)
{
	Vec3 proj = projected(other);
	x -= proj.x;
	y -= proj.y;
	z -= proj.z;
}

Vec3 Vec3::rejected(Vec3 const &other) const
{
	return *this - projected(other);
}

void Vec3::cross(Vec3 const &other)
{
	Vec3 crossCopy = crossed(other);
	x = crossCopy.x;
	y = crossCopy.y;
	z = crossCopy.z;
}

Vec3 Vec3::crossed(Vec3 const &other) const
{
	return Vec3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

std::ostream &operator<<(std::ostream &os, Vec3 const &vec)
{
	os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return os;
}

#ifndef MIN_ERROR_EQUAL
#define MIN_ERROR_EQUAL 0.0001
#endif
bool Vec3::operator==(Vec3 const &other) const
{
	return (fabs(x - other.x) < (MIN_ERROR_EQUAL)) && (fabs(y - other.y) < (MIN_ERROR_EQUAL)) && (fabs(z - other.z) < (MIN_ERROR_EQUAL));
}

bool Vec3::operator!=(Vec3 const &other) const
{
	return !(*this == other);
}

ZMathLib_Graphics::Vec3 operator+(MATHTYPE const a, ZMathLib_Graphics::Vec3 b)
{
	return b + a;
}
ZMathLib_Graphics::Vec3 operator-(MATHTYPE const a, ZMathLib_Graphics::Vec3 b)
{
	return Vec3(a) - b;
}
ZMathLib_Graphics::Vec3 operator*(MATHTYPE const a, ZMathLib_Graphics::Vec3 b)
{
	return b * a;
}
ZMathLib_Graphics::Vec3 operator/(MATHTYPE const a, ZMathLib_Graphics::Vec3 b)
{
	return Vec3(a) / b;
}
ZMathLib_Graphics::Vec3 operator%(MATHTYPE const a, ZMathLib_Graphics::Vec3 b)
{
	return Vec3(a) % b;
}

// Converts Vec3 to a 3x1 matrix
Matrix Vec3::to_row() const
{
	Matrix ret(3, 1);
	ret.set(0, 0, x);
	ret.set(1, 0, y);
	ret.set(2, 0, z);
	return ret;
}
// Converts Vec3 to a 1x3 matrix
Matrix Vec3::to_column() const
{
	Matrix ret(1, 3);
	ret.set(0, 0, x);
	ret.set(0, 1, y);
	ret.set(0, 2, z);
	return ret;
}
// Converts Vec3 to a 4x1 matrix, with w as the rightmost component (defaults to w=0)
Matrix Vec3::to_row4(MATHTYPE w) const
{
	return Vec4(x, y, z, w).to_row();
}
// Converts Vec3 to a 1x4 matrix, with w as the lowest component (defaults to w=0)
Matrix Vec3::to_column4(MATHTYPE w) const
{
	return Vec4(x, y, z, w).to_column();
}

// Drops z, returning just Vec2(x, y)
Vec2 Vec3::shortened() const
{
	return Vec2(x, y);
}
// Extends Vec3 to Vec4 with w
Vec4 Vec3::extended(MATHTYPE w) const
{
	return Vec4(x, y, z, w);
}
