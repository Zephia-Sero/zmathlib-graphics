#include "vector.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cmath>

using namespace ZMathLib_Graphics;

Vec4 Vec4::Zero() { return Vec4(0, 0, 0, 0); }
Vec4 Vec4::One() { return Vec4(1, 1, 1, 1); }
Vec4 Vec4::X() { return Vec4(1, 0, 0, 0); }
Vec4 Vec4::Y() { return Vec4(0, 1, 0, 0); }
Vec4 Vec4::Z() { return Vec4(0, 0, 1, 0); }
Vec4 Vec4::W() { return Vec4(0, 0, 0, 1); }

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Vec4::Vec4(MATHTYPE v) : x(v), y(v), z(v), w(v) {}
Vec4::Vec4(MATHTYPE x, MATHTYPE y, MATHTYPE z, MATHTYPE w) : x(x), y(y), z(z), w(w) {}
Vec4::Vec4(Vec4 const &from) : x(from.x), y(from.y), z(from.z), w(from.w) {}
Vec4 Vec4::operator=(Vec4 const &from)
{
	return Vec4(from);
}
/* Vec4::Vec4(Matrix const &mtx) */
/* { */
/* 	if (mtx.width != 1) */
/* 		throw std::invalid_argument("Vec4(Matrix) expects matrix with width of 1"); */
/* 	if (mtx.height != 3) */
/* 		throw std::invalid_argument("Vec4(Matrix) expects matrix with height of 3"); */
/* 	x = mtx.get(0, 0); */
/* 	y = mtx.get(0, 1); */
/* 	z = mtx.get(0, 2); */
/* } */

/* Vec4 Vec4::RadialXY(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleY) */
/* { */
/* 	return Vec4( */
/* 		length *  std::cos(angleX) * -std::sin(angleY), */
/* 		length * -std::sin(angleX), */
/* 		length *  std::cos(angleX) *  std::cos(angleY) */
/* 	); */
/* } */
/* Vec4 Vec4::RadialXZ(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleZ) */
/* { */
/* 	return Vec4( */
/* 		length *  std::cos(angleX) * -std::sin(angleZ), */
/* 		length * -std::sin(angleX) *  std::cos(angleZ), */
/* 		length *  std::cos(angleX) */
/* 	); */
/* } */
/* Vec4 Vec4::RadialYZ(MATHTYPE length, MATHTYPE angleY, MATHTYPE angleZ) */
/* { */
/* 	return Vec4( */
/* 		length *  */
/* 	); */
/* } */

Vec4 Vec4::operator+() const
{
	return *this;
}

Vec4 Vec4::operator-() const
{
	return Vec4(-x, -y, -z, -w);
}

#define VEC4_VEC_OP(op) \
Vec4 Vec4::operator op(Vec4 const &other) const \
{ \
	return Vec4(x op other.x, y op other.y, z op other.z, w op other.w); \
}

#define VEC4_VEC_OP_CALL(op, call) \
Vec4 Vec4::operator op(Vec4 const &other) const \
{ \
	return Vec4(call(x, other.x), call(y, other.y), call(z, other.z), call(w, other.w)); \
}
#define VEC4_VEC_ASSIGN_OP(op) \
Vec4 Vec4::operator op(Vec4 const &other) \
{ \
	return Vec4(x op other.x, y op other.y, z op other.z, w op other.w); \
}

#define VEC4_VEC_ASSIGN_OP_CALL(opn, call) \
Vec4 Vec4::operator opn(Vec4 const &other) \
{ \
	return Vec4(x = call(x, other.x), y = call(y, other.y), z = call(z, other.z), w = call(w, other.w)); \
}

#define VEC4_SCALAR_OP(op) \
Vec4 Vec4::operator op(MATHTYPE const other) const \
{ \
	return Vec4(x op other, y op other, z op other, w op other); \
}
#define VEC4_SCALAR_ASSIGN_OP(op) \
Vec4 Vec4::operator op(MATHTYPE const other) \
{ \
	return Vec4(x op other, y op other, z op other, w op other); \
}
#define VEC4_SCALAR_OP_CALL(op, call) \
Vec4 Vec4::operator op(MATHTYPE const other) const \
{ \
	return Vec4(call(x, other), call(y, other), call(z, other), call(w, other)); \
}
#define VEC4_SCALAR_ASSIGN_OP_CALL(opn, call) \
Vec4 Vec4::operator opn(MATHTYPE const other) \
{ \
	return Vec4(x = call(x, other), y = call(y, other), z = call(z, other), w = call(w, other)); \
}


VEC4_VEC_OP(+);
VEC4_VEC_OP(-);
VEC4_VEC_OP(*);
VEC4_VEC_OP(/);
VEC4_VEC_OP_CALL(%, fmod);
VEC4_VEC_ASSIGN_OP(+=);
VEC4_VEC_ASSIGN_OP(-=);
VEC4_VEC_ASSIGN_OP(*=);
VEC4_VEC_ASSIGN_OP(/=);
VEC4_VEC_ASSIGN_OP_CALL(%=, fmod);

VEC4_SCALAR_OP(+);
VEC4_SCALAR_OP(-);
VEC4_SCALAR_OP(*);
VEC4_SCALAR_OP(/);
VEC4_SCALAR_OP_CALL(%, fmod);
VEC4_SCALAR_ASSIGN_OP(+=);
VEC4_SCALAR_ASSIGN_OP(-=);
VEC4_SCALAR_ASSIGN_OP(*=);
VEC4_SCALAR_ASSIGN_OP(/=);
VEC4_SCALAR_ASSIGN_OP_CALL(%=, fmod);

MATHTYPE Vec4::length_squared() const
{
	return x * x + y * y + z * z + w * w;
}
MATHTYPE Vec4::length() const
{
	return std::sqrt(length_squared());
}

void Vec4::normalize()
{
	auto len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}
Vec4 Vec4::normalized() const
{
	Vec4 ret(*this);
	ret.normalize();
	return ret;
}
void Vec4::scale(MATHTYPE const factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	w *= factor;
}
Vec4 Vec4::scaled(MATHTYPE const factor) const
{
	Vec4 ret(*this);
	ret.scale(factor);
	return ret;
}
void Vec4::limit_length(MATHTYPE const maxLength, MATHTYPE const minLength)
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
Vec4 Vec4::limited_length(MATHTYPE const maxLength, MATHTYPE const minLength) const
{
	Vec4 ret(*this);
	ret.limit_length(maxLength, minLength);
	return ret;
}
void Vec4::clamp(MATHTYPE const min, MATHTYPE const max)
{
	x = std::clamp(x, min, max);
	y = std::clamp(y, min, max);
	z = std::clamp(z, min, max);
	w = std::clamp(w, min, max);
}
Vec4 Vec4::clamped(MATHTYPE const min, MATHTYPE const max) const
{
	Vec4 ret(*this);
	ret.clamp(min, max);
	return ret;
}

MATHTYPE Vec4::dot(Vec4 const &other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

MATHTYPE Vec4::angle(Vec4 const &other) const
{
	MATHTYPE dotProd = dot(other);
	MATHTYPE magnitudes = std::sqrt(length_squared() * other.length_squared());
	MATHTYPE cosValue = dotProd / magnitudes;
	MATHTYPE angle = std::acos(cosValue);
	return angle;
}

MATHTYPE Vec4::projected_length(Vec4 const &other) const
{
	MATHTYPE magnitude = length();
	MATHTYPE vecAngle = angle(other);
	return magnitude * std::cos(vecAngle);
}

void Vec4::project(Vec4 const &other)
{
	Vec4 projVecCopy = projected(other);
	x = projVecCopy.x;
	y = projVecCopy.y;
	z = projVecCopy.z;
	w = projVecCopy.w;
}

Vec4 Vec4::projected(Vec4 const &other) const
{
	Vec4 otherNormal = other.normalized();
	MATHTYPE projLength = projected_length(other);
	return otherNormal * projLength;
}

void Vec4::reject(Vec4 const &other)
{
	Vec4 proj = projected(other);
	x -= proj.x;
	y -= proj.y;
	z -= proj.z;
	w -= proj.w;
}

Vec4 Vec4::rejected(Vec4 const &other) const
{
	return *this - projected(other);
}

std::ostream &operator<<(std::ostream &os, Vec4 const &vec)
{
	os << "Vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return os;
}

#ifndef MIN_ERROR_EQUAL
#define MIN_ERROR_EQUAL 0.0001
#endif
bool Vec4::operator==(Vec4 const &other) const
{
	return (fabs(x - other.x) < (MIN_ERROR_EQUAL)) && (fabs(y - other.y) < (MIN_ERROR_EQUAL)) && (fabs(z - other.z) < (MIN_ERROR_EQUAL)) && (fabs(w - other.w) < (MIN_ERROR_EQUAL));
}

bool Vec4::operator!=(Vec4 const &other) const
{
	return !(*this == other);
}

ZMathLib_Graphics::Vec4 operator+(MATHTYPE const a, ZMathLib_Graphics::Vec4 b)
{
	return b + a;
}
ZMathLib_Graphics::Vec4 operator-(MATHTYPE const a, ZMathLib_Graphics::Vec4 b)
{
	return Vec4(a) - b;
}
ZMathLib_Graphics::Vec4 operator*(MATHTYPE const a, ZMathLib_Graphics::Vec4 b)
{
	return b * a;
}
ZMathLib_Graphics::Vec4 operator/(MATHTYPE const a, ZMathLib_Graphics::Vec4 b)
{
	return Vec4(a) / b;
}
ZMathLib_Graphics::Vec4 operator%(MATHTYPE const a, ZMathLib_Graphics::Vec4 b)
{
	return Vec4(a) % b;
}

// Converts Vec4 to a 4x1 matrix
Matrix Vec4::to_row() const
{
	Matrix ret(4, 1);
	ret.set(0, 0, x);
	ret.set(1, 0, y);
	ret.set(2, 0, z);
	ret.set(3, 0, w);
	return ret;
}
// Converts Vec4 to a 1x4 matrix
Matrix Vec4::to_column() const
{
	Matrix ret(1, 4);
	ret.set(0, 0, x);
	ret.set(0, 1, y);
	ret.set(0, 2, z);
	ret.set(0, 3, w);
	return ret;
}
// Drops w, returning just Vec3(x, y, z)
Vec3 Vec4::shortened() const
{
	return Vec3(x, y, z);
}
// Extends Vec4 to Matrix(5, 1) with v
Matrix Vec4::extended_row(MATHTYPE v) const
{
	Matrix ret(5, 1);
	ret.set(0, 0, x);
	ret.set(1, 0, y);
	ret.set(2, 0, z);
	ret.set(3, 0, w);
	ret.set(4, 0, v);
	return ret;
}
// Extends Vec4 to Matrix(1, 5) with v
Matrix Vec4::extended_column(MATHTYPE v) const
{
	Matrix ret(1, 5);
	ret.set(0, 0, x);
	ret.set(0, 1, y);
	ret.set(0, 2, z);
	ret.set(0, 3, w);
	ret.set(0, 4, v);
	return ret;
}
