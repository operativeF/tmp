
add_library(boost_tmp_tests
    STATIC
        ${CMAKE_CURRENT_LIST_DIR}/Boost.TMP-Tests.cpp
)

add_dependencies(boost_tmp_tests boost_tmp)
target_link_libraries(boost_tmp_tests PRIVATE boost_tmp)
