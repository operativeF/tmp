
add_library(boost_tmp_tests STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Boost.TMP-Tests.cpp)

target_link_libraries(boost_tmp_tests PRIVATE boost_tmp)

if(MSVC)
    target_compile_options(boost_tmp_tests PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()
