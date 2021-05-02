# CMake configuration to build LibISAAC
# License: BSD 3-clause
#
# For example usage: see README.md

cmake_minimum_required(VERSION 3.9)
project(LibISAAC
        VERSION 1.0.0
        LANGUAGES C
        DESCRIPTION
        "A modern reimplementation of the ISAAC CSPRNG.")

# Unless specified, by default create Release builds
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# -----------------------------------------------------------------------------
# Compiler flags
# -----------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Activate a million warnings to have the cleanest possible code
set(FLAGS_WARNINGS
        -Wall
        -Wextra
        -pedantic
        -Wconversion
        -Wdouble-promotion
        -Wswitch-default
        -Wswitch-enum
        -Wuninitialized
        -Wno-unused-variable
        -Wpacked
        -Wpadded
        -Wshadow
        -Wformat-security
        -Wlogical-not-parentheses
        -Waggregate-return
        -Wmissing-declarations
        -Wsign-conversion
        -Wjump-misses-init)
# Debug build: compile with no optimisation, debug info and printing
set(CMAKE_C_FLAGS_DEBUG "${WARNING_FLAGS} \
    -g3 \
    -O0 \
    -DDEBUG \
    -fprofile-instr-generate \
    -fcoverage-mapping")
# Append sanitiser flags on non-Windows systems
if (NOT WIN32 AND NOT CYGWIN AND NOT MSYS)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
            -fsanitize=address,undefined \
            -static-libsan \
            -fno-omit-frame-pointer \
            -mno-omit-leaf-frame-pointer")
endif ()

# Mini-sized release build: compile with optimisation for size
# convert warnings into errors and some other optimisations
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} \
        -DMINSIZEREL \
        ${WARNING_FLAGS} \
        -Os \
        -Werror \
        -fomit-frame-pointer \
        -march=native \
        -mtune=native")


# -----------------------------------------------------------------------------
# Source files
# -----------------------------------------------------------------------------
set(LIB_HEADER inc/isaac.h)
set(LIB_SRC_FILES src/isaac.c)
set(TEST_SRC_FILES
        tst/atto/atto.h
        tst/atto/atto.c
        tst/test.h
        tst/test.c
        tst/test_init.c
        tst/test_stream.c
        tst/test_convert.c
        tst/test_cleanup.c)



# -----------------------------------------------------------------------------
# Build targets
# -----------------------------------------------------------------------------
# Copy the library API header into the build directory.
# With this command, if the header changes, it's copied, otherwise not.
configure_file(${LIB_HEADER} ${CMAKE_BINARY_DIR} COPYONLY)

# Static library (.a) for 32-bit version of ISAAC
add_library(isaac32 STATIC ${LIB_SRC_FILES})
target_include_directories(isaac32 PUBLIC inc/)
target_compile_definitions(isaac32 PUBLIC ISAAC_BITS=32)

# Static library (.a) for 64-bit version of ISAAC
add_library(isaac64 STATIC ${LIB_SRC_FILES})
target_include_directories(isaac64 PUBLIC inc/)
target_compile_definitions(isaac64 PUBLIC ISAAC_BITS=64)

# Shared library (.dylib / .dll) for 32-bit version of ISAAC
# Does not reuse the static library object files, as they are
# recompiled in order to have position-independent code
add_library(isaac32shared SHARED ${LIB_SRC_FILES})
target_include_directories(isaac32shared PUBLIC inc/)
target_compile_definitions(isaac32shared PUBLIC ISAAC_BITS=32)
set_target_properties(isaac32shared PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERPROCEDURAL_OPTIMISATION TRUE)

# Shared library (.dylib / .dll) for 64-bit version of ISAAC
# Does not reuse the static library object files, as they are
# recompiled in order to have position-independent code
add_library(isaac64shared SHARED ${LIB_SRC_FILES})
target_include_directories(isaac64shared PUBLIC inc/)
target_compile_definitions(isaac64shared PUBLIC ISAAC_BITS=64)
set_target_properties(isaac64shared PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERPROCEDURAL_OPTIMISATION TRUE)

# Test runner executable testing the static library with the
# 32-bit version of ISAAC
add_executable(testisaac32
        ${LIB_SRC_FILES}
        ${TEST_SRC_FILES})
target_include_directories(testisaac32
        PRIVATE inc/
        PRIVATE tst/
        PRIVATE tst/atto/)
target_compile_definitions(testisaac32 PUBLIC ISAAC_BITS=32)
add_dependencies(testisaac32 isaac32)
target_link_libraries(testisaac32 PUBLIC isaac32)
set_target_properties(testisaac32 PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERPROCEDURAL_OPTIMISATION TRUE)

# Test runner executable testing the static library with the
# 64-bit version of ISAAC
add_executable(testisaac64
        ${LIB_SRC_FILES}
        ${TEST_SRC_FILES})
target_include_directories(testisaac64
        PRIVATE inc/
        PRIVATE tst/
        PRIVATE tst/atto/)
target_compile_definitions(testisaac64 PUBLIC ISAAC_BITS=64)
add_dependencies(testisaac64 isaac64)
target_link_libraries(testisaac64 PUBLIC isaac64)
set_target_properties(testisaac64 PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERPROCEDURAL_OPTIMISATION TRUE)


# Test runner executable testing the shared library with the
# 32-bit version of ISAAC
add_executable(testisaac32shared
        ${LIB_SRC_FILES}
        ${TEST_SRC_FILES})
target_include_directories(testisaac32shared
        PRIVATE inc/
        PRIVATE tst/
        PRIVATE tst/atto/)
target_compile_definitions(testisaac32shared PUBLIC ISAAC_BITS=32)
add_dependencies(testisaac32shared isaac32shared)
target_link_libraries(testisaac32shared PUBLIC isaac32shared)
set_target_properties(testisaac32shared PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERPROCEDURAL_OPTIMISATION TRUE)

# Test runner executable testing the shared library with the
# 64-bit version of ISAAC
add_executable(testisaac64shared
        ${LIB_SRC_FILES}
        ${TEST_SRC_FILES})
target_include_directories(testisaac64shared
        PRIVATE inc/
        PRIVATE tst/
        PRIVATE tst/atto/)
target_compile_definitions(testisaac64shared PUBLIC ISAAC_BITS=64)
add_dependencies(testisaac64shared isaac64shared)
target_link_libraries(testisaac64shared PUBLIC isaac64shared)
set_target_properties(testisaac64shared PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERPROCEDURAL_OPTIMISATION TRUE)

# Doxygen documentation builder
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Cmake's wrapper of Doxygen, constructing a doxyfile from the
    # DOXYGEN_* variables, which are mapped to the Doxygen variables.
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_SORT_MEMBER_DOCS NO)
    set(DOXYGEN_ALIASES license="**License:**")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    doxygen_add_docs(doxygen
            # List of input files for Doxygen
            ${PROJECT_SOURCE_DIR}/inc/isaac.h
            ${PROJECT_SOURCE_DIR}/LICENSE.md
            ${PROJECT_SOURCE_DIR}/README.md
            ${PROJECT_SOURCE_DIR}/CHANGELOG.md)
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen not found. Cannot generate documentation.")
endif (DOXYGEN_FOUND)
