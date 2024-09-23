#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "mathtype.hpp"
#include <cstddef>

namespace ZMathLib_Graphics {
struct MathTypePointerList {
private:
	MATHTYPE **_array;
public:
	size_t const length;
	MathTypePointerList(size_t len);
	~MathTypePointerList();
	MATHTYPE *&operator[](size_t index) const;
};

// forward declaration is needed!
struct Vec2;
struct Vec3;
struct Vec4;

struct Matrix {
private:
	MATHTYPE *_array;
public:
	unsigned int width, height;

	static Matrix Zero(unsigned int w, unsigned int h);
	static Matrix Zero(unsigned int size);
	static Matrix Identity(unsigned int size);

	Vec2 to_vec2() const;
	Vec3 to_vec3() const;
	Vec4 to_vec4() const;

	// 3x3 translation matrix
	static Matrix translate2(MATHTYPE ox, MATHTYPE oy);
	// 4x4 translation matrix
	static Matrix translate3(MATHTYPE ox, MATHTYPE oy, MATHTYPE oz);

	// 2x2 scaling matrix
	static Matrix scale2(MATHTYPE scale);
	// 2x2 scaling matrix
	static Matrix scale2(MATHTYPE sx, MATHTYPE sy);
	// 3x3 scaling matrix
	static Matrix scale3(MATHTYPE scale);
	// 3x3 scaling matrix
	static Matrix scale3(MATHTYPE sx, MATHTYPE sy, MATHTYPE sz);
	// 4x4 scaling matrix
	static Matrix scale4(MATHTYPE scale);
	// 4x4 scaling matrix
	static Matrix scale4(MATHTYPE sx, MATHTYPE sy, MATHTYPE sz, MATHTYPE sw);
	// arbitrary scaling matrix
	static Matrix scale(unsigned int numScalars, ...);

	// 2x2 rotation matrix (Counter ClockWise)
	static Matrix rotate2(MATHTYPE angle);
	// 2x2 rotation matrix (ClockWise)
	static Matrix rotate2CW(MATHTYPE angle);
	// 3x3 rotation matrix (Counter ClockWise) about the Z axis
	static Matrix rotate3Z(MATHTYPE angle);
	// 3x3 rotation matrix (ClockWise) about the Z axis
	static Matrix rotate3ZCW(MATHTYPE angle);
	// 3x3 rotation matrix (Counter ClockWise) about the Y axis
	static Matrix rotate3Y(MATHTYPE angle);
	// 3x3 rotation matrix (ClockWise) about the Y axis
	static Matrix rotate3YCW(MATHTYPE angle);
	// 3x3 rotation matrix (Counter ClockWise) about the X axis
	static Matrix rotate3X(MATHTYPE angle);
	// 3x3 rotation matrix (ClockWise) about the X axis
	static Matrix rotate3XCW(MATHTYPE angle);

	Matrix(unsigned int size);
	Matrix(unsigned int w, unsigned int h);
	Matrix(Matrix const &mtx);
	~Matrix();

	Matrix operator+() const;
	Matrix operator-() const;

	Matrix operator+(Matrix const &other) const;
	Matrix operator-(Matrix const &other) const;
	Matrix operator*(Matrix const &other) const;

	void transpose();
	Matrix transposed() const;

	MATHTYPE determinant() const;

	Matrix operator+(MATHTYPE other) const;
	Matrix operator-(MATHTYPE other) const;
	Matrix operator*(MATHTYPE other) const;
	Matrix operator/(MATHTYPE other) const;

	bool operator==(Matrix other) const;
	bool operator!=(Matrix other) const;

	//Matrix operator+(Matrix other) const;
	//Matrix operator-(Matrix other) const;

	MATHTYPE  get(unsigned int xColumn, unsigned int yColumn) const;
	MATHTYPE &get_mut(unsigned int xColumn, unsigned int yColumn);
	void      set(unsigned int xColumn, unsigned int yColumn, MATHTYPE newValue);

	Matrix get_column(unsigned int xColumn) const;
	MathTypePointerList get_column_mut(unsigned int xColumn);
	Matrix get_row(unsigned int yRow) const;
	MathTypePointerList get_row_mut(unsigned int yRow);

	// Maps each row to a new row, through func()
	void map_rows(Matrix (*func)(unsigned int yRow, Matrix row));
	// Maps each column to a new column, through func()
	void map_columns(Matrix (*func)(unsigned int xColumn, Matrix column));
	// Maps each cell to a new cell, through func()
	void map_cells(MATHTYPE (*func)(unsigned int xColumn, unsigned int yRow, MATHTYPE cell));

	// Maps each row to a new row, through func(), returns a new Matrix
	Matrix mapped_rows(Matrix (*func)(unsigned int yRow, Matrix row)) const;
	// Maps each column to a new column, through func(), returns a new Matrix
	Matrix mapped_columns(Matrix (*func)(unsigned int xColumn, Matrix column)) const;
	// Maps each column to a new column, through func(), returns a new Matrix
	Matrix mapped_cells(MATHTYPE (*func)(unsigned int xColumn, unsigned int yRow, MATHTYPE cell)) const;

	// Takes in a matrix dimensions CxR and produces a matrix 1xR, applying func() on each row of the matrix.
	void reduce_rows(MATHTYPE (*func)(unsigned int yRow, Matrix row));
	// Takes in a matrix dimensions CxR and produces a matrix Cx1, applying func() on each column of the matrix.
	void reduce_columns(MATHTYPE (*func)(unsigned int xColumn, Matrix column));

	// Takes in a matrix dimensions CxR and produces a matrix 1xR, applying func() on each row of the matrix. Returns a new Matrix.
	Matrix reduced_rows(MATHTYPE (*func)(unsigned int yRow, Matrix row)) const;
	// Takes in a matrix dimensions CxR and produces a matrix Cx1, applying func() on each column of the matrix. Returns a new Matrix.
	Matrix reduced_columns(MATHTYPE (*func)(unsigned int xColumn, Matrix column)) const;

	void print() const;

	Vec2 operator*(Vec2 const &other) const;
	Vec3 operator*(Vec3 const &other) const;
	Vec4 operator*(Vec4 const &other) const;

	// none of this unless C++23
	//MATHTYPE &operator[](size_t xColumn, size_t yRow);
};
}
ZMathLib_Graphics::Matrix operator*(MATHTYPE other, ZMathLib_Graphics::Matrix mtx);

#endif
