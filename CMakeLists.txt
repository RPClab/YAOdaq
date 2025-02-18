#########################################################
#  ██╗   ██╗ █████╗  ██████╗ ██████╗  █████╗  ██████╗   #
#  ╚██╗ ██╔╝██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔═══██╗  #
#   ╚████╔╝ ███████║██║   ██║██║  ██║███████║██║   ██║  #
#    ╚██╔╝  ██╔══██║██║   ██║██║  ██║██╔══██║██║▄▄ ██║  #
#     ██║   ██║  ██║╚██████╔╝██████╔╝██║  ██║╚██████╔╝  #
#     ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝ ╚══▀▀═╝   #
#########################################################
cmake_minimum_required(VERSION 3.16...3.20.2 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/external" "${CMAKE_CURRENT_SOURCE_DIR}")

# Load Setting to be able to change the options etc.
include(Settings)

include(GetCMakeMM)
cmmm(VERSION "2.0" REPOSITORY "flagarde/CMakeMM" PROVIDER "gitlab" VERBOSITY VERBOSE)

project(YAODAQ VERSION "0.0.1.0" DESCRIPTION "YAODAQ for RPClab" HOMEPAGE_URL "https://github.com/RPClab/YAODAQ" LANGUAGES CXX)

cmmm_modules_list(REPOSITORY "flagarde/CMakeCM" PROVIDER "gitlab" DESTINATION "Modules" BRANCH "main")

include(PreventInSourceBuilds)
prevent_in_source_builds()

include(DefaultInstallPrefix)
default_install_prefix("${CMAKE_SOURCE_DIR}/bin")

include(Standards)
cxx_17()
c_11()

include(GNUInstallDirs)

option(ENABLE_TESTS "Build the tests" TRUE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#include(DefaultConfigurations)
#include(ConfigurationCheck)

#set_default_configuration("Debug")

#include(Formatters)



# Ask CMake to output a compile_commands.json file for use with things like Vim YCM.
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(CMAKE_LINK_DEPENDS_NO_SHARED TRUE)


set(CMAKE_MACOSX_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
link_directories("${CMAKE_INSTALL_FULL_LIBDIR}")

# If we want to have test in the executables
if(ENABLE_DOCTESTS)
  add_dependencies(YAODAQ::doctest)
  add_definitions(-DENABLE_DOCTEST_IN_LIBRARY)
endif()

include(ProcessorCount)
processorcount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
endif()

include(Architectures)

set(CMAKE_MESSAGE_CONTEXT_SHOW TRUE)


if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

#include(PositionIndependentExecutable)

# Optional IPO. Do not use IPO if it's not supported by compiler.
#include(CheckIPOSupported)
#check_ipo_supported(RESULT aResult OUTPUT aOutput)
#if(aResult)
#  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
#else()
#  message(WARNING "IPO is not supported:# ${aOutput}")
#endif()

include(Sanitizers)

#include(DependencyGraph)
#gen_dep_graph(OUTPUT_DIR ${CMAKE_INSTALL_PREFIX} TARGET_NAME dependency-graph OUTPUT_TYPE pdf)

#include(Tools)
#clang_tidy(-format-style=file -checks=* -header-filter='${CMAKE_SOURCE_DIR}/*')
#cppcheck(--enable=warning,performance,portability,missingInclude --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)" --suppress=missingIncludeSystem --quiet --verbose --force)
#include_what_you_use(-Xiwyu)

if(ENABLE_TESTS)
  include(Doctest)
  add_subdirectory(tests)
endif()

add_subdirectory(src)

if(ENABLE_EXTRAS)
  add_subdirectory(extras)
endif()

add_subdirectory(apps)

if(ENABLE_DOCS)
  add_subdirectory(docs)
endif()

