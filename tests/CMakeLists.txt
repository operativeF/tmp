
add_executable(tmp_test)

target_sources(tmp_test
    PRIVATE
        test.cpp

    PRIVATE
        FILE_SET boost_tmp_test_modules TYPE CXX_MODULES FILES
        all_of_test.ixx
        any_of_test.ixx
        clamp_test.ixx
        contains_test.ixx
        count_if_test.ixx
        drop_test.ixx
        each_test.ixx
        erase_test.ixx
        extrema_test.ixx
        filter_test.ixx
        find_if_test.ixx
        flatten_test.ixx
        fold_left_test.ixx
        fold_right_test.ixx
        index_test.ixx
        insert_test.ixx
        join_test.ixx
        logic_test.ixx
        none_of_test.ixx
        partition_test.ixx
        pop_front_test.ixx
        product_test.ixx
        push_back_test.ixx
        push_front_test.ixx
        range_math_test.ixx
        remove_if_test.ixx
        repeat_sequence_test.ixx
        replace_if_test.ixx
        reverse_test.ixx
        rotate_test.ixx
        set_test.ixx
        size_test.ixx
        sort_test.ixx
        swap_test.ixx
        take_test.ixx
        tee_test.ixx
        transform_test.ixx
        
        tmp_all_tests.ixx
)

if(MSVC)
    target_compile_options(tmp_test PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()

target_link_libraries(tmp_test
    PRIVATE
        boost_tmp
)
