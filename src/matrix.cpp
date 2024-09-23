#include "matrix.hpp"
#include "mathtype.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include "vector.hpp"

namespace ZMathLib_Graphics {
Matrix Matrix::Zero(unsigned int w, unsigned int h)
{
	return Matrix(w, h);
}
Matrix Matrix::Zero(unsigned int size)
{
	return Matrix(size, size);
}
Matrix Matrix::Identity(unsigned int size)
{
	Matrix ret(size, size);
	// diagonal of 1's
	for (unsigned int i = 0; i < size; ++i)
		ret._array[i * size + i] = 1.0;
	return ret;
}
/* Matrix::Matrix(Vec2 vec) */
/* { */
/* 	width = 1; */
/* 	height = 2; */
/* 	_array = new MATHTYPE[width * height]; */
/* 	_array[0] = vec.x; */
/* 	_array[1] = vec.y; */
/* } */
/* Matrix::Matrix(Vec3 vec) */
/* { */
/* 	width = 1; */
/* 	height = 3; */
/* 	_array = new MATHTYPE[width * height]; */
/* 	_array[0] = vec.x; */
/* 	_array[1] = vec.y; */
/* 	_array[2] = vec.z; */
/* } */

Matrix::Matrix(unsigned int size) : width(size), height(size)
{
	if (width == 0)
		throw std::invalid_argument("Expected width > 0 for matrix constructor");
	if (height == 0)
		throw std::invalid_argument("Expected height > 0 for matrix constructor");
	_array = new MATHTYPE[width * height];
	for (unsigned int i = 0; i < width * height; ++i)
		_array[i] = 0.0;
}

Matrix::Matrix(unsigned int w, unsigned int h) : width(w), height(h)
{
	if (width == 0)
		throw std::invalid_argument("Expected width > 0 for matrix constructor");
	if (height == 0)
		throw std::invalid_argument("Expected height > 0 for matrix constructor");
	_array = new MATHTYPE[width * height];
	for (unsigned int i = 0; i < width * height; ++i)
		_array[i] = 0.0;
}


Matrix::Matrix(Matrix const &mtx)
{
	width = mtx.width;
	height = mtx.height;
	if (width == 0)
		throw std::invalid_argument("Expected width > 0 for matrix copy constructor");
	if (height == 0)
		throw std::invalid_argument("Expected height > 0 for matrix copy constructor");
	_array = new MATHTYPE[width * height];
	for (unsigned int i = 0; i < width * height; ++i)
		_array[i] = mtx._array[i];
}

Matrix::~Matrix()
{
	delete [] _array;
}

MATHTYPE  Matrix::get(unsigned int xColumn, unsigned int yRow) const
{
	if (xColumn >= width)
		throw std::out_of_range("Column index exceeded width of matrix");
	if (yRow >= height)
		throw std::out_of_range("Row index exceeded height of matrix");
	return _array[yRow * width + xColumn];
}
MATHTYPE &Matrix::get_mut(unsigned int xColumn, unsigned int yRow)
{
	if (xColumn >= width)
		throw std::out_of_range("Column index exceeded width of matrix");
	if (yRow >= height)
		throw std::out_of_range("Row index exceeded height of matrix");
	return _array[yRow * width + xColumn];
}
void      Matrix::set(unsigned int xColumn, unsigned int yRow, MATHTYPE newValue)
{
	if (xColumn >= width)
		throw std::out_of_range("Column index exceeded width of matrix");
	if (yRow >= height)
		throw std::out_of_range("Row index exceeded height of matrix");
	_array[yRow * width + xColumn] = newValue;
}

Matrix Matrix::get_column(unsigned int xColumn) const
{
	if (xColumn >= width)
		throw std::out_of_range("Column index exceeded width of matrix");
	Matrix ret(1, height);
	for (size_t i = 0; i < height; ++i)
		ret._array[i] = _array[i * width + xColumn];
	return ret;
}
MathTypePointerList Matrix::get_column_mut(unsigned int xColumn) 
{
	if (xColumn >= width)
		throw std::out_of_range("Column index exceeded width of matrix");
	MathTypePointerList ret(height);
	for (size_t i = 0; i < height; ++i)
		ret[i] = &_array[i * width + xColumn];
	return ret;
}
Matrix Matrix::get_row(unsigned int yRow) const
{
	if (yRow >= height)
		throw std::out_of_range("Row index exceeded height of matrix");
	Matrix ret(width, 1);
	for (size_t i = 0; i < width; ++i)
		ret._array[i] = _array[yRow * width + i];
	return ret;
}
MathTypePointerList Matrix::get_row_mut(unsigned int yRow) 
{
	if (yRow >= height)
		throw std::out_of_range("Row index exceeded height of matrix");
	MathTypePointerList ret(width);
	for (size_t i = 0; i < width; ++i)
		ret[i] = &_array[yRow * width + i];
	return ret;
}

void Matrix::print() const
{
	for (unsigned int y = 0; y < height; ++y) {
		std::cout << "[ ";
		for (unsigned int x = 0; x < width; ++x) {
			std::cout << get(x, y) << " ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << std::endl;
}
}
