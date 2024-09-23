#include "mathtype.hpp"
#include "matrix.hpp"
#include <cstdio>
#include <stdexcept>

namespace ZMathLib_Graphics {
Matrix Matrix::operator+(Matrix const &other) const
{
	if (width != other.width || height != other.height)
		throw std::invalid_argument("Matrix + Matrix operation requires matrices of equal width and height");
	Matrix ret(width, height);
	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			ret._array[y * width + x] = _array[y * width + x] + other._array[y * width + x];
	return ret;
}
Matrix Matrix::operator-(Matrix const &other) const
{
	if (width != other.width || height != other.height)
		throw std::invalid_argument("Matrix - Matrix operation requires matrices of equal width and height");
	Matrix ret(width, height);
	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			ret._array[y * width + x] = _array[y * width + x] - other._array[y * width + x];
	return ret;
}
Matrix Matrix::operator*(Matrix const &other) const
{
	if (width != other.height)
		throw std::invalid_argument("Matrix A * Matrix B operation requires that A.width == B.height");
	Matrix ret(other.width, height);
	for (unsigned int x = 0; x < ret.width; ++x) {
		Matrix column = other.get_column(x);
		for (unsigned int y = 0; y < ret.height; ++y) {
			Matrix row = get_row(y);
			MATHTYPE dot = 0;
			for (unsigned int i = 0; i < column.height; ++i)
				dot += row._array[i] * column._array[i];
			ret._array[y * ret.width + x] = dot;
		}
	}
	return ret;
}
}
