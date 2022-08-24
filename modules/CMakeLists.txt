#  Copyright 2021 Thomas Figueroa.
#  Distributed under the Boost Software License, Version 1.0.
#
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_library(boost_tmp STATIC)

target_sources(boost_tmp
    PUBLIC
        FILE_SET boost_tmp_modules TYPE CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Boost.TMP.ixx
)

if(ENABLE_COMPILE_TIME_TESTING)
  target_compile_definitions(boost_tmp PRIVATE TMP_COMPILE_TIME_TESTING)
endif()

if(MSVC)
    target_compile_options(boost_tmp PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()
