//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Contains;

import Boost.TMP;

namespace contains_test {
    using namespace boost::tmp;

    export int run() {
        false_{} = call_<contains_<int_<0>>, int_<1>>{};
        true_{}  = call_<contains_<int_<2>>, int_<0>, int_<1>, int_<2>>{};
        return 0;
    }
} // namespace contains_test
