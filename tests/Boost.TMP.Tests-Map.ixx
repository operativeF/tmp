//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <type_traits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP.Tests:Map;

import Boost.TMP;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace map_test {
    using namespace boost::tmp;

    template<typename T, typename U>
    using less_than = bool_<(T::value::value < U::value::value)>;

    template<typename T, typename U>
    using greater_than_t = bool_<std::alignment_of_v<typename U::value> < std::alignment_of_v<typename T::value>>;

    template<int V1, int V2>
    struct two_ints {
        int a{V1};
        int b{V2};
    };

    template<int V1, int V2, int V3>
    struct three_ints {
        int a{V1};
        int b{V2};
        int c{V3};
    };

    export int run() {
        // Map by element value
        using ab_map = call_<map_<lift_<less_than>>, char_<'a'>, char_<'b'>>;
        MapType<map_element_<char_<'a'>, sizet_<0>, sizet_<0>>, map_element_<char_<'b'>, sizet_<1>, sizet_<1>>>{} =
            ab_map{};
        
        char_<'a'>{} = ab_map::get_type_from_input_pos<sizet_<0>>{};

        // Map by type size; greatest size to least
        using adv_map = call_<map_<lift_<greater_than_t>>, int_<1>, three_ints<1, 3, 5>, two_ints<1, 2>>;
        MapType<map_element_<three_ints<1, 3, 5>, sizet_<1>, sizet_<0>>, map_element_<two_ints<1, 2>, sizet_<2>, sizet_<1>>, map_element_<int_<1>, sizet_<0>, sizet_<2>>>{} = adv_map{};

        two_ints<1, 2>{} = adv_map::get_type_from_input_pos<sizet_<2>>{};
        sizet_<1>{}      = adv_map::get_memory_pos<sizet_<2>>{};

        return 0;
    }

} // namespace map_test