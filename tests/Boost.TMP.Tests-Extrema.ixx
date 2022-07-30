//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Extrema;

import Boost.TMP;

namespace extrema_test {
    using namespace boost::tmp;

    using alist = list_<int_<6>, int_<5>, int_<11>>;
    using blist = list_<int_<11>, int_<6>, int_<5>>;
    using clist = list_<int_<5>, int_<11>, int_<6>, int_<1>>;
    using dlist = list_<int_<-5>, int_<70>, int_<61>, int_<1>>;

    export int run() {
        int_<5>{}  = call_<unpack_<min_element_<>>, alist>{};
        int_<5>{}  = call_<unpack_<min_element_<>>, blist>{};
        int_<11>{} = call_<unpack_<max_element_<>>, clist>{};
        int_<11>{} = call_<unpack_<max_element_<>>, alist>{};
        int_<70>{} = call_<unpack_<max_element_<>>, dlist>{};

        return 0;
    }
} // namespace extrema_test
