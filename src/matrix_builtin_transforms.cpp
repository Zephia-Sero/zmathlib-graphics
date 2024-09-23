#include "matrix.hpp"
#include <cmath>
#include <cstdarg>

using namespace ZMathLib_Graphics;

Matrix Matrix::scale2(MATHTYPE scale)
{
	return scale2(scale, scale);
}
Matrix Matrix::scale2(MATHTYPE sx, MATHTYPE sy)
{
	Matrix ret = Matrix::Zero(2);
	ret.set(0,0, sx);
	ret.set(1,1, sy);
	return ret;	
}
Matrix Matrix::scale3(MATHTYPE scale)
{
	return scale3(scale, scale, scale);
}
Matrix Matrix::scale3(MATHTYPE sx, MATHTYPE sy, MATHTYPE sz)
{
	Matrix ret = Matrix::Zero(3);
	ret.set(0,0, sx);
	ret.set(1,1, sy);
	ret.set(2,2, sz);
	return ret;
}
Matrix Matrix::scale4(MATHTYPE scale)
{
	return scale4(scale, scale, scale, scale);
}
// 4x4 scaling matrix
Matrix Matrix::scale4(MATHTYPE sx, MATHTYPE sy, MATHTYPE sz, MATHTYPE sw)
{
	Matrix ret = Matrix::Zero(4);
	ret.set(0,0, sx);
	ret.set(1,1, sy);
	ret.set(2,2, sz);
	ret.set(3,3, sw);
	return ret;
}

Matrix Matrix::scale(unsigned int numScalars, ...)
{
	std::va_list vargs;
	va_start(vargs, numScalars);
	Matrix ret = Matrix::Zero(numScalars);
	for (unsigned int i = 0; i < numScalars; ++i)
		ret.set(i, i, va_arg(vargs, double));
	va_end(vargs);
	return ret;
}

Matrix Matrix::rotate2(MATHTYPE angle)
{
	Matrix ret(2, 2);
	ret.set(0, 0,  cos(angle));
	ret.set(1, 0, -sin(angle));
	ret.set(0, 1,  sin(angle));
	ret.set(1, 1,  cos(angle));
	return ret;
}
Matrix Matrix::rotate2CW(MATHTYPE angle)
{
	Matrix ret(2, 2);
	ret.set(0, 0,  cos(angle));
	ret.set(1, 0,  sin(angle));
	ret.set(0, 1, -sin(angle));
	ret.set(1, 1,  cos(angle));
	return ret;
}
Matrix Matrix::rotate3Z(MATHTYPE angle)
{
	Matrix ret(3, 3);
	ret.set(0, 0,  cos(angle));
	ret.set(1, 0, -sin(angle));
	ret.set(0, 1,  sin(angle));
	ret.set(1, 1,  cos(angle));
	ret.set(2, 0, 0);
	ret.set(2, 1, 0);
	ret.set(0, 2, 0);
	ret.set(1, 2, 0);
	ret.set(2, 2, 1);
	return ret;
}
Matrix Matrix::rotate3ZCW(MATHTYPE angle)
{
	Matrix ret(3, 3);
	ret.set(0, 0,  cos(angle));
	ret.set(1, 0,  sin(angle));
	ret.set(0, 1, -sin(angle));
	ret.set(1, 1,  cos(angle));
	ret.set(2, 0, 0);
	ret.set(2, 1, 0);
	ret.set(0, 2, 0);
	ret.set(1, 2, 0);
	ret.set(2, 2, 1);
	return ret;
}

// up is +y
Matrix Matrix::rotate3Y(MATHTYPE angle)
{
	Matrix ret(3, 3);
	// Vec3(0, 0, 1) -> rotate3Y(PI/2)  -> Vec3(-1, 0, 0)
	// x = x cos(a) - z sin(a)
	// z = z cos(a) + x sin(a)
	ret.set(0, 0,  cos(angle));
	ret.set(2, 0,  sin(angle));
	ret.set(0, 2, -sin(angle));
	ret.set(2, 2,  cos(angle));
	ret.set(0, 1, 0);
	ret.set(1, 0, 0);
	ret.set(1, 1, 1);
	ret.set(1, 2, 0);
	ret.set(2, 1, 0);
	return ret;
}
Matrix Matrix::rotate3YCW(MATHTYPE angle)
{
	Matrix ret(3, 3);
	ret.set(0, 0,  cos(angle));
	ret.set(2, 0, -sin(angle));
	ret.set(0, 2,  sin(angle));
	ret.set(2, 2,  cos(angle));
	ret.set(0, 1, 0);
	ret.set(1, 0, 0);
	ret.set(1, 1, 1);
	ret.set(1, 2, 0);
	ret.set(2, 1, 0);
	return ret;
}
Matrix Matrix::rotate3X(MATHTYPE angle)
{
	Matrix ret(3, 3);
	ret.set(1, 1,  cos(angle));
	ret.set(2, 1, -sin(angle));
	ret.set(1, 2,  sin(angle));
	ret.set(2, 2,  cos(angle));
	ret.set(0, 0, 1);
	ret.set(1, 0, 0);
	ret.set(0, 1, 1);
	ret.set(0, 2, 0);
	ret.set(2, 0, 0);
	return ret;
}
Matrix Matrix::rotate3XCW(MATHTYPE angle)
{
	Matrix ret(3, 3);
	ret.set(1, 1,  cos(angle));
	ret.set(2, 1,  sin(angle));
	ret.set(1, 2, -sin(angle));
	ret.set(2, 2,  cos(angle));
	ret.set(0, 0, 1);
	ret.set(1, 0, 0);
	ret.set(0, 1, 1);
	ret.set(0, 2, 0);
	ret.set(2, 0, 0);
	return ret;
}

Matrix Matrix::translate2(MATHTYPE ox, MATHTYPE oy)
{
	Matrix ret = Identity(3);
	ret.set(2, 0, ox);
	ret.set(2, 1, oy);
	return ret;
}
Matrix Matrix::translate3(MATHTYPE ox, MATHTYPE oy, MATHTYPE oz)
{
	Matrix ret = Identity(4);
	ret.set(3, 0, ox);
	ret.set(3, 1, oy);
	ret.set(3, 2, oz);
	return ret;
}
