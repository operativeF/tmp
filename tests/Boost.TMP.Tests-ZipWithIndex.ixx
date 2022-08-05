//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:ZipWithIndex;

import Boost.TMP;

namespace zip_with_index_test {
    using namespace boost::tmp;

    export int run() {
        list_<list_<sizet_<0>, char_<'a'>>, list_<sizet_<1>, char_<'b'>>, list_<sizet_<2>, char_<'c'>>>{}
            = call_<zip_with_index_<>, char_<'a'>, char_<'b'>, char_<'c'>>{};
        return 0;
    }
} // namespace zip_with_index_test
