
add_library(boost_tmp_tests
    STATIC
        ${CMAKE_CURRENT_LIST_DIR}/Boost.TMP-Tests.cpp
)

if(ENABLE_CPP_MODULE)
    target_compile_definitions(boost_tmp_tests
        PRIVATE
            ENABLE_CPP_MODULE
    )
endif()

add_dependencies(boost_tmp_tests boost_tmp)
target_link_libraries(boost_tmp_tests PRIVATE boost_tmp)
