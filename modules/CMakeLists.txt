#  Copyright 2021 Thomas Figueroa.
#  Distributed under the Boost Software License, Version 1.0.
#
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

if(ENABLE_CPP_MODULE)
  add_library(boost_tmp STATIC)
  target_include_directories(boost_tmp PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_sources(boost_tmp
      PUBLIC
          FILE_SET boost_tmp_modules TYPE CXX_MODULES FILES
          ${CMAKE_CURRENT_SOURCE_DIR}/Boost.TMP.ixx
  )
  target_compile_definitions(boost_tmp
    PRIVATE
      ENABLE_CPP_MODULE
      BOOST_TMP_EXPORT=export
  )
else()
  add_library(boost_tmp INTERFACE)
  target_include_directories(boost_tmp INTERFACE ${CMAKE_SOURCE_DIR}/include)
endif()
