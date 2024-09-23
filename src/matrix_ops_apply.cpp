#include "mathtype.hpp"
#include "matrix.hpp"
#include <stdexcept>

namespace ZMathLib_Graphics {
// Maps each row to a new row, through func()
void Matrix::map_rows(Matrix (*func)(unsigned int yRow, Matrix row))
{
	for (unsigned int rowIdx = 0; rowIdx < height; ++rowIdx) {
		Matrix row = get_row(rowIdx);
		Matrix transformed = func(rowIdx, row);
		if (transformed.height != 1)
			throw std::invalid_argument("Matrix.map_rows function returned non-row Matrix");
		for (unsigned int columnIdx = 0; columnIdx < width; ++columnIdx)
			_array[rowIdx * width + columnIdx] = transformed._array[columnIdx];
	}
}
// Maps each column to a new column, through func()
void Matrix::map_columns(Matrix (*func)(unsigned int xColumn, Matrix column))
{
	for (unsigned int columnIdx = 0; columnIdx < width; ++columnIdx) {
		Matrix column = get_column(columnIdx);
		Matrix transformed = func(columnIdx, column);
		if (transformed.width != 1)
			throw std::invalid_argument("Matrix.map_columns function returned non-column Matrix");
		for (unsigned int rowIdx = 0; rowIdx < height; ++rowIdx)
			_array[rowIdx * width + columnIdx] = transformed._array[rowIdx];
	}
}
// Maps each cell to a new cell, through func()
void Matrix::map_cells(MATHTYPE (*func)(unsigned int xColumn, unsigned int yRow, MATHTYPE cell))
{
	for (unsigned int rowIdx = 0; rowIdx < height; ++rowIdx) {
		for (unsigned int columnIdx = 0; columnIdx < width; ++columnIdx) {
			MATHTYPE &cell = _array[rowIdx * width + columnIdx];
			cell = func(columnIdx, rowIdx, cell);
		}
	}
}

// Maps each row to a new row, through func(), returns a new Matrix
Matrix Matrix::mapped_rows(Matrix (*func)(unsigned int yRow, Matrix row)) const
{
	Matrix ret(*this);
	ret.map_rows(func);
	return ret;
}

// Maps each column to a new column, through func(), returns a new Matrix
Matrix Matrix::mapped_columns(Matrix (*func)(unsigned int xColumn, Matrix column)) const
{
	Matrix ret(*this);
	ret.map_columns(func);
	return ret;
}
// Maps each column to a new column, through func(), returns a new Matrix
Matrix Matrix::mapped_cells(MATHTYPE (*func)(unsigned int xColumn, unsigned int yRow, MATHTYPE cell)) const
{
	Matrix ret(*this);
	ret.map_cells(func);
	return ret;
}


// Takes in a matrix dimensions CxR and produces a matrix 1xR, applying func() on each row of the matrix.
void Matrix::reduce_rows(MATHTYPE (*func)(unsigned int yRow, Matrix row))
{
	MATHTYPE *newArray = new MATHTYPE[1 * height];
	for (unsigned int rowIdx = 0; rowIdx < height; ++rowIdx) {
		Matrix row = get_row(rowIdx);
		MATHTYPE value = func(rowIdx, row);
		newArray[rowIdx] = value;
	}
	delete [] _array;
	_array = newArray;
	width = 1;
}
// Takes in a matrix dimensions CxR and produces a matrix Cx1, applying func() on each column of the matrix.
void Matrix::reduce_columns(MATHTYPE (*func)(unsigned int xColumn, Matrix column))
{
	MATHTYPE *newArray = new MATHTYPE[width * 1];
	for (unsigned int columnIdx = 0; columnIdx < width; ++columnIdx) {
		Matrix column = get_column(columnIdx);
		MATHTYPE value = func(columnIdx, column);
		newArray[columnIdx] = value;
	}
	delete [] _array;
	_array = newArray;
	height = 1;
}
// Takes in a matrix dimensions CxR and produces a matrix 1xR, applying func() on each row of the matrix. Returns a new Matrix.
Matrix Matrix::reduced_rows(MATHTYPE (*func)(unsigned int yRow, Matrix row)) const
{
	Matrix ret(*this);
	ret.reduce_rows(func);
	return ret;
}
// Takes in a matrix dimensions CxR and produces a matrix Cx1, applying func() on each column of the matrix. Returns a new Matrix.
Matrix Matrix::reduced_columns(MATHTYPE (*func)(unsigned int xColumn, Matrix column)) const
{
	Matrix ret(*this);
	ret.reduce_columns(func);
	return ret;
}
}
