cmake_minimum_required(VERSION 3.24)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" AND NOT MSVC)
    set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)
    add_compile_options("-fmodules -stdlib=libc++ -fbuiltin-module-map -fimplicit-module-maps -fprebuilt-module-path=${PREBUILT_MODULE_PATH}")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)
endif()

if(WIN32)
	# Enable usage of updated __cplusplus macro
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5050 /utf-8 /D __WIN64__ /D UNICODE /D _UNICODE /Zc:__cplusplus /EHsc /arch:AVX2 /experimental:module /sdl-")	
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(boost_tmp VERSION 1.1)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(modules)
add_subdirectory(tests)
