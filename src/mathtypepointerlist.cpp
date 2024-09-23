#include "mathtype.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

namespace ZMathLib_Graphics {
MathTypePointerList::MathTypePointerList(size_t len) : length(len)
{
	_array = (MATHTYPE **) malloc(sizeof(MATHTYPE *) * length);
	for (size_t i = 0; i < length; ++i)
		_array[i] = nullptr;
}
MathTypePointerList::~MathTypePointerList()
{
	// don't free each index, since those are references to memory someone else (Matrix) controls!
	free(_array);
}
MATHTYPE *&MathTypePointerList::operator[](size_t index) const
{
	if (index >= length)
		throw std::out_of_range("index exceeded length of MathTypePointerList");
	return _array[index];
}
}
