//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Index;

import Boost.TMP;

namespace index_test {
    using namespace boost::tmp;

    export int run() {
        // Get index 2 of VPP
        int_<3>{} = call_<index_<uint_<2>>, int_<1>, char_<'c'>, int_<3>, int_<4>>{};

        // Unpack simple_list, then take index 0
        int_<1>{} = call_<ui0_<>, list_<int_<1>, int_<2>, int_<3>>>{};
        
        // Get first element of pack
        int_<1>{} = call_<front_<>, int_<1>, int_<2>, int_<3>>{};
        return 0;
    }
} // namespace index_test
