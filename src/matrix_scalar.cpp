#include "mathtype.hpp"
#include "matrix.hpp"

#define MTX_OP(op) Matrix Matrix::operator op(MATHTYPE other) const \
{ \
	Matrix ret(*this); \
	for (unsigned int x = 0; x < ret.width; ++x) \
		for (unsigned int y = 0; y < ret.height; ++y) \
			ret._array[y * ret.width + x] op##= other; \
	return ret; \
}
namespace ZMathLib_Graphics {
MTX_OP(+)
MTX_OP(-)
MTX_OP(*)
MTX_OP(/)
}
ZMathLib_Graphics::Matrix operator*(MATHTYPE other, ZMathLib_Graphics::Matrix mtx)
{
	return mtx * other;
}
