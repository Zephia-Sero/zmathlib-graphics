#include "mathtype.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include <stdexcept>
#include <utility>

namespace ZMathLib_Graphics {
MATHTYPE Matrix::determinant() const
{
	if (width != height)
		throw std::invalid_argument("Determinant requires square matrix");
	// slight optimization!
	//if (*this == Matrix::Identity(width))
	//	return 1;
	if (width == 1)
		return _array[0];
	if (width == 2)
		return (_array[0 * 2 + 0] * _array[1 * 2 + 1]) - (_array[0 * 2 + 1] * _array[1 * 2 + 0]);
	int sign = 1;
	MATHTYPE ret = 0;
	for (unsigned int x = 0; x < width; ++x) {
		MATHTYPE multiplier = sign * _array[x];
		sign = -sign;
		if (multiplier == 0)
			continue;
		Matrix sub(width - 1, height - 1);
		unsigned int i = 0;
		for (unsigned int sy = 1; sy < height; ++sy) {
			for (unsigned int sx = 0; sx < width; ++sx) {
				if (sx == x) continue;
				sub._array[i] = _array[sy * height + sx];
				++i;
			}
		}
		ret += multiplier * sub.determinant();
	}
	return ret;
}
Matrix Matrix::operator+() const
{
	return Matrix(*this);
}

Matrix Matrix::operator-() const
{
	return *this * -1;
}
void Matrix::transpose()
{
	MATHTYPE *newArray = new MATHTYPE[height * width];
	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			newArray[x * height + y] = _array[y * width + x];
	delete [] _array;
	_array = newArray;
	std::swap(width, height);
}
Matrix Matrix::transposed() const
{
	Matrix ret(*this);
	ret.transpose();
	return ret;
}
Vec2 Matrix::to_vec2() const
{
	if ((width == 1 && height == 2) || (width == 2 && height == 1))
		return Vec2(_array[0], _array[1]);
	throw std::invalid_argument("Matrix::to_vec2() expects Matrix 1x2 or 2x1");
}
Vec3 Matrix::to_vec3() const
{
	if ((width == 1 && height == 3) || (width == 3 && height == 1))
		return Vec3(_array[0], _array[1], _array[2]);
	throw std::invalid_argument("Matrix::to_vec3() expects Matrix 1x3 or 3x1");
}
Vec4 Matrix::to_vec4() const
{
	if ((width == 1 && height == 4) || (width == 4 && height == 1))
		return Vec4(_array[0], _array[1], _array[2], _array[3]);
	throw std::invalid_argument("Matrix::to_vec4() expects Matrix 1x4 or 4x1");
}
}
