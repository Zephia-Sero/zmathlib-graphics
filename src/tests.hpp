#ifndef TESTS_HPP
#define TESTS_HPP

#include <cstdio>
#include <string>
#define BEGIN_TEST(testName) void testName() \
{ \
	currentTest = #testName; \
	printf("%*s\e[37mRunning \e[36m" #testName "\e[37m...\n", 8 * indent, ""); \
	++indent;
#define END_TEST() \
	--indent; \
}

#define test_not_implemented() \
	printf("%*s\e[91mTest not yet implemented\n", 8*indent, "");

#define test_assert(condition, ...) \
	{if (!(condition)) \
		test_fail(#condition __VA_ARGS__);}

namespace ZMathLib_Graphics::Tests {
	void test_all();

	void test_mtx_transforms();

	void test_vec_conversions();
	void test_vec2_conversions();
	void test_vec3_conversions();
	void test_vec4_conversions();

	void test_mtx();
	void test_mtx_unary_ops();
	void test_mtx_apply_ops();
	void test_mtx_mtx_ops();
	void test_mtx_vec_ops();
	void test_mtx_compare_ops();
	void test_mtx_accesses();
	void test_mtx_ctors();
	void test_mtx_constctors();
	void test_mtx_normal_ctors();

	void test_vec4();
	void test_vec4_unary_ops();
	void test_vec4_scalar_ops();
	void test_vec4_vector_ops();
	void test_vec4_ctors();
	void test_vec4_constctors();
	void test_vec4_normalctors();

	void test_vec3();
	void test_vec3_unary_ops();
	void test_vec3_scalar_ops();
	void test_vec3_vector_ops();
	void test_vec3_ctors();
	void test_vec3_constctors();
	void test_vec3_normalctors();

	void test_vec2();
	void test_vec2_unary_ops();
	void test_vec2_scalar_ops();
	void test_vec2_vector_ops();
	void test_vec2_ctors();
	void test_vec2_constctors();
	void test_vec2_normalctors();

	extern char const *currentTest;
	extern unsigned int indent;
	void test_fail(std::string const &reason);
}

#endif
