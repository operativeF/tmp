//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:PushFront;

import Boost.TMP;

namespace push_front_test {
    using namespace boost::tmp;

    export int run() {
        list_<int_<4>, int_<1>, int_<2>>{} = call_<push_front_<int_<4>>, int_<1>, int_<2>>{};
        list_<int_<1>>{} = call_<push_front_<int_<1>>>{};
        return 0;
    }
} // namespace push_front_test
