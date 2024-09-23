#ifndef VECTOR_HPP
#define VECTOR_HPP


#include <ostream>
#include "mathtype.hpp"

namespace ZMathLib_Graphics {
// forward declaration!
struct Matrix;
struct Vec2;
struct Vec3;
struct Vec4;

struct Vec2 {
	MATHTYPE x, y;

	static Vec2 Zero();
	static Vec2 One();
	static Vec2 X();
	static Vec2 Y();

	// Converts Vec2 to a 2x1 matrix
	Matrix to_row() const;
	// Converts Vec2 to a 1x2 matrix
	Matrix to_column() const;
	// Converts Vec2 to a 3x1 matrix, with z as the rightmost component (defaults to z=0)
	Matrix to_row3(MATHTYPE z=0) const;
	// Converts Vec2 to a 1x3 matrix, with z as the lowest component (defaults to z=0)
	Matrix to_column3(MATHTYPE z=0) const;
	// Converts Vec2 to a 4x1 matrix, with w as the rightmost component, z the 2nd-rightmost (defaults to z=0, w=0)
	Matrix to_row4(MATHTYPE z=0, MATHTYPE w=0) const;
	// Converts Vec2 to a 4x1 matrix, with w as the lowest component, z the 2nd-lowest (defaults to z=0, w=0)
	Matrix to_column4(MATHTYPE z=0, MATHTYPE w=0) const;

	// Drops y, returning just x
	MATHTYPE shortened() const;
	// Extends Vec2 to Vec3 with z, defaults to z=0
	Vec3 extended(MATHTYPE z=0) const;

	static Vec2 Radial(MATHTYPE length, MATHTYPE angle);
	Vec2();
	Vec2(MATHTYPE v);
        Vec2(MATHTYPE x, MATHTYPE y);
        Vec2(Vec2 const &from);

        Vec2 operator+() const;
        Vec2 operator-() const;

        Vec2 operator+(Vec2 const &other) const;
	Vec2 operator+=(Vec2 const &other);
        Vec2 operator-(Vec2 const &other) const;
	Vec2 operator-=(Vec2 const &other);
        Vec2 operator*(Vec2 const &other) const;
	Vec2 operator*=(Vec2 const &other);
        Vec2 operator/(Vec2 const &other) const;
	Vec2 operator/=(Vec2 const &other);
        Vec2 operator%(Vec2 const &other) const;
        Vec2 operator%=(Vec2 const &other);

        Vec2 operator+(MATHTYPE const other) const;
	Vec2 operator+=(MATHTYPE const other);
        Vec2 operator-(MATHTYPE const other) const;
	Vec2 operator-=(MATHTYPE const other);
        Vec2 operator*(MATHTYPE const other) const;
	Vec2 operator*=(MATHTYPE const other);
        Vec2 operator/(MATHTYPE const other) const;
	Vec2 operator/=(MATHTYPE const other);
        Vec2 operator%(MATHTYPE const other) const;
        Vec2 operator%=(MATHTYPE const other);

	Vec2 operator=(Vec2 const &other);

	MATHTYPE length() const;
	MATHTYPE length_squared() const;

	void normalize();
	Vec2 normalized() const;
	// Roughly equivalent to `vec *= factor`
	void scale(MATHTYPE const factor);
	// Equivalent to `vec * factor`
	Vec2 scaled(MATHTYPE const factor) const;
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	void limit_length(MATHTYPE const maxLength, MATHTYPE const minLength=0);
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	Vec2 limited_length(MATHTYPE const maxLength, MATHTYPE const minLength=0) const;
	// Limits each component to [min, max]
	void clamp(MATHTYPE const min, MATHTYPE const max);
	// Limits each component to [min, max]
	Vec2 clamped(MATHTYPE const min, MATHTYPE const max) const;

	MATHTYPE dot(Vec2 const &other) const;
	// Maybe one day, but right now I think this would be kinda cursed since it'd require "upcasting" to Vec3 and arbitrarily
	// deciding which plane the vec2's should lie on.
	/* Vec3 crossed(Vec2 const &other) const; */
	MATHTYPE projected_length(Vec2 const &other) const;
	void project(Vec2 const &other);
	Vec2 projected(Vec2 const &other) const;
	void reject(Vec2 const &other);
	Vec2 rejected(Vec2 const &other) const;
	MATHTYPE angle(Vec2 const &other) const;
	MATHTYPE angle() const;

	bool operator==(Vec2 const &other) const;
	bool operator!=(Vec2 const &other) const;

	// decided these are unholy unless MATHTYPE=int which is unlikely!
        /* Vec2 operator<<(Vec2 const &other) const; */
        /* Vec2 operator<<=(Vec2 const &other); */
        /* Vec2 operator>>(Vec2 const &other) const; */
        /* Vec2 operator>>=(Vec2 const &other); */
        /* Vec2 operator&&(Vec2 const &other) const; */
        /* Vec2 operator||(Vec2 const &other) const; */
        /* Vec2 operator&(Vec2 const &other) const; */
        /* Vec2 operator&=(Vec2 const &other); */
        /* Vec2 operator|(Vec2 const &other) const; */
        /* Vec2 operator|=(Vec2 const &other); */
        /* Vec2 operator^(Vec2 const &other) const; */
        /* Vec2 operator^=(Vec2 const &other); */
        /* Vec2 operator~() const; */
};


struct Vec3 {
	MATHTYPE x, y, z;

	static Vec3 Zero();
	static Vec3 One();
	static Vec3 X();
	static Vec3 Y();
	static Vec3 Z();

	// Converts Vec3 to a 3x1 matrix
	Matrix to_row() const;
	// Converts Vec3 to a 1x3 matrix
	Matrix to_column() const;
	// Converts Vec3 to a 4x1 matrix, with w as the rightmost component (defaults to w=0)
	Matrix to_row4(MATHTYPE w=0) const;
	// Converts Vec3 to a 1x4 matrix, with w as the lowest component (defaults to w=0)
	Matrix to_column4(MATHTYPE w=0) const;

	// Drops z, returning just Vec2(x, y)
	Vec2 shortened() const;
	// Extends Vec3 to Vec4 with w
	Vec4 extended(MATHTYPE w=0) const;

	// I'm bad at vector math, i'll add this later probably
	/* static Vec3 RadialXY(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleY); */
	/* static Vec3 RadialXZ(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleZ); */
	/* static Vec3 RadialYZ(MATHTYPE length, MATHTYPE angleY, MATHTYPE angleZ); */
	Vec3();
	Vec3(MATHTYPE v);
        Vec3(MATHTYPE x, MATHTYPE y, MATHTYPE z);
        Vec3(Vec3 const &from);

        Vec3 operator+() const;
        Vec3 operator-() const;

        Vec3 operator+(Vec3 const &other) const;
	Vec3 operator+=(Vec3 const &other);
        Vec3 operator-(Vec3 const &other) const;
	Vec3 operator-=(Vec3 const &other);
        Vec3 operator*(Vec3 const &other) const;
	Vec3 operator*=(Vec3 const &other);
        Vec3 operator/(Vec3 const &other) const;
	Vec3 operator/=(Vec3 const &other);
        Vec3 operator%(Vec3 const &other) const;
        Vec3 operator%=(Vec3 const &other);

        Vec3 operator+(MATHTYPE const other) const;
	Vec3 operator+=(MATHTYPE const other);
        Vec3 operator-(MATHTYPE const other) const;
	Vec3 operator-=(MATHTYPE const other);
        Vec3 operator*(MATHTYPE const other) const;
	Vec3 operator*=(MATHTYPE const other);
        Vec3 operator/(MATHTYPE const other) const;
	Vec3 operator/=(MATHTYPE const other);
        Vec3 operator%(MATHTYPE const other) const;
        Vec3 operator%=(MATHTYPE const other);

	Vec3 operator=(Vec3 const &other);

	MATHTYPE length() const;
	MATHTYPE length_squared() const;

	void normalize();
	Vec3 normalized() const;
	// Roughly equivalent to `vec *= factor`
	void scale(MATHTYPE const factor);
	// Equivalent to `vec * factor`
	Vec3 scaled(MATHTYPE const factor) const;
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	void limit_length(MATHTYPE const maxLength, MATHTYPE const minLength=0);
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	Vec3 limited_length(MATHTYPE const maxLength, MATHTYPE const minLength=0) const;
	// Limits each component to [min, max]
	void clamp(MATHTYPE const min, MATHTYPE const max);
	// Limits each component to [min, max]
	Vec3 clamped(MATHTYPE const min, MATHTYPE const max) const;

	MATHTYPE dot(Vec3 const &other) const;
	void cross(Vec3 const &other);
	Vec3 crossed(Vec3 const &other) const;
	MATHTYPE projected_length(Vec3 const &other) const;
	void project(Vec3 const &other);
	Vec3 projected(Vec3 const &other) const;
	void reject(Vec3 const &other);
	Vec3 rejected(Vec3 const &other) const;
	MATHTYPE angle(Vec3 const &other) const;

	bool operator==(Vec3 const &other) const;
	bool operator!=(Vec3 const &other) const;

	// decided these are unholy unless MATHTYPE=int which is unlikely!
        /* Vec3 operator<<(Vec3 const &other) const; */
        /* Vec3 operator<<=(Vec3 const &other); */
        /* Vec3 operator>>(Vec3 const &other) const; */
        /* Vec3 operator>>=(Vec3 const &other); */
        /* Vec3 operator&&(Vec3 const &other) const; */
        /* Vec3 operator||(Vec3 const &other) const; */
        /* Vec3 operator&(Vec3 const &other) const; */
        /* Vec3 operator&=(Vec3 const &other); */
        /* Vec3 operator|(Vec3 const &other) const; */
        /* Vec3 operator|=(Vec3 const &other); */
        /* Vec3 operator^(Vec3 const &other) const; */
        /* Vec3 operator^=(Vec3 const &other); */
        /* Vec3 operator~() const; */
};

struct Vec4 {
	MATHTYPE x, y, z, w;

	static Vec4 Zero();
	static Vec4 One();
	static Vec4 X();
	static Vec4 Y();
	static Vec4 Z();
	static Vec4 W();

	// Converts Vec4 to a 4x1 matrix
	Matrix to_row() const;
	// Converts Vec4 to a 1x4 matrix
	Matrix to_column() const;

	// Drops w, returning just Vec3(x, y, z)
	Vec3 shortened() const;
	// Extends Vec4 to Matrix(5, 1) with v
	Matrix extended_row(MATHTYPE v=0) const;
	// Extends Vec4 to Matrix(1, 5) with v
	Matrix extended_column(MATHTYPE v=0) const;

	// I'm bad at vector math, i'll add this later probably
	/* static Vec3 RadialXY(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleY); */
	/* static Vec3 RadialXZ(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleZ); */
	/* static Vec3 RadialYZ(MATHTYPE length, MATHTYPE angleY, MATHTYPE angleZ); */
	Vec4();
	Vec4(MATHTYPE v);
        Vec4(MATHTYPE x, MATHTYPE y, MATHTYPE z, MATHTYPE w);
	Vec4(Matrix const &mtx);
        Vec4(Vec4 const &from);

        Vec4 operator+() const;
        Vec4 operator-() const;

        Vec4 operator+(Vec4 const &other) const;
	Vec4 operator+=(Vec4 const &other);
        Vec4 operator-(Vec4 const &other) const;
	Vec4 operator-=(Vec4 const &other);
        Vec4 operator*(Vec4 const &other) const;
	Vec4 operator*=(Vec4 const &other);
        Vec4 operator/(Vec4 const &other) const;
	Vec4 operator/=(Vec4 const &other);
        Vec4 operator%(Vec4 const &other) const;
        Vec4 operator%=(Vec4 const &other);

        Vec4 operator+(MATHTYPE const other) const;
	Vec4 operator+=(MATHTYPE const other);
        Vec4 operator-(MATHTYPE const other) const;
	Vec4 operator-=(MATHTYPE const other);
        Vec4 operator*(MATHTYPE const other) const;
	Vec4 operator*=(MATHTYPE const other);
        Vec4 operator/(MATHTYPE const other) const;
	Vec4 operator/=(MATHTYPE const other);
        Vec4 operator%(MATHTYPE const other) const;
        Vec4 operator%=(MATHTYPE const other);

	Vec4 operator=(Vec4 const &other);

	MATHTYPE length() const;
	MATHTYPE length_squared() const;

	void normalize();
	Vec4 normalized() const;
	// Roughly equivalent to `vec *= factor`
	void scale(MATHTYPE const factor);
	// Equivalent to `vec * factor`
	Vec4 scaled(MATHTYPE const factor) const;
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	void limit_length(MATHTYPE const maxLength, MATHTYPE const minLength=0);
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	Vec4 limited_length(MATHTYPE const maxLength, MATHTYPE const minLength=0) const;
	// Limits each component to [min, max]
	void clamp(MATHTYPE const min, MATHTYPE const max);
	// Limits each component to [min, max]
	Vec4 clamped(MATHTYPE const min, MATHTYPE const max) const;

	MATHTYPE dot(Vec4 const &other) const;
	// 4D lacks orthogonality apparently so none of this
	/* void cross(Vec4 const &other);
	Vec4 crossed(Vec4 const &other) const; */
	MATHTYPE projected_length(Vec4 const &other) const;
	void project(Vec4 const &other);
	Vec4 projected(Vec4 const &other) const;
	void reject(Vec4 const &other);
	Vec4 rejected(Vec4 const &other) const;
	MATHTYPE angle(Vec4 const &other) const;

	bool operator==(Vec4 const &other) const;
	bool operator!=(Vec4 const &other) const;

	// decided these are unholy unless MATHTYPE=int which is unlikely!
        /* Vec4 operator<<(Vec4 const &other) const; */
        /* Vec4 operator<<=(Vec4 const &other); */
        /* Vec4 operator>>(Vec4 const &other) const; */
        /* Vec4 operator>>=(Vec4 const &other); */
        /* Vec4 operator&&(Vec4 const &other) const; */
        /* Vec4 operator||(Vec4 const &other) const; */
        /* Vec4 operator&(Vec4 const &other) const; */
        /* Vec4 operator&=(Vec4 const &other); */
        /* Vec4 operator|(Vec4 const &other) const; */
        /* Vec4 operator|=(Vec4 const &other); */
        /* Vec4 operator^(Vec4 const &other) const; */
        /* Vec4 operator^=(Vec4 const &other); */
        /* Vec4 operator~() const; */
};
}

std::ostream &operator<<(std::ostream &os, ZMathLib_Graphics::Vec2 const &vec);
std::ostream &operator<<(std::ostream &os, ZMathLib_Graphics::Vec3 const &vec);
std::ostream &operator<<(std::ostream &os, ZMathLib_Graphics::Vec4 const &vec);

ZMathLib_Graphics::Vec2 operator+(MATHTYPE const a, ZMathLib_Graphics::Vec2 b);
ZMathLib_Graphics::Vec2 operator-(MATHTYPE const a, ZMathLib_Graphics::Vec2 b);
ZMathLib_Graphics::Vec2 operator*(MATHTYPE const a, ZMathLib_Graphics::Vec2 b);
ZMathLib_Graphics::Vec2 operator/(MATHTYPE const a, ZMathLib_Graphics::Vec2 b);
ZMathLib_Graphics::Vec2 operator%(MATHTYPE const a, ZMathLib_Graphics::Vec2 b);

ZMathLib_Graphics::Vec3 operator+(MATHTYPE const a, ZMathLib_Graphics::Vec3 b);
ZMathLib_Graphics::Vec3 operator-(MATHTYPE const a, ZMathLib_Graphics::Vec3 b);
ZMathLib_Graphics::Vec3 operator*(MATHTYPE const a, ZMathLib_Graphics::Vec3 b);
ZMathLib_Graphics::Vec3 operator/(MATHTYPE const a, ZMathLib_Graphics::Vec3 b);
ZMathLib_Graphics::Vec3 operator%(MATHTYPE const a, ZMathLib_Graphics::Vec3 b);

ZMathLib_Graphics::Vec4 operator+(MATHTYPE const a, ZMathLib_Graphics::Vec4 b);
ZMathLib_Graphics::Vec4 operator-(MATHTYPE const a, ZMathLib_Graphics::Vec4 b);
ZMathLib_Graphics::Vec4 operator*(MATHTYPE const a, ZMathLib_Graphics::Vec4 b);
ZMathLib_Graphics::Vec4 operator/(MATHTYPE const a, ZMathLib_Graphics::Vec4 b);
ZMathLib_Graphics::Vec4 operator%(MATHTYPE const a, ZMathLib_Graphics::Vec4 b);

#endif
