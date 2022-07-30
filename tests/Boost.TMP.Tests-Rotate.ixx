//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Rotate;

import Boost.TMP;

namespace rotate_test {
    using namespace boost::tmp;

    export int run() {
        list_<int_<1>, int_<2>, int_<3>>{} = call_<rotate_<int_<0>>, int_<1>, int_<2>, int_<3>>{};
        list_<int_<2>, int_<3>, int_<1>>{} = call_<rotate_<int_<1>>, int_<1>, int_<2>, int_<3>>{};
        // TODO: Allow rotations in opposite direction.
        // list_<int_<3>, int_<1>, int_<2>>{} = call_<rotate_<int_<-1>>, int_<1>, int_<2>, int_<3>>{};

        return 0;
    }
} // namespace rotate_test
