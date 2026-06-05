cmake_minimum_required(VERSION 3.20)

# CppKaiLanguage - the KAI surface languages.
#
#   - Pi  (postfix / RPN language)
#   - Rho (infix language, built on top of Pi)
#
# Downstream of CppKaiCore (Core + Executor + CommonLang). Extracted from CppKAI
# for reuse on other platforms (including Android). Builds standalone or via
# add_subdirectory from a parent project.

if(NOT DEFINED PROJECT_NAME)
    project(CppKaiLanguage CXX)
endif()

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CPPKAILANG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CPPKAILANG_INCLUDE ${CPPKAILANG_ROOT}/Include)

# Pi/Rho depend on the CppKaiCore module (Core, CommonLang, Executor). When
# built as part of CppKAI those targets already exist. For a standalone build,
# set KAI_CORE_DIR to a CppKaiCore checkout (and KAI_MONOTONIC_INCLUDE_DIR for
# CppKaiCore's own boost.monotonic dependency).
if(NOT TARGET Core)
    if(NOT KAI_CORE_DIR)
        message(FATAL_ERROR
            "CppKaiLanguage requires CppKaiCore. Set -DKAI_CORE_DIR=/path/to/CppKaiCore")
    endif()
    add_subdirectory(${KAI_CORE_DIR} ${CMAKE_BINARY_DIR}/CppKaiCore)
endif()

# --- PiLang -----------------------------------------------------------------
file(GLOB_RECURSE cppkailang_pi_src
    ${CPPKAILANG_ROOT}/Source/Library/Language/Pi/Source/*.cpp)
add_library(PiLang ${cppkailang_pi_src})
target_include_directories(PiLang PUBLIC
    ${CPPKAILANG_INCLUDE}
    ${CPPKAILANG_INCLUDE}/KAI/Language/Pi)
target_link_libraries(PiLang PUBLIC CommonLang Executor Core)

# --- RhoLang ----------------------------------------------------------------
file(GLOB_RECURSE cppkailang_rho_src
    ${CPPKAILANG_ROOT}/Source/Library/Language/Rho/Source/*.cpp)
add_library(RhoLang ${cppkailang_rho_src})
target_include_directories(RhoLang PUBLIC
    ${CPPKAILANG_INCLUDE}
    ${CPPKAILANG_INCLUDE}/KAI/Language/Rho)
target_link_libraries(RhoLang PUBLIC PiLang CommonLang Executor Core)

# Honour a parent-provided output directory (CppKAI's BIN_HOME).
if(DEFINED BIN_HOME)
    set_target_properties(PiLang RhoLang PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${BIN_HOME}"
        LIBRARY_OUTPUT_DIRECTORY "${BIN_HOME}")
endif()
