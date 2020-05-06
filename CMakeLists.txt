cmake_minimum_required(VERSION 3.12)

project(GhulbusMath CXX)

set(CMAKE_CXX_STANDARD 17)
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
    ${GB_MATH_INCLUDE_DIR}/gbMath/AABB3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Color4.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Line2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Line3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Matrix4.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/MatrixIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/MatrixPolicies.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/NumberTypeTraits.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/OBB3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Sphere3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Transform2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Transform3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector2Swizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector3.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector3Swizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/Vector4.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorIO.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorSwizzle.hpp
    ${GB_MATH_INCLUDE_DIR}/gbMath/VectorTraits.hpp
)

set(GB_MATH_TEST_SOURCES
    ${GB_MATH_TEST_DIR}/test_utils/MultiplicationOrderAwareOperand.hpp
    ${GB_MATH_TEST_DIR}/TestAABB3.cpp
    ${GB_MATH_TEST_DIR}/TestColor4.cpp
    ${GB_MATH_TEST_DIR}/TestLine2.cpp
    ${GB_MATH_TEST_DIR}/TestLine3.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix2.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix3.cpp
    ${GB_MATH_TEST_DIR}/TestMatrix4.cpp
    ${GB_MATH_TEST_DIR}/TestMatrixIO.cpp
    ${GB_MATH_TEST_DIR}/TestOBB3.cpp
    ${GB_MATH_TEST_DIR}/TestSphere3.cpp
    ${GB_MATH_TEST_DIR}/TestTransform2.cpp
    ${GB_MATH_TEST_DIR}/TestTransform3.cpp
    ${GB_MATH_TEST_DIR}/TestVector2.cpp
    ${GB_MATH_TEST_DIR}/TestVector3.cpp
    ${GB_MATH_TEST_DIR}/TestVector4.cpp
    ${GB_MATH_TEST_DIR}/TestVectorIO.cpp
    ${GB_MATH_TEST_DIR}/TestVectorSwizzle.cpp
    ${GB_MATH_TEST_DIR}/TestMath.cpp
)

add_library(gbMath INTERFACE)
# apply build interface generator expression per element and not to the whole list, to avoid triggering CMP0076
list(TRANSFORM GB_MATH_HEADER_FILES REPLACE .+ $<BUILD_INTERFACE:\\0> OUTPUT_VARIABLE GB_MATH_BUILD_INTERFACE_HEADER_FILES)
target_sources(gbMath INTERFACE ${GB_MATH_BUILD_INTERFACE_HEADER_FILES})
target_include_directories(gbMath INTERFACE $<BUILD_INTERFACE:${GB_MATH_INCLUDE_DIR}>)
target_compile_features(gbMath INTERFACE cxx_std_17)
target_compile_options(gbMath INTERFACE $<BUILD_INTERFACE:$<$<CXX_COMPILER_ID:MSVC>:/W4>>)
target_compile_options(gbMath INTERFACE
    $<BUILD_INTERFACE:$<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>:-pedantic -Wall>>)

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
                GIT_TAG v2.1.2)
        elseif(WIN32)
            set(GB_FETCH_EXTERNAL_CATCH
                URL https://github.com/catchorg/Catch2/archive/v2.1.2.zip
                URL_HASH MD5=54d2785d7e5549907421e8db5c1b3817)
        else()
            set(GB_FETCH_EXTERNAL_CATCH
                URL https://github.com/catchorg/Catch2/archive/v2.1.2.tar.gz
                URL_HASH MD5=4c5740d7446d9b4e3735dcff0951aaca)
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

###############################################################################
## Doxygen gbBase
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
## Packaging gbBase
###############################################################################

set(GB_LIBRARY_NAMESPACE Ghulbus::)

install(TARGETS gbMath EXPORT gbMathTargets
    RUNTIME DESTINATION bin/$<CONFIG>
    LIBRARY DESTINATION lib/$<CONFIG>
    ARCHIVE DESTINATION lib/$<CONFIG>
    INCLUDES DESTINATION include
)
target_include_directories(gbMath INTERFACE $<INSTALL_INTERFACE:include>)
install(FILES ${GB_MATH_HEADER_FILES} ${GB_MATH_GENERATED_HEADER_FILES} DESTINATION include/gbMath)
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
