cmake_minimum_required(VERSION 3.28)

project(boost_tmp VERSION 1.1)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 23)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_BENCHMARKING "Enable benchmarking" OFF)
option(ENABLE_CPP_MODULE "Enable C++ module of Boost.TMP" ON)
option(ENABLE_COMPILE_TIME_TESTING "Enable compile-time testing using concepts." OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	# Enable usage of updated __cplusplus macro
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5050 /utf-8 /GR- /D __WIN64__ /D UNICODE /D _UNICODE /Zc:__cplusplus /EHsc")	
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif() # MSVC

add_subdirectory(modules)

if(ENABLE_BENCHMARKING)
  add_subdirectory(benchmark)
endif()

if(ENABLE_COMPILE_TIME_TESTING)
  add_subdirectory(tests)
endif()
