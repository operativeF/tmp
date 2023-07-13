cmake_minimum_required(VERSION 3.27)

project(boost_tmp VERSION 1.1)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_BENCHMARKING "Enable benchmarking" OFF)
option(ENABLE_CPP_MODULE "Enable C++ module of Boost.TMP" OFF)
option(ENABLE_COMPILE_TIME_TESTING "Enable compile-time testing using concepts." ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	# Enable usage of updated __cplusplus macro
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5050 /utf-8 /GR- /D __WIN64__ /D UNICODE /D _UNICODE /Zc:__cplusplus /EHsc")	
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  if(ENABLE_CPP_MODULE)
    string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
      "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -E -x c++ <SOURCE>"
      " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
      " -fmodules-ts -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT> -fdep-format=trtbd"
      " -o <PREPROCESSED_SOURCE>")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG "-fmodules-ts -fmodule-mapper=<MODULE_MAP_FILE> -fdep-format=trtbd -x c++")
  endif()
else()
  if(ENABLE_CPP_MODULE)
    string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
    "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -E -x c++ <SOURCE>"
    " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
    " -fmodules-ts -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT> -fdep-format=trtbd"
    " -o <PREPROCESSED_SOURCE>")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "clang")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG "-fmodules-ts -fmodule-mapper=<MODULE_MAP_FILE> -fdep-format=trtbd -x c++")
  endif()
endif()

add_subdirectory(modules)

if(ENABLE_BENCHMARKING)
  add_subdirectory(benchmark)
endif()

if(ENABLE_COMPILE_TIME_TESTING)
  add_subdirectory(tests)
endif()
