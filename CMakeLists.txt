cmake_minimum_required(VERSION 3.0)
project(boost_tmp)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
	# Disable unreferenced inline function removal warning
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4514")
	# Enable usage of updated __cplusplus macro
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")	
endif()

if(MSVC)
	set(COMP_OPTIONS /Wall)
else() # clang / GCC
	set(COMP_OPTIONS -ftemplate-depth=2048 -Wall)
endif()

option(MAKE_INCLUDE_TESTS OFF)

# Add Standardese target
find_program(STANDARDESE standardese HINTS ${STANDARDESE_ROOT})

if (STANDARDESE)
	set(BOOST_TMP_DOCS_DIR ${CMAKE_BINARY_DIR}/doc/standardese)
	message(STATUS "Found standardese for documentation generation")
	message(STATUS "Documentation dir is: ${BOOST_TMP_DOCS_DIR}")
	file(MAKE_DIRECTORY ${BOOST_TMP_DOCS_DIR})
	add_custom_target(
			standardese
			COMMAND ${STANDARDESE}
			-I${CMAKE_SOURCE_DIR}/include/boost/tmp
			--input.blacklist_namespace=detail
			--compilation.comments_in_macro=false
			--output.require_comment_for_full_synopsis=false
			--output.format=html
			${CMAKE_SOURCE_DIR}/include/boost/tmp
			WORKING_DIRECTORY ${BOOST_TMP_DOCS_DIR}
	)
endif (STANDARDESE)

add_subdirectory(modules)
