//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Zip;

import Boost.TMP;
import :Helpers;

namespace zip_test {
    using namespace boost::tmp;

    export int run() {
        list_<uint_<3>, uint_<7>>{} =
            call_<zip_<lift_<add>>, list_<int_<1>, int_<3>>, list_<int_<2>, int_<4>>>{};
        list_<list_<int_<1>, int_<2>>, list_<int_<3>, int_<4>>>{} =
            call_<zip_<listify_>, list_<int_<1>, int_<3>>, list_<int_<2>, int_<4>>>{};
        return 0;
    }
} // namespace zip_with_index_test
