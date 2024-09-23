#include "matrix.hpp"
#include <cmath>

#ifndef MIN_ERROR_EQUAL
#define MIN_ERROR_EQUAL 0.0001
#endif
namespace ZMathLib_Graphics {
bool Matrix::operator==(Matrix other) const
{
	if (width != other.width)
		return false;
	if (height != other.height)
		return false;
	for (unsigned int x = 0; x < width; ++x) {
		for (unsigned int y = 0; y < height; ++y) {
			if (fabs(_array[y * width + x] - other._array[y * width + x]) >= (MIN_ERROR_EQUAL))
				return false;
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix other) const
{
	return !(*this == other);
}
}
