cmake_minimum_required(VERSION 3.3)

project(GhulbusMath CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if($ENV{TRAVIS})
    if($ENV{TRAVIS} STREQUAL "true")
        message(STATUS "Building on Travis-CI.")
        set(IS_TRAVIS_BUILD TRUE)
    endif()
endif()

option(GB_GENERATE_COVERAGE_INFO "If set, line coverage info will be generated from debug test runs." OFF)
if(GB_GENERATE_COVERAGE_INFO)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # this is an undocumented option for changing the output extension from *.cpp.ext
        # to *.ext; As there is no reasonable way to obtain the list of object files
        # this seems to be the best option to generate the naming gcov expects.
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
        set(GCOV_COMMAND gcov CACHE STRING "Command to invoke to run gcov.")
    endif()
endif()

###############################################################################
## Library gbMath
###############################################################################

set(GB_MATH_VERSION_MAJOR 0)
set(GB_MATH_VERSION_MINOR 1)
set(GB_MATH_VERSION_PATCH 0)
set(GB_MATH_VERSION "${GB_MATH_VERSION_MAJOR}.${GB_MATH_VERSION_MINOR}.${GB_MATH_VERSION_PATCH}")

set(GB_MATH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GB_MATH_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

set(GB_MATH_HEADER_FILES
    ${GB_MATH_INCLUDE_DIR}/gbMath/config.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/MatrixIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/MatrixPolicies.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/NumberTypeTraits.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2Swizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorSwizzle.hpp
)

set(GB_MATH_TEST_SOURCES
    ${GB_MATH_TEST_DIR}/test_utils/MultiplicationOrderAwareOperand.hpp
    ${GB_MATH_TEST_DIR}/TestMatrix2.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix3.cpp
    ${GB_MATH_TEST_DIR}/TestVector2.cpp
    ${GB_MATH_TEST_DIR}/TestVector3.cpp
    ${GB_MATH_TEST_DIR}/TestVectorSwizzle.cpp
    ${GB_MATH_TEST_DIR}/TestMath.cpp
)

add_library(gbMath INTERFACE)
target_sources(gbMath INTERFACE ${GB_MATH_HEADER_FILES})
target_include_directories(gbMath INTERFACE ${GB_MATH_INCLUDE_DIR})
target_compile_features(gbMath INTERFACE cxx_lambdas cxx_override cxx_range_for)
target_compile_features(gbMath INTERFACE cxx_attributes cxx_func_identifier cxx_noexcept)
target_compile_options(gbMath INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/W4>)
target_compile_options(gbMath INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>:-pedantic -Wall>)

###############################################################################
## Testing gbMath
###############################################################################

option(GB_BUILD_TESTS "Determines whether to build tests." ON)
if(GB_BUILD_TESTS)
    enable_testing()

    if(NOT TARGET Catch)
        include(ExternalProject)
        if(IS_TRAVIS_BUILD)     # on travis, use git for fetching instead of wget
            set(GB_FETCH_EXTERNAL_CATCH
                GIT_REPOSITORY https://github.com/philsquared/Catch.git
                GIT_TAG 0c1c9fa9229c7358ce16c9910004a39290b20f5f)
        elseif(WIN32)
            set(GB_FETCH_EXTERNAL_CATCH
                URL https://github.com/philsquared/Catch/archive/v1.2.1-develop.12.zip
                URL_HASH MD5=cda228922a1c9248364c99a3ff9cd9fa)
        else()
            set(GB_FETCH_EXTERNAL_CATCH
                URL https://github.com/philsquared/Catch/archive/v1.2.1-develop.12.tar.gz
                URL_HASH MD5=a8dfb7be899a6e7fb30bd55d53426122)
        endif()
        ExternalProject_Add(Catch-External
            PREFIX ${CMAKE_BINARY_DIR}/external/Catch
            ${GB_FETCH_EXTERNAL_CATCH}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/Catch/src/Catch-External/single_include/catch.hpp
                                                     ${CMAKE_BINARY_DIR}/external/Catch/include/catch.hpp
        )
        add_library(Catch INTERFACE)
        add_dependencies(Catch Catch-External)
        target_include_directories(Catch INTERFACE ${CMAKE_BINARY_DIR}/external/Catch/include)
    endif()

    add_executable(gbMath_Test ${GB_MATH_TEST_SOURCES})
    target_link_libraries(gbMath_Test gbMath Catch)
    target_include_directories(gbMath_Test PRIVATE ${GB_MATH_TEST_DIR})
    add_test(NAME TestMath COMMAND gbMath_Test)

    if(GB_GENERATE_COVERAGE_INFO AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
        target_compile_options(gbMath_Test PRIVATE --coverage -fprofile-arcs -ftest-coverage)
        target_link_libraries(gbMath_Test -fprofile-arcs -ftest-coverage)
        add_custom_target(gbMath_TestCoverage
            COMMAND ${GCOV_COMMAND} -o CMakeFiles/gbMath_Test.dir/test ${GB_MATH_TEST_SOURCES}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            COMMENT "Collecting gcov coverage information"
        )
    endif()

endif()
