//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

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
        list_<map_element_<char_<'a'>, sizet_<0>, sizet_<0>>, map_element_<char_<'b'>, sizet_<1>, sizet_<1>>>{} =
            call_<map_<lift_<less_than>>, char_<'a'>, char_<'b'>>{};

        // Map by type size; greatest size to least
        list_<map_element_<three_ints<1, 3, 5>, sizet_<1>, sizet_<0>>, map_element_<two_ints<1, 2>, sizet_<2>, sizet_<1>>, map_element_<int_<1>, sizet_<0>, sizet_<2>>>{} =
            call_<map_<lift_<greater_than_t>>, int_<1>, three_ints<1, 3, 5>, two_ints<1, 2>>{};

        return 0;
    }

} // namespace map_test