#  Copyright 2021 Thomas Figueroa.
#  Distributed under the Boost Software License, Version 1.0.
#
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt


set(TMP_ALGO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/algorithm)
set(TMP_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)

set(TMP_ALGO_IXX
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.ixx
)

set(TMP_MAIN_IXX
    # ${TMP_BASE_DIR}/Boost.TMP-Base.ListOperations.ixx
    # ${TMP_BASE_DIR}/Boost.TMP-Base.Map.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Types.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Try.ixx
)

set(TMP_BASE_IXX
    ${CMAKE_CURRENT_SOURCE_DIR}/Boost.TMP.ixx
)

add_library(boost_tmp STATIC)

target_sources(boost_tmp
    PUBLIC
        FILE_SET boost_tmp_modules TYPE CXX_MODULES FILES
        ${TMP_ALGO_IXX}
        ${TMP_MAIN_IXX}
        ${TMP_BASE_IXX}
)

if(MSVC)
    target_compile_options(boost_tmp PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()
