cmake_minimum_required(VERSION 3.24)

project(GhulbusMath CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

if(MSVC)
    option(GB_PARALLEL_BUILD "If set, uses multiple build processes in parallel." ON)
    if(GB_PARALLEL_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif()
endif()

###############################################################################
## Library gbMath
###############################################################################

set(GB_MATH_VERSION_MAJOR 0)
set(GB_MATH_VERSION_MINOR 9)
set(GB_MATH_VERSION_PATCH 0)
set(GB_MATH_VERSION "${GB_MATH_VERSION_MAJOR}.${GB_MATH_VERSION_MINOR}.${GB_MATH_VERSION_PATCH}")

set(GB_MATH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GB_MATH_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

add_library(gbMath INTERFACE)
target_sources(gbMath
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${GB_MATH_INCLUDE_DIR}
    FILES
    ${GB_MATH_INCLUDE_DIR}/gbMath/config.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/AABB2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/AABB3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Basis3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Circle2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Color4.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/ComponentVector3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Line2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Line3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix4.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/MatrixIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/MatrixPolicies.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/NumberTypeTraits.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/OBB3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Rational.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/RationalIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Sphere3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Tensor3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Transform2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Transform3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/TransformLine3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2Swizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector3Swizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector4.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorSwizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorTraits.hpp
)
target_compile_options(gbMath INTERFACE $<BUILD_INTERFACE:$<$<CXX_COMPILER_ID:MSVC>:/W4>>)
target_compile_options(gbMath INTERFACE $<BUILD_INTERFACE:$<$<CXX_COMPILER_ID:MSVC>:/permissive->>)
target_compile_options(gbMath INTERFACE
    $<BUILD_INTERFACE:$<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>:-pedantic -Wall>>)
target_compile_options(gbMath INTERFACE $<$<CXX_COMPILER_ID:GNU>:-pedantic -Wall>)

###############################################################################
## Testing gbMath
###############################################################################

set(GB_MATH_TEST_SOURCES
${GB_MATH_TEST_DIR}/TestAABB2.cpp
    ${GB_MATH_TEST_DIR}/TestAABB3.cpp
    ${GB_MATH_TEST_DIR}/TestBasis3.cpp
    ${GB_MATH_TEST_DIR}/TestCircle2.cpp
    ${GB_MATH_TEST_DIR}/TestColor4.cpp
    ${GB_MATH_TEST_DIR}/TestComponentVector3.cpp
    ${GB_MATH_TEST_DIR}/TestLine2.cpp
    ${GB_MATH_TEST_DIR}/TestLine3.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix2.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix3.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix4.cpp
    ${GB_MATH_TEST_DIR}/TestMatrixIO.cpp
    ${GB_MATH_TEST_DIR}/TestOBB3.cpp
    ${GB_MATH_TEST_DIR}/TestRational.cpp
    ${GB_MATH_TEST_DIR}/TestRationalIO.cpp
    ${GB_MATH_TEST_DIR}/TestSphere3.cpp
    ${GB_MATH_TEST_DIR}/TestTensor3.cpp
    ${GB_MATH_TEST_DIR}/TestTransform2.cpp
    ${GB_MATH_TEST_DIR}/TestTransform3.cpp
    ${GB_MATH_TEST_DIR}/TestTransformLine3.cpp
    ${GB_MATH_TEST_DIR}/TestVector2.cpp
    ${GB_MATH_TEST_DIR}/TestVector3.cpp
    ${GB_MATH_TEST_DIR}/TestVector4.cpp
    ${GB_MATH_TEST_DIR}/TestVectorIO.cpp
    ${GB_MATH_TEST_DIR}/TestVectorSwizzle.cpp
    ${GB_MATH_TEST_DIR}/TestMath.cpp
)

option(GB_BUILD_TESTS "Determines whether to build tests." ON)
if(GB_BUILD_TESTS)
    enable_testing()

    if(NOT EXISTS ${PROJECT_BINARY_DIR}/external/catch2/catch_amalgamated.hpp)
        file(DOWNLOAD
             https://github.com/catchorg/Catch2/releases/download/v3.4.0/catch_amalgamated.hpp
             ${PROJECT_BINARY_DIR}/external/catch2/catch_amalgamated.hpp
             EXPECTED_HASH SHA1=be29d8580ffa74428f47e2480c327b4c1e25a183
             )
        file(DOWNLOAD
             https://github.com/catchorg/Catch2/releases/download/v3.4.0/catch_amalgamated.cpp
             ${PROJECT_BINARY_DIR}/external/catch2/catch_amalgamated.cpp
             EXPECTED_HASH SHA1=af0af6a63cee729a5672602b0c779c1d6426a546
             )
        file(WRITE ${PROJECT_BINARY_DIR}/external/catch2/catch.hpp "#include <catch_amalgamated.hpp>\n")
    endif()

    add_library(Catch2 STATIC)
    target_sources(Catch2
        PRIVATE
        ${PROJECT_BINARY_DIR}/external/catch2/catch_amalgamated.cpp
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_BINARY_DIR}/external/catch2
        FILES
        ${PROJECT_BINARY_DIR}/external/catch2/catch_amalgamated.hpp
        ${PROJECT_BINARY_DIR}/external/catch2/catch.hpp
    )

    add_executable(gbMath_Test)
    target_sources(gbMath_Test
        PRIVATE
        ${GB_MATH_TEST_SOURCES}
        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${GB_MATH_TEST_DIR}
        FILES
        ${GB_MATH_TEST_DIR}/test_utils/MultiplicationOrderAwareOperand.hpp
    )
    target_link_libraries(gbMath_Test gbMath Catch2)
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

###############################################################################
## Doxygen gbMath
###############################################################################

option(GB_GENERATE_DOXYGEN_DOCUMENTATION "If checked, API documentation will be generated if Doxygen is available." ON)
if(GB_GENERATE_DOXYGEN_DOCUMENTATION)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(GB_LIB_DOC_DIR ${PROJECT_BINARY_DIR}/doc)
        configure_file(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in ${GB_LIB_DOC_DIR}/Doxyfile @ONLY)
        add_custom_target(doxygen-doc
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${GB_LIB_DOC_DIR}
            COMMENT "Building doxygen documentation"
            SOURCES ${PROJECT_SOURCE_DIR}/doc/Doxyfile.in
        )
        source_group("" FILES ${PROJECT_SOURCE_DIR}/doc/Doxyfile.in)
    endif()
endif()

###############################################################################
## Packaging gbMath
###############################################################################

set(GB_LIBRARY_NAMESPACE Ghulbus::)

install(TARGETS gbMath EXPORT gbMathTargets
    RUNTIME DESTINATION bin/$<CONFIG>
    LIBRARY DESTINATION lib/$<CONFIG>
    ARCHIVE DESTINATION lib/$<CONFIG>
    INCLUDES DESTINATION include
    FILE_SET HEADERS
)
target_include_directories(gbMath INTERFACE $<INSTALL_INTERFACE:include>)
install(FILES LICENSE DESTINATION ".")

if(GB_GENERATE_DOXYGEN_DOCUMENTATION AND DOXYGEN_FOUND)
    install(DIRECTORY ${GB_LIB_DOC_DIR}/html DESTINATION doc MESSAGE_NEVER)
endif()

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/gbMathConfig.cmake.in
    ${PROJECT_BINARY_DIR}/cmake/gbMathConfig.cmake
    INSTALL_DESTINATION cmake
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/cmake/gbMathVersion.cmake
    VERSION ${GB_MATH_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(${PROJECT_SOURCE_DIR}/cmake/gbMathMacros.cmake.in
    ${PROJECT_BINARY_DIR}/cmake/gbMathMacros.cmake
    COPYONLY
)

# installation - build tree specific package config files
export(EXPORT gbMathTargets FILE ${PROJECT_BINARY_DIR}/cmake/gbMathTargets.cmake NAMESPACE ${GB_LIBRARY_NAMESPACE})
export(PACKAGE gbMath)

# installation - relocatable package config files
install(EXPORT gbMathTargets
    FILE gbMathTargets.cmake
    NAMESPACE ${GB_LIBRARY_NAMESPACE}
    DESTINATION cmake
)
install(FILES
    ${PROJECT_BINARY_DIR}/cmake/gbMathConfig.cmake
    ${PROJECT_BINARY_DIR}/cmake/gbMathMacros.cmake
    ${PROJECT_BINARY_DIR}/cmake/gbMathVersion.cmake
    DESTINATION cmake
)
