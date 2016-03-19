cmake_minimum_required(VERSION 3.3)

project(GhulbusMath CXX)

if($ENV{TRAVIS})
    if($ENV{TRAVIS} STREQUAL "true")
        message(STATUS "Building on Travis-CI.")
        set(IS_TRAVIS_BUILD TRUE)
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
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2SIMD.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorSwizzle.hpp
)

set(GB_MATH_TEST_SOURCES
    ${GB_MATH_TEST_DIR}/TestVector2.cpp
    ${GB_MATH_TEST_DIR}/TestVector2SIMD.cpp
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
    add_test(NAME TestMath COMMAND gbMath_Test)
endif()
