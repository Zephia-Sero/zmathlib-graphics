#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "mathtype.hpp"
#include "vector.hpp"

namespace ZMathLib_Graphics {
struct Quaternion {
private:
	Vec4 _vec;
public:
	static Quaternion Zero();
	static Quaternion One();
	// returns Quaternion with Real component=1
	static Quaternion R();
	// returns Quaternion with I component=1
	static Quaternion I();
	// returns Quaternion with J component=1
	static Quaternion J();
	// returns Quaternion with K component=1
	static Quaternion K();

	// Converts Quaternion to a 4x1 matrix
	Matrix to_row() const;
	// Converts Quaternion to a 1x4 matrix
	Matrix to_column() const;

	// Drops w, returning just Vec3(x, y, z)
	Vec4 to_vec4() const;

	// I'm bad at vector math, i'll add this later probably
	/* static Vec3 RadialXY(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleY); */
	/* static Vec3 RadialXZ(MATHTYPE length, MATHTYPE angleX, MATHTYPE angleZ); */
	/* static Vec3 RadialYZ(MATHTYPE length, MATHTYPE angleY, MATHTYPE angleZ); */
	Quaternion();
	Quaternion(MATHTYPE v);
        Quaternion(MATHTYPE r, MATHTYPE i, MATHTYPE j, MATHTYPE k);
	Quaternion(Matrix const &mtx);
        Quaternion(Quaternion const &from);
        Quaternion(Vec4 const &from);

        Quaternion operator+() const;
        Quaternion operator-() const;
	void conjugate();
	Quaternion conjugated() const;

        Quaternion operator+(Quaternion const &other) const;
	Quaternion operator+=(Quaternion const &other);
        Quaternion operator-(Quaternion const &other) const;
	Quaternion operator-=(Quaternion const &other);
        Quaternion operator*(Quaternion const &other) const;
	Quaternion operator*=(Quaternion const &other);
        Quaternion operator/(Quaternion const &other) const;
	Quaternion operator/=(Quaternion const &other);

        Quaternion operator+(MATHTYPE const other) const;
	Quaternion operator+=(MATHTYPE const other);
        Quaternion operator-(MATHTYPE const other) const;
	Quaternion operator-=(MATHTYPE const other);
        Quaternion operator*(MATHTYPE const other) const;
	Quaternion operator*=(MATHTYPE const other);
        Quaternion operator/(MATHTYPE const other) const;
	Quaternion operator/=(MATHTYPE const other);

	MATHTYPE length() const;
	MATHTYPE length_squared() const;

	void normalize();
	Quaternion normalized() const;
	// Roughly equivalent to `quaternion *= factor`
	void scale(MATHTYPE const factor);
	// Equivalent to `quaternion * factor`
	Quaternion scaled(MATHTYPE const factor) const;
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	void limit_length(MATHTYPE const maxLength, MATHTYPE const minLength=0);
	// Limits length to [`minLength`, `maxLength`]. Note that minLength is the 2nd argument
	Quaternion limited_length(MATHTYPE const maxLength, MATHTYPE const minLength=0) const;
	// Limits each component to [min, max]
	void clamp(MATHTYPE const min, MATHTYPE const max);
	// Limits each component to [min, max]
	Quaternion clamped(MATHTYPE const min, MATHTYPE const max) const;

	// Don't think these are very useful for quaternions, lemme know if you need them!
	/* MATHTYPE dot(Vec4 const &other) const; */
	/* // 4D lacks orthogonality apparently so none of this */
	/* void cross(Vec4 const &other); */
	/* Vec4 crossed(Vec4 const &other) const; */
	/* MATHTYPE projected_length(Vec4 const &other) const; */
	/* void project(Vec4 const &other); */
	/* Vec4 projected(Vec4 const &other) const; */
	/* void reject(Vec4 const &other); */
	/* Vec4 rejected(Vec4 const &other) const; */
	/* MATHTYPE angle(Vec4 const &other) const; */

	bool operator==(Quaternion const &other) const;
	bool operator!=(Quaternion const &other) const;

	MATHTYPE r() const;
	MATHTYPE i() const;
	MATHTYPE j() const;
	MATHTYPE k() const;

};
}
std::ostream &operator<<(std::ostream &os, ZMathLib_Graphics::Quaternion const &quat);

#endif
