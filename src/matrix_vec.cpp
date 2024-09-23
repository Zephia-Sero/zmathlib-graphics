#include "vector.hpp"
#include "matrix.hpp"

using namespace ZMathLib_Graphics;

Vec2 Matrix::operator*(Vec2 const &other) const
{
	return ((*this) * other.to_column()).to_vec2();
}
Vec3 Matrix::operator*(Vec3 const &other) const
{
	return ((*this) * other.to_column()).to_vec3();
}
Vec4 Matrix::operator*(Vec4 const &other) const
{
	return ((*this) * other.to_column()).to_vec4();
}
