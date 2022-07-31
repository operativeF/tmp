//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Take;

import Boost.TMP;

namespace take_test {
    using namespace boost::tmp;

    export int run() {
        list_<int_<1>>{}          = call_<take_<uint_<1>>, int_<1>, int_<2>, int_<3>>{};
        list_<int_<1>, int_<2>>{} = call_<take_<uint_<2>>, int_<1>, int_<2>, int_<3>>{};

        // UNDER CONSIDERATION: Taking more than the list results in compilation failure.
        // UNDER CONSIDERATION: Taking from an empty input results in compilation failure.
        // list_<>{} = call_<take_<uint_<4>>>{};
        return 0;
    }
} // namespace take_test