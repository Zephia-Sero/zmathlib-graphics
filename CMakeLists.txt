cmake_minimum_required (VERSION 3.11)
project (zmath VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files to the binary
add_library(zmath SHARED
        src/mathtypepointerlist.cpp
        src/matrix_builtin_transforms.cpp
        src/matrix_compare.cpp
        src/matrix.cpp
        src/matrix_mtx.cpp
        src/matrix_ops_apply.cpp
        src/matrix_scalar.cpp
        src/matrix_unary.cpp
        src/matrix_vec.cpp
        src/quaternion.cpp
        src/vec2.cpp
        src/vec3.cpp
        src/vec4.cpp
)

set(ZMATH_PUBLIC_HEADERS
        include/mathtype.hpp
        include/matrix.hpp
        include/quaternion.hpp
        include/vector.hpp
)

# Allow CMake to append version # to filename
set_target_properties(zmath PROPERTIES VERSION ${PROJECT_VERSION})

# Semantic versioning for previous
set_target_properties(zmath PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# Set external include files
set_target_properties(zmath PROPERTIES PUBLIC_HEADER "${ZMATH_PUBLIC_HEADERS}")

# Set the include directory for the library itself
target_include_directories(zmath PRIVATE "src")

# Install headers and SOs to system directories
include(GNUInstallDirs)
install(TARGETS zmath
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
