//  Copyright 2018-2019 Odin Holmes.
//            2022      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

import Boost.TMP.Tests;

int main() {
    return any_of_test::run() ||
           all_of_test::run() ||
           clamp_test::run()  ||
           contains_test::run() ||
           count_if_test::run() ||
           drop_test::run() ||
           each_test::run() ||
           erase_test::run() ||
        //    extrema_test::run() ||
           filter_test::run() ||
           find_if_test::run() ||
         //   flatten_test::run() ||
           fold_left_test::run() ||
           fold_right_test::run() ||
           index_test::run() ||
           insert_test::run() ||
           join_test::run() ||
           logic_test::run() ||
           none_of_test::run() ||
           partition_test::run() ||
           pop_front_test::run() ||
        //    product_test::run() ||
           push_back_test::run() ||
           push_front_test::run() ||
        //    range_math_test::run() ||
           remove_if_test::run() ||
           repeat_sequence_test::run() ||
           replace_if_test::run() ||
           reverse_test::run() ||
           rotate_test::run() ||
        //    set_test::run() ||
           size_test::run()   ||
           sort_test::run()   ||
           swap_test::run()   ||
           take_test::run()   ||
           tee_test::run()    ||
           transform_test::run();
}

