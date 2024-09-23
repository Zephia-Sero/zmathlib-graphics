#include "mathtype.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "tests.hpp"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>

MATHTYPE random_num()
{
	return 100 * (MATHTYPE) rand() / RAND_MAX;
}

MATHTYPE rand_cell(unsigned int, unsigned int, MATHTYPE)
{
	return 100 * (MATHTYPE) rand() / RAND_MAX;
}

MATHTYPE indexed_cell(unsigned int x, unsigned int y, MATHTYPE)
{
	return x * 10 + y;
}

int main()
{
	srand(time(NULL));
	ZMathLib_Graphics::Tests::test_all();
	return 0;
}

namespace ZMathLib_Graphics::Tests {
char const *currentTest = "test_UNKNOWN";
unsigned int indent = 0;

BEGIN_TEST(test_all)
	test_vec2();
	test_vec3();
	test_vec4();
	test_mtx();
	test_vec_conversions();
	test_mtx_transforms();
	std::cout << "\e[92mAll tests ok!" << std::endl;
END_TEST()

BEGIN_TEST(test_mtx_transforms)
	Matrix rot = Matrix::rotate2(M_PI / 4.);
	Vec2 vec2(1, 0);
	test_assert(rot * vec2 == Vec2(M_SQRT1_2));
	Matrix rotCW = Matrix::rotate2CW(M_PI / 4);
	test_assert(rotCW * vec2 == Vec2(M_SQRT1_2, -M_SQRT1_2));
	Matrix scale2 = Matrix::scale2(4, -2);
	Vec2 vec2_2(9, 3);
	test_assert(scale2 * vec2_2 == Vec2(36, -6));

	Matrix rotZ = Matrix::rotate3Z(M_PI / 4.);
	Vec3 vec3(1, 0, 0);
	test_assert(rotZ * vec3 == Vec3(M_SQRT1_2, M_SQRT1_2, 0));
	Matrix rotZCW = Matrix::rotate3ZCW(M_PI / 4.);
	test_assert(rotZCW * vec3 == Vec3(M_SQRT1_2, -M_SQRT1_2, 0));

	Matrix rotY = Matrix::rotate3Y(M_PI / 4.);
	test_assert(rotY * vec3 == Vec3(M_SQRT1_2, 0, -M_SQRT1_2));
	Matrix rotYCW = Matrix::rotate3YCW(M_PI / 4.);
	test_assert(rotYCW * vec3 == Vec3(M_SQRT1_2, 0, M_SQRT1_2));

	Vec3 vec3other(0, 0, 1);
	Matrix rotX = Matrix::rotate3X(M_PI / 4.);
	test_assert(rotX * vec3other == Vec3(0, -M_SQRT1_2, M_SQRT1_2));
	Matrix rotXCW = Matrix::rotate3XCW(M_PI / 4.);
	test_assert(rotXCW * vec3other == Vec3(0, M_SQRT1_2, M_SQRT1_2));

	Vec3 vec3sc(1, 2, 3);
	Matrix scale3 = Matrix::scale3(6, 3, 2);
	test_assert(scale3 * vec3sc == Vec3(6, 6, 6));

	test_not_implemented();
END_TEST()

BEGIN_TEST(test_vec2_conversions)
	Matrix mtxSrc(1, 2);
	mtxSrc.set(0, 0, 20);
	mtxSrc.set(0, 1, -14);
	Vec2 vecDst = mtxSrc.to_vec2();
	test_assert(vecDst == Vec2(20, -14));
	Vec2 vecSrc(-1, 4);
	Matrix mtxColDst = vecSrc.to_column();
	test_assert(mtxColDst.width == 1 && mtxColDst.height == 2
			&& mtxColDst.get(0, 0) == -1 && mtxColDst.get(0, 1) == 4);
	Matrix mtxRowDst = vecSrc.to_row();
	test_assert(mtxRowDst.width == 2 && mtxRowDst.height == 1
			&& mtxRowDst.get(0, 0) == -1 && mtxRowDst.get(1, 0) == 4);
	Matrix mtxCol3Dst = vecSrc.to_column3(4);
	test_assert(mtxCol3Dst.width == 1 && mtxCol3Dst.height == 3
			&& mtxCol3Dst.get(0, 0) == -1 && mtxCol3Dst.get(0, 1) == 4
			&& mtxCol3Dst.get(0, 2) == 4);
	Matrix mtxRow3Dst = vecSrc.to_row3(4);
	test_assert(mtxRow3Dst.width == 3 && mtxRow3Dst.height == 1
			&& mtxRow3Dst.get(0, 0) == -1 && mtxRow3Dst.get(1, 0) == 4
			&& mtxRow3Dst.get(2, 0) == 4);
	Matrix mtxCol4Dst = vecSrc.to_column4(4,-6);
	test_assert(mtxCol4Dst.width == 1 && mtxCol4Dst.height == 4
			&& mtxCol4Dst.get(0, 0) == -1 && mtxCol4Dst.get(0, 1) == 4
			&& mtxCol4Dst.get(0, 2) == 4 && mtxCol4Dst.get(0, 3) == -6);
	Matrix mtxRow4Dst = vecSrc.to_row4(4,-6);
	test_assert(mtxRow4Dst.width == 4 && mtxRow4Dst.height == 1
			&& mtxRow4Dst.get(0, 0) == -1 && mtxRow4Dst.get(1, 0) == 4
			&& mtxRow4Dst.get(2, 0) == 4 && mtxRow4Dst.get(3, 0) == -6);

	test_assert(mtxColDst.to_vec2() == vecSrc);
	test_assert(mtxRowDst.to_vec2() == vecSrc);
	test_assert(mtxCol3Dst.to_vec3().shortened() == vecSrc);
	test_assert(mtxRow3Dst.to_vec3().shortened() == vecSrc);
	test_assert(mtxCol4Dst.to_vec4().shortened().shortened() == vecSrc);
	test_assert(mtxRow4Dst.to_vec4().shortened().shortened() == vecSrc);

	test_assert(vecSrc.shortened() == -1);
	test_assert(vecSrc.extended(9) == Vec3(-1, 4, 9));
END_TEST()

BEGIN_TEST(test_vec3_conversions)
	Matrix mtxSrc(1, 3);
	mtxSrc.set(0, 0, 20);
	mtxSrc.set(0, 1, -14);
	mtxSrc.set(0, 2, 5);
	Vec3 vecDst = mtxSrc.to_vec3();
	test_assert(vecDst == Vec3(20, -14, 5));
	Vec3 vecSrc(-1, 4, 33);
	Matrix mtxColDst = vecSrc.to_column();
	test_assert(mtxColDst.width == 1 && mtxColDst.height == 3
		&& mtxColDst.get(0, 0) == -1 && mtxColDst.get(0, 1) == 4 && mtxColDst.get(0, 2) == 33);
	Matrix mtxRowDst = vecSrc.to_row();
	test_assert(mtxRowDst.width == 3 && mtxRowDst.height == 1
		&& mtxRowDst.get(0, 0) == -1 && mtxRowDst.get(1, 0) == 4 && mtxRowDst.get(2, 0) == 33);
	Matrix mtxCol4Dst = vecSrc.to_column4(9);
	test_assert(mtxCol4Dst.width == 1 && mtxCol4Dst.height == 4
		&& mtxCol4Dst.get(0, 0) == -1 && mtxCol4Dst.get(0, 1) == 4 && mtxCol4Dst.get(0, 2) == 33
		&& mtxCol4Dst.get(0, 3) == 9);
	Matrix mtxRow4Dst = vecSrc.to_row4(9);
	test_assert(mtxRow4Dst.width == 4 && mtxRow4Dst.height == 1
		&& mtxRow4Dst.get(0, 0) == -1 && mtxRow4Dst.get(1, 0) == 4 && mtxRow4Dst.get(2, 0) == 33
		&& mtxRow4Dst.get(3, 0) == 9);

	test_assert(mtxColDst.to_vec3() == vecSrc);
	test_assert(mtxRowDst.to_vec3() == vecSrc);
	test_assert(mtxCol4Dst.to_vec4().shortened() == vecSrc);
	test_assert(mtxRow4Dst.to_vec4().shortened() == vecSrc);

	test_assert(vecSrc.shortened() == Vec2(-1, 4));
	test_assert(vecSrc.extended(3) == Vec4(-1, 4, 33, 3));
END_TEST()

BEGIN_TEST(test_vec4_conversions)
	Matrix mtxSrc(1, 4);
	mtxSrc.set(0, 0, 20);
	mtxSrc.set(0, 1, -14);
	mtxSrc.set(0, 2, 5);
	mtxSrc.set(0, 3, 8);
	Vec4 vecDst = mtxSrc.to_vec4();
	test_assert(vecDst == Vec4(20, -14, 5, 8));
	Vec4 vecSrc(-1, 4, 33, 1);
	Matrix mtxColDst = vecSrc.to_column();
	test_assert(mtxColDst.width == 1 && mtxColDst.height == 4
		&& mtxColDst.get(0, 0) == -1 && mtxColDst.get(0, 1) == 4 && mtxColDst.get(0, 2) == 33 && mtxColDst.get(0, 3) == 1);
	Matrix mtxRowDst = vecSrc.to_row();
	test_assert(mtxRowDst.width == 4 && mtxRowDst.height == 1
		&& mtxRowDst.get(0, 0) == -1 && mtxRowDst.get(1, 0) == 4 && mtxRowDst.get(2, 0) == 33 && mtxRowDst.get(3, 0) == 1);

	test_assert(mtxColDst.to_vec4() == vecSrc);
	test_assert(mtxRowDst.to_vec4() == vecSrc);

	test_assert(vecSrc.shortened() == Vec3(-1, 4, 33));
	Matrix mtxTrialRow = vecSrc.extended_row(3);
	Matrix mtxExpectRow(5, 1);
	mtxExpectRow.set(0, 0, -1);
	mtxExpectRow.set(1, 0, 4);
	mtxExpectRow.set(2, 0, 33);
	mtxExpectRow.set(3, 0, 1);
	mtxExpectRow.set(4, 0, 3);
	Matrix mtxTrialColumn = vecSrc.extended_column(3);
	Matrix mtxExpectColumn(1, 5);
	mtxExpectColumn.set(0, 0, -1);
	mtxExpectColumn.set(0, 1, 4);
	mtxExpectColumn.set(0, 2, 33);
	mtxExpectColumn.set(0, 3, 1);
	mtxExpectColumn.set(0, 4, 3);

	test_assert(mtxTrialRow == mtxExpectRow);
	test_assert(mtxTrialColumn == mtxExpectColumn);
END_TEST()

BEGIN_TEST(test_vec_conversions)
	test_vec2_conversions();
	test_vec3_conversions();
	test_vec4_conversions();
END_TEST()

BEGIN_TEST(test_mtx)
	test_mtx_ctors();
	test_mtx_accesses();
	test_mtx_apply_ops();
	test_mtx_compare_ops();
	test_mtx_unary_ops();
	test_mtx_mtx_ops();
	test_mtx_vec_ops();
END_TEST()

BEGIN_TEST(test_mtx_mtx_ops)
	Matrix a(2, 3);
	a.set(0, 0, 5);
	a.set(1, 0, -3);
	a.set(0, 1, 6);
	a.set(1, 1, 14);
	a.set(0, 2, -9);
	a.set(1, 2, 10);
	Matrix b(2, 3);
	b.set(0, 0, 3);
	b.set(1, 0, 1);
	b.set(0, 1, -4);
	b.set(1, 1, 2);
	b.set(0, 2, -6);
	b.set(1, 2, 5);
	Matrix c(1, 2);
	c.set(0, 0, 4);
	c.set(0, 1, 8);

	Matrix outABP = a + b;
	test_assert(outABP.get(0, 0) == 8);
	test_assert(outABP.get(1, 0) == -2);
	test_assert(outABP.get(0, 1) == 2);
	test_assert(outABP.get(1, 1) == 16);
	test_assert(outABP.get(0, 2) == -15);
	test_assert(outABP.get(1, 2) == 15);
	Matrix outABM = a - b;
	test_assert(outABM.get(0, 0) == 2);
	test_assert(outABM.get(1, 0) == -4);
	test_assert(outABM.get(0, 1) == 10);
	test_assert(outABM.get(1, 1) == 12);
	test_assert(outABM.get(0, 2) == -3);
	test_assert(outABM.get(1, 2) == 5);

	// produces 1x3
	Matrix outACM = a * c;
	test_assert(outACM.width == c.width && outACM.height == a.height);
	test_assert(outACM.get(0, 0) == a.get(0, 0) * c.get(0, 0) + a.get(1, 0) * c.get(0, 1));
	test_assert(outACM.get(0, 1) == a.get(0, 1) * c.get(0, 0) + a.get(1, 1) * c.get(0, 1));
	test_assert(outACM.get(0, 2) == a.get(0, 2) * c.get(0, 0) + a.get(1, 2) * c.get(0, 1));
	// produces 1x3
	Matrix outBCM = b * c;
	test_assert(outBCM.width == c.width && outBCM.height == b.height);
	test_assert(outBCM.get(0, 0) == b.get(0, 0) * c.get(0, 0) + b.get(1, 0) * c.get(0, 1));
	test_assert(outBCM.get(0, 1) == b.get(0, 1) * c.get(0, 0) + b.get(1, 1) * c.get(0, 1));
	test_assert(outBCM.get(0, 2) == b.get(0, 2) * c.get(0, 0) + b.get(1, 2) * c.get(0, 1));
END_TEST()
#define PI 3.1415926535
BEGIN_TEST(test_mtx_vec_ops)
	// rotation CCW by PI/2
	Matrix transform2(2, 2);
	transform2.set(0, 0,  cos(PI / 2));
	transform2.set(1, 0, -sin(PI / 2));
	transform2.set(0, 1,  sin(PI / 2));
	transform2.set(1, 1,  cos(PI / 2));
	Vec2 vec2(1, 0);
	test_assert(transform2 * vec2 == Vec2(0, 1));
	Matrix transform3(3, 3);
	// rotate about Z axis
	transform3.set(0, 0,  cos(PI / 2));
	transform3.set(1, 0, -sin(PI / 2));
	transform3.set(0, 1,  sin(PI / 2));
	transform3.set(1, 1,  cos(PI / 2));
	transform3.set(2, 0,  0);
	transform3.set(2, 1,  0);
	transform3.set(0, 2,  0);
	transform3.set(1, 2,  0);
	transform3.set(2, 2,  1);
	Vec3 vec3(1, 0, 1);
	test_assert(transform3 * vec3 == Vec3(0, 1, 1));
END_TEST()
BEGIN_TEST(test_mtx_unary_ops)
	Matrix mtx(3, 5);
	mtx.map_cells(rand_cell);
	test_assert(mtx == +mtx);
	test_assert(mtx == -(-mtx));
	Matrix negative = -mtx;
	for (unsigned int x = 0; x < negative.width; ++x)
		for (unsigned int y = 0; y < negative.height; ++y)
			test_assert(negative.get(x, y) == -mtx.get(x, y));

	Matrix transposed = mtx.transposed();
	test_assert(transposed.width == mtx.height && transposed.height == mtx.width);
	for (unsigned int x = 0; x < transposed.width; ++x)
		for (unsigned int y = 0; y < transposed.height; ++y)
			test_assert(transposed.get(x, y) == mtx.get(y, x));

	Matrix ident = Matrix::Identity(5);
	MATHTYPE identDet = ident.determinant();
	test_assert(identDet == 1);

	Matrix indexed(3, 3);
	indexed.map_cells(indexed_cell);
	MATHTYPE indexedDet = indexed.determinant();
	MATHTYPE targetDet = 0 - 10*(1*22 - 21*2) + 20*(1*12 - 11*2);
	test_assert(indexedDet == targetDet);
END_TEST();

BEGIN_TEST(test_mtx_compare_ops)
	Matrix mtx(3, 9);
	mtx.map_cells(rand_cell);
	Matrix mtx2(mtx);
	test_assert(mtx == mtx2);
	test_assert(mtx2 == mtx);
	mtx2.set(2, 4, mtx2.get(2, 4) + 53);
	test_assert(mtx != mtx2);
	test_assert(mtx2 != mtx);
	Matrix mtx3(2, 2);
	mtx3.set(0, 0, mtx2.get(0, 0));
	mtx3.set(1, 0, mtx2.get(1, 0));
	mtx3.set(0, 1, mtx2.get(0, 1));
	mtx3.set(1, 1, mtx2.get(1, 1));
	test_assert(mtx2 != mtx3);
	test_assert(mtx3 != mtx2);
END_TEST()

MATHTYPE proper_map(unsigned int x, unsigned int y, MATHTYPE value)
{
	if ((x + y) % 2 == 0)
		return value * 2;
	return value / 2;
}
Matrix indexed_row(unsigned int y, Matrix mtx)
{
	(void)y;
	for (unsigned int i = 0; i < mtx.width; ++i)
		mtx.set(i, 0, i);
	return mtx;
}
Matrix indexed_column(unsigned int x, Matrix mtx)
{
	(void)x;
	for (unsigned int i = 0; i < mtx.height; ++i)
		mtx.set(0, i, i);
	return mtx;
}
MATHTYPE row_sum(unsigned int y, Matrix row)
{
	(void)y;
	MATHTYPE ret = 0;
	for (unsigned int x = 0; x < row.width; ++x)
		ret += row.get(x, 0);
	return ret;
}
MATHTYPE col_sum(unsigned int x, Matrix col)
{
	(void)x;
	MATHTYPE ret = 0;
	for (unsigned int y = 0; y < col.height; ++y)
		ret += col.get(0, y);
	return ret;
}
BEGIN_TEST(test_mtx_apply_ops)
	Matrix mtx(3, 5);
	// test map_cells
	mtx.map_cells(indexed_cell);
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 5; ++y) {
			test_assert(mtx.get(x, y) == indexed_cell(x, y, 0));
		}
	}
	mtx.map_cells(rand_cell);
	// test mapped_cells
	Matrix cellsMapped = mtx.mapped_cells(proper_map);
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 5; ++y) {
			test_assert(cellsMapped.get(x, y) == proper_map(x, y, mtx.get(x, y))) ;
		}
	}
	// test mapped_rows
	Matrix rowMapped = mtx.mapped_rows(indexed_row);
	for (unsigned int x = 0; x < rowMapped.width; ++x) {
		for (unsigned int y = 0; y < rowMapped.height; ++y) {
			test_assert(rowMapped.get(x, y) == x);
		}
	}
	// test mapped_columns
	Matrix colMapped = mtx.mapped_columns(indexed_column);
	for (unsigned int x = 0; x < colMapped.width; ++x) {
		for (unsigned int y = 0; y < colMapped.height; ++y) {
			test_assert(colMapped.get(x, y) == y);
		}
	}
	// test map_rows
	Matrix rowMappedDirect(mtx);
	rowMappedDirect.map_rows(indexed_row);
	for (unsigned int x = 0; x < rowMappedDirect.width; ++x) {
		for (unsigned int y = 0; y < rowMappedDirect.height; ++y) {
			test_assert(rowMappedDirect.get(x, y) == x);
		}
	}
	// test map_columns
	Matrix colMappedDirect(mtx);
	colMappedDirect.map_columns(indexed_column);
	for (unsigned int x = 0; x < colMappedDirect.width; ++x) {
		for (unsigned int y = 0; y < colMappedDirect.height; ++y) {
			test_assert(colMappedDirect.get(x, y) == y);
		}
	}

	// test reduced_rows
	Matrix reducedRows = mtx.reduced_rows(row_sum);
	for (unsigned int y = 0; y < reducedRows.height; ++y)
		test_assert(reducedRows.get(0, y) == row_sum(y, mtx.get_row(y)));
	// test reduced_columns
	Matrix reducedColumns = mtx.reduced_columns(col_sum);
	for (unsigned int x = 0; x < reducedColumns.width; ++x)
		test_assert(reducedColumns.get(x, 0) == col_sum(x, mtx.get_column(x)));
END_TEST()

BEGIN_TEST(test_mtx_ctors)
	test_mtx_constctors();
	test_mtx_normal_ctors();
END_TEST()

BEGIN_TEST(test_mtx_accesses)
	// Test .get()
	Matrix mtx = Matrix::Identity(3);
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 3; ++y) {
			if (x == y) {
				test_assert(mtx.get(x, y) == 1, ", on case Identity(3)");
			} else {
				test_assert(mtx.get(x, y) == 0, ", on case Identity(3)");
			}
		}
	}
	// Test .set()
	mtx.set(0, 0, 10);
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 3; ++y) {
			if (x == 0 && y == 0) {
				// Test .get_mut()
				MATHTYPE &v = mtx.get_mut(x, y);
				test_assert(v == 10, ", after set");
				v = 6;
				test_assert(mtx.get(x, y) == 6, ", after set again");
			} else if (x == y) {
				test_assert(mtx.get(x, y) == 1, ", after set");
			} else {
				test_assert(mtx.get(x, y) == 0, ", after set");
			}
		}
	}
	// Copy row/column
	Matrix row = mtx.get_row(1);
	test_assert(row.width == 3 && row.height == 1);
	for (unsigned int x = 0; x < 3; ++x)
		test_assert(row.get(x, 0) == x % 2); // 0 1 0
	Matrix col = mtx.get_column(2);
	test_assert(col.width == 1 && col.height == 3);
	for (unsigned int y = 0; y < 3; ++y) {
		test_assert(col.get(0, y) == (y == 2)); // 0 0 1
	}
	// Make sure it's not mutably borrowed
	row.set(1, 0, -3);
	col.set(0, 0, 22);
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 3; ++y) {
			if (x == 0 && y == 0) {
				test_assert(mtx.get(x, y) == 6, ", on case Identity(3)");
			} else if (x == y) {
				test_assert(mtx.get(x, y) == 1, ", on case Identity(3)");
			} else {
				test_assert(mtx.get(x, y) == 0, ", on case Identity(3)");
			}
		}
	}
	// Test mut get
	MathTypePointerList rowMut = mtx.get_row_mut(0);
	MathTypePointerList colMut = mtx.get_column_mut(1);
	*rowMut[1] = -5;
	*colMut[2] = 33;
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 3; ++y) {
			if (x == 0 && y == 0) {
				test_assert(mtx.get(x, y) == 6);
			} else if (x == 1 && y == 0) {
				test_assert(mtx.get(x, y) == -5, ", on case rowMut");
			} else if (x == 1 && y == 2) {
				test_assert(mtx.get(x, y) == 33, ", on case colMut");
			} else if (x == y) {
				test_assert(mtx.get(x, y) == 1);
			} else {
				test_assert(mtx.get(x, y) == 0);
			}
		}
	}


END_TEST()
BEGIN_TEST(test_mtx_rw_accesses)
	test_not_implemented();
END_TEST()
BEGIN_TEST(test_mtx_normal_ctors)
	Matrix mtxS(5);
	test_assert(mtxS.width == 5 && mtxS.height == 5);
	Matrix mtxWH(2, 5);
	test_assert(mtxWH.width == 2 && mtxWH.height == 5);

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			mtxS.set(i, j, rand());
	Matrix mtxMtx(mtxS);
	test_assert(mtxS.width == 5 && mtxS.height == 5);
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			test_assert(mtxMtx.get(i, j) == mtxS.get(i, j));
END_TEST()
BEGIN_TEST(test_mtx_constctors)
	Matrix mtx033 = Matrix::Zero(3);
	test_assert(mtx033.width == 3 && mtx033.height == 3);
	for (unsigned int i = 0; i < 3; ++i)
		for (unsigned int j = 0; j < 3; ++j)
			test_assert(mtx033.get(i, j) == 0, ", on case Zero(3)");

	Matrix mtx023 = Matrix::Zero(2,3);
	test_assert(mtx023.width == 2 && mtx023.height == 3);
	for (unsigned int i = 0; i < 2; ++i)
		for (unsigned int j = 0; j < 3; ++j)
			test_assert(mtx023.get(i, j) == 0, ", on case Zero(2,3)");

	Matrix mtx144 = Matrix::Identity(4);
	test_assert(mtx144.width == 4 && mtx144.height == 4);
	for (unsigned int i = 0; i < 4; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			if (i == j) {
				test_assert(mtx144.get(i, j) == 1, ", on case Identity(4)");
			} else {
				test_assert(mtx144.get(i, j) == 0, ", on case Identity(4)");
			}
		}
	}
END_TEST()

BEGIN_TEST(test_vec4)
	test_vec4_ctors();
	test_vec4_unary_ops();
	test_vec4_scalar_ops();
	test_vec4_vector_ops();
END_TEST()

BEGIN_TEST(test_vec4_vector_ops)
	Vec4 a(15, -11, 9, 5);
	Vec4 b(-16, -12, 4, 20);
	Vec4 out = a + b;
	test_assert(out.x == -1 && out.y == -23 && out.z == 13 && out.w == 25);
	out = a - b;
	test_assert(out.x == 31 && out.y == 1 && out.z == 5 && out.w == -15);
	out = a * b;
	test_assert(out.x == -240 && out.y == 132 && out.z == 36 && out.w == 100);
	out = a / b;
	test_assert(fabs(out.x - 15 / -16.) < 0.000001 && fabs(out.y - -11. / -12.) < 0.000001 && fabs(out.z - 9/4.) < 0.000001 && fabs(out.w - 5 / 20.) < 0.000001);
	out = a % b;
	test_assert(out.x == 15 && out.y == -11 && out.z == 1 && out.w == 5);
	test_assert(a.dot(b) == 28);
	test_assert(Vec4(-1, 0, 0, 0).dot(Vec4(1, 0, 0, 0)) == -1);
	test_assert(fabs(a.projected_length(b) - 0.980195) < 0.000001);
	test_assert(a.projected(b) == b.normalized() * a.projected_length(b));
	test_assert(a - a.projected(b) == a.rejected(b));
END_TEST()

BEGIN_TEST(test_vec4_scalar_ops)
	Vec4 vec(-22, 64, 38, 18);
	Vec4 out = vec + 2;
	test_assert(out.x == -20 && out.y == 66 && out.z == 40 && out.w == 20);
	out = vec - 2;
	test_assert(out.x == -24 && out.y == 62 && out.z == 36 && out.w == 16);
	out = vec * 2;
	test_assert(out.x == -44 && out.y == 128 && out.z == 76 && out.w == 36);
	out = vec / 2;
	test_assert(out.x == -11 && out.y == 32 && out.z == 19 && out.w == 9);
	out = vec % 5;
	test_assert(out.x == -2 && out.y == 4 && out.z == 3 && out.w == 3);
	vec += 3;
	test_assert(vec.x == -19 && vec.y == 67 && vec.z == 41 && vec.w == 21);
	vec -= 5;
	test_assert(vec.x == -24 && vec.y == 62 && vec.z == 36 && vec.w == 16);
	vec *= 2;
	test_assert(vec.x == -48 && vec.y == 124 && vec.z == 72 && vec.w == 32);
	vec /= -4;
	test_assert(vec.x == 12 && vec.y == -31 && vec.z == -18 && vec.w == -8);
	vec %= 3;
	test_assert(vec.x == 0 && vec.y == -1 && vec.z == 0 && vec.w == -2);
	vec.scale(-3);
	test_assert(vec.x == 0 && vec.y == 3 && vec.z == 0 && vec.w == 6);
	vec.x = -22;
	vec.y = 64;
	vec.z = 38;
	vec.w = 18;
	out = 2 + vec;
	test_assert(out.x == -20 && out.y == 66 && out.z == 40 && out.w == 20);
	out = 2 - vec;
	test_assert(out.x == 24 && out.y == -62 && out.z == -36 && out.w == -16);
	out = 2 * vec;
	test_assert(out.x == -44 && out.y == 128 && out.z == 76 && out.w == 36);
	out = 2 / vec;
	test_assert(out == Vec4(-1 / 11., 1 / 32., 1 / 19., 1 / 9.));
	out = 5 % vec;
	test_assert(out.x == 5 && out.y == 5 && out.z == 5 && out.w == 5);
END_TEST()

BEGIN_TEST(test_vec4_unary_ops)
	Vec4 vec(-45, 61, 73, 19);
	vec = +vec;
	test_assert(vec.x == -45 && vec.y == 61 && vec.z == 73 && vec.w == 19);
	vec = -vec;
	test_assert(vec.x == 45 && vec.y == -61 && vec.z == -73 && vec.w == -19);

	test_assert(vec.length_squared() == 11436);
	test_assert(fabs(vec.length() * vec.length() - vec.length_squared()) < 0.001);
	vec.normalize();
	test_assert(fabs(vec.length() - 1) < 0.000001);
	vec.limit_length(0.75, 0.5);
	test_assert(fabs(vec.length() - 0.75) < 0.000001);
	vec.limit_length(1.5, 1.25);
	test_assert(fabs(vec.length() - 1.25) < 0.000001);
	vec = Vec4(1, 5, -3, 8);
	vec.clamp(1.5, 8);
	test_assert(vec.x == 1.5 && vec.y == 5 && vec.z == 1.5 && vec.w == 8);
	vec.clamp(0.2, 1.8);
	test_assert(vec.x == 1.5 && fabs(vec.y - 1.8) < 0.000001 && vec.z == 1.5 && fabs(vec.w - 1.8) < 0.000001);
END_TEST()

BEGIN_TEST(test_vec4_ctors)
	test_vec4_constctors();
	test_vec4_normalctors();
END_TEST()

BEGIN_TEST(test_vec4_constctors)
	Vec4 vec = Vec4::Zero();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 0 && vec.w == 0);
	vec = Vec4::One();
	test_assert(vec.x == 1 && vec.y == 1 && vec.z == 1 && vec.w == 1);
	vec = Vec4::X();
	test_assert(vec.x == 1 && vec.y == 0 && vec.z == 0 && vec.w == 0);
	vec = Vec4::Y();
	test_assert(vec.x == 0 && vec.y == 1 && vec.z == 0 && vec.w == 0);
	vec = Vec4::Z();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 1 && vec.w == 0);
	vec = Vec4::W();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 0 && vec.w == 1);
END_TEST()

BEGIN_TEST(test_vec4_normalctors)
	Vec4 vec = Vec4();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 0 && vec.w == 0);
	vec = Vec4(4);
	test_assert(vec.x == 4 && vec.y == 4 && vec.z == 4 && vec.w == 4);
	vec = Vec4(1, -3, 2, 9);
	test_assert(vec.x == 1 && vec.y == -3 && vec.z == 2 && vec.w == 9);
	Vec4 other(vec);
	test_assert(vec.x == 1 && vec.y == -3 && vec.z == 2 && vec.w == 9);
	test_assert(other.x == 1 && other.y == -3 && other.z == 2 && other.w == 9);
	other = Vec4(Vec4(42, -93, 11, 2));
	test_assert(other.x == 42 && other.y == -93 && other.z == 11 && other.w == 2);
	other = vec;
	test_assert(vec.x == 1 && vec.y == -3 && vec.z == 2 && vec.w == 9);
	test_assert(other.x == 1 && other.y == -3 && other.z == 2 && other.w == 9);
END_TEST()

BEGIN_TEST(test_vec3)
	test_vec3_ctors();
	test_vec3_unary_ops();
	test_vec3_scalar_ops();
	test_vec3_vector_ops();
END_TEST()

BEGIN_TEST(test_vec3_vector_ops)
	Vec3 a(15, -11, 9);
	Vec3 b(-16, -12, 4);
	Vec3 out = a + b;
	test_assert(out.x == -1 && out.y == -23 && out.z == 13);
	out = a - b;
	test_assert(out.x == 31 && out.y == 1 && out.z == 5);
	out = a * b;
	test_assert(out.x == -240 && out.y == 132 && out.z == 36);
	out = a / b;
	test_assert(fabs(out.x - 15 / -16.) < 0.000001 && fabs(out.y - -11. / -12.) < 0.000001 && fabs(out.z - 9/4.) < 0.000001);
	out = a % b;
	test_assert(out.x == 15 && out.y == -11 && out.z == 1);
	test_assert(a.dot(b) == -72);
	test_assert(Vec3(-1, 0, 0).dot(Vec3(1, 0, 0)) == -1);
	test_assert(fabs(a.projected_length(b) - -3.530092) < 0.000001);
	test_assert(a.projected(b) == b.normalized() * a.projected_length(b));
	test_assert(a - a.projected(b) == a.rejected(b));
	out = a.crossed(b);
	test_assert(fabs(out.angle(a) - 3.1415926535 / 2.) < 0.000001);
	test_assert(fabs(out.angle(b) - 3.1415926535 / 2.) < 0.000001);
END_TEST()

BEGIN_TEST(test_vec3_scalar_ops)
	Vec3 vec(-22, 64, 38);
	Vec3 out = vec + 2;
	test_assert(out.x == -20 && out.y == 66 && out.z == 40);
	out = vec - 2;
	test_assert(out.x == -24 && out.y == 62 && out.z == 36);
	out = vec * 2;
	test_assert(out.x == -44 && out.y == 128 && out.z == 76);
	out = vec / 2;
	test_assert(out.x == -11 && out.y == 32 && out.z == 19);
	out = vec % 5;
	test_assert(out.x == -2 && out.y == 4 && out.z == 3);
	vec += 3;
	test_assert(vec.x == -19 && vec.y == 67 && vec.z == 41);
	vec -= 5;
	test_assert(vec.x == -24 && vec.y == 62 && vec.z == 36);
	vec *= 2;
	test_assert(vec.x == -48 && vec.y == 124 && vec.z == 72);
	vec /= -4;
	test_assert(vec.x == 12 && vec.y == -31 && vec.z == -18);
	vec %= 3;
	test_assert(vec.x == 0 && vec.y == -1 && vec.z == 0);
	vec.scale(-3);
	test_assert(vec.x == 0 && vec.y == 3 && vec.z == 0);
	vec.x = -22;
	vec.y = 64;
	vec.z = 38;
	out = 2 + vec;
	test_assert(out.x == -20 && out.y == 66 && out.z == 40);
	out = 2 - vec;
	test_assert(out.x == 24 && out.y == -62 && out.z == -36);
	out = 2 * vec;
	test_assert(out.x == -44 && out.y == 128 && out.z == 76);
	out = 2 / vec;
	test_assert(out == Vec3(-1 / 11., 1 / 32., 1 / 19.));
	out = 5 % vec;
	test_assert(out.x == 5 && out.y == 5 && out.z == 5);
END_TEST()

BEGIN_TEST(test_vec3_unary_ops)
	Vec3 vec(-45, 61, 73);
	vec = +vec;
	test_assert(vec.x == -45 && vec.y == 61 && vec.z == 73);
	vec = -vec;
	test_assert(vec.x == 45 && vec.y == -61 && vec.z == -73);

	test_assert(vec.length_squared() == 11075);
	test_assert(fabs(vec.length() * vec.length() - vec.length_squared()) < 0.001);
	vec.normalize();
	test_assert(fabs(vec.length() - 1) < 0.000001);
	vec.limit_length(0.75, 0.5);
	test_assert(fabs(vec.length() - 0.75) < 0.000001);
	vec.limit_length(1.5, 1.25);
	test_assert(fabs(vec.length() - 1.25) < 0.000001);
	vec = Vec3(1, 5, -3);
	vec.clamp(1.5, 8);
	test_assert(vec.x == 1.5 && vec.y == 5 && vec.z == 1.5);
	vec.clamp(0.2, 1.8);
	test_assert(vec.x == 1.5 && fabs(vec.y - 1.8) < 0.000001 && vec.z == 1.5);
END_TEST()

BEGIN_TEST(test_vec3_ctors)
	test_vec3_constctors();
	test_vec3_normalctors();
END_TEST()

BEGIN_TEST(test_vec3_constctors)
	Vec3 vec = Vec3::Zero();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 0);
	vec = Vec3::One();
	test_assert(vec.x == 1 && vec.y == 1 && vec.z == 1);
	vec = Vec3::X();
	test_assert(vec.x == 1 && vec.y == 0 && vec.z == 0);
	vec = Vec3::Y();
	test_assert(vec.x == 0 && vec.y == 1 && vec.z == 0);
	vec = Vec3::Z();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 1);
END_TEST()

BEGIN_TEST(test_vec3_normalctors)
	Vec3 vec = Vec3();
	test_assert(vec.x == 0 && vec.y == 0 && vec.z == 0);
	vec = Vec3(4);
	test_assert(vec.x == 4 && vec.y == 4 && vec.z == 4);
	vec = Vec3(1, -3, 2);
	test_assert(vec.x == 1 && vec.y == -3 && vec.z == 2);
	Vec3 other(vec);
	test_assert(vec.x == 1 && vec.y == -3 && vec.z == 2);
	test_assert(other.x == 1 && other.y == -3 && other.z == 2);
	other = Vec3(Vec3(42, -93, 11));
	test_assert(other.x == 42 && other.y == -93 && other.z == 11);
	other = vec;
	test_assert(vec.x == 1 && vec.y == -3 && vec.z == 2);
	test_assert(other.x == 1 && other.y == -3 && other.z == 2);
END_TEST()

BEGIN_TEST(test_vec2)
	test_vec2_ctors();
	test_vec2_unary_ops();
	test_vec2_scalar_ops();
	test_vec2_vector_ops();
END_TEST()

BEGIN_TEST(test_vec2_vector_ops)
	Vec2 a(15, -11);
	Vec2 b(-16, -12);
	Vec2 out = a + b;
	test_assert(out.x == -1 && out.y == -23);
	out = a - b;
	test_assert(out.x == 31 && out.y == 1);
	out = a * b;
	test_assert(out.x = -240 && out.y == 132);
	out = a / b;
	test_assert(fabs(out.x - 15 / -16.) < 0.000001 && fabs(out.y - -11. / -12.) < 0.000001);
	out = a % b;
	test_assert(out.x == 15 && out.y == -11);
	test_assert(a.dot(b) == -108);
	test_assert(Vec2(-1, 0).dot(Vec2(1, 0)) == -1);
	test_assert(fabs(a.projected_length(b) - -5.4) < 0.000001);
	test_assert(a.projected(b) == b.normalized() * a.projected_length(b));
	test_assert(a - a.projected(b) == a.rejected(b));
END_TEST()

BEGIN_TEST(test_vec2_scalar_ops)
	Vec2 vec(-22, 64);
	Vec2 out = vec + 2;
	test_assert(out.x == -20 && out.y == 66);
	out = vec - 2;
	test_assert(out.x == -24 && out.y == 62);
	out = vec * 2;
	test_assert(out.x == -44 && out.y == 128);
	out = vec / 2;
	test_assert(out.x == -11 && out.y == 32);
	out = vec % 5;
	test_assert(out.x == -2 && out.y == 4);
	vec += 3;
	test_assert(vec.x == -19 && vec.y == 67);
	vec -= 5;
	test_assert(vec.x == -24 && vec.y == 62);
	vec *= 2;
	test_assert(vec.x == -48 && vec.y == 124);
	vec /= -4;
	test_assert(vec.x == 12 && vec.y == -31);
	vec %= 3;
	test_assert(vec.x == 0 && vec.y == -1);
	vec.scale(-3);
	test_assert(vec.x == 0 && vec.y == 3);
	vec.x = -22;
	vec.y = 64;
	out = 2 + vec;
	test_assert(out.x == -20 && out.y == 66);
	out = 2 - vec;
	test_assert(out.x == 24 && out.y == -62);
	out = 2 * vec;
	test_assert(out.x == -44 && out.y == 128);
	out = 2 / vec;
	test_assert(out == Vec2(-1 / 11., 1 / 32.));
	out = 5 % vec;
	test_assert(out.x == 5 && out.y == 5);
END_TEST()

BEGIN_TEST(test_vec2_ctors)
	test_vec2_constctors();
	test_vec2_normalctors();
END_TEST()

BEGIN_TEST(test_vec2_constctors)
	Vec2 vec = Vec2::Zero();
	test_assert(vec.x == 0 && vec.y == 0);
	vec = Vec2::One();
	test_assert(vec.x == 1 && vec.y == 1);
	vec = Vec2::X();
	test_assert(vec.x == 1 && vec.y == 0);
	vec = Vec2::Y();
	test_assert(vec.x == 0 && vec.y == 1);
END_TEST()

BEGIN_TEST(test_vec2_normalctors)
	Vec2 vec = Vec2();
	test_assert(vec.x == 0 && vec.y == 0);
	vec = Vec2(4);
	test_assert(vec.x == 4 && vec.y == 4);
	vec = Vec2(1, -3);
	test_assert(vec.x == 1 && vec.y == -3);
	Vec2 other(vec);
	test_assert(vec.x == 1 && vec.y == -3);
	test_assert(other.x == 1 && other.y == -3);
	other = Vec2(Vec2(42, -93));
	test_assert(other.x == 42 && other.y == -93);
	other = vec;
	test_assert(vec.x == 1 && vec.y == -3);
	test_assert(other.x == 1 && other.y == -3);
END_TEST()

BEGIN_TEST(test_vec2_unary_ops)
	Vec2 vec(-45, 61);
	vec = +vec;
	test_assert(vec.x == -45 && vec.y == 61);
	vec = -vec;
	test_assert(vec.x == 45 && vec.y == -61);

	test_assert(vec.length_squared() == 5746);
	test_assert(vec.length() * vec.length() == vec.length_squared());
	vec.normalize();
	test_assert(fabs(vec.length() - 1) < 0.000001);
	vec.limit_length(0.75, 0.5);
	test_assert(fabs(vec.length() - 0.75) < 0.000001);
	vec.limit_length(1.5, 1.25);
	test_assert(fabs(vec.length() - 1.25) < 0.000001);
	vec = Vec2(1, 5);
	vec.clamp(1.5, 8);
	test_assert(vec.x == 1.5 && vec.y == 5);
	vec.clamp(0.2, 1.8);
	test_assert(vec.x == 1.5 && fabs(vec.y - 1.8) < 0.000001);
	vec = Vec2::One();
	test_assert(fabs(vec.angle() - 3.1415926535 / 4) < 0.000001);
	vec.normalize();
	test_assert(fabs(vec.angle() - 3.1415926535 / 4) < 0.000001);

END_TEST()

__attribute__((noreturn))
void test_fail(std::string const &reason)
{
	std::cerr << "\e[91mTest \e[36m" << currentTest << " \e[91mfailed: " << reason << std::endl;
	exit(1);
}
}
