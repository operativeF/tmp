//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:NoneOf;

import Boost.TMP;

namespace none_of_test {
    using namespace boost::tmp;

    template <typename T>
    using is_even = bool_<(T::value % 2 == 0)>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;
    using blist = list_<uint_<1>, uint_<3>>;

    export int run() {
        bool_<false>{} = call_<unpack_<none_of_<lift_<is_even>>>, alist>{};
        bool_<true>{} = call_<unpack_<none_of_<lift_<is_even>>>, blist>{};
        return 0;
    }
} // namespace none_of_test
