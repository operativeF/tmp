//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:MakeSequence;

import Boost.TMP;

namespace make_sequence_test {
    using namespace boost::tmp;

    template<typename T>
    using and_one = sizet_<T::value + 1>;

    template<typename T>
    struct always_one {
        template<typename N>
        using f = sizet_<T::value>;
    };

    template<typename T>
    using div_3 = sizet_<T::value / 3>;

    template<typename Denom>
    struct div_n {
        template<typename Numer>
        using f = sizet_<Numer::value / Denom::value>;
    };

    template<typename IndexTo>
    using repeating_index_seq = call_<make_sequence_<lift_<div_n<IndexTo>::template f>>, sizet_<(IndexTo::value * IndexTo::value)>>;

    export int run() {
        list_<sizet_<0>, sizet_<1>, sizet_<2>>{} = call_<make_sequence_<>, sizet_<3>>{};
        list_<sizet_<1>, sizet_<2>, sizet_<3>>{} = call_<make_sequence_<lift_<and_one>>, sizet_<3>>{};
        list_<sizet_<1>, sizet_<1>, sizet_<1>>{} = call_<make_sequence_<lift_<always_one<sizet_<1>>::template f>>, sizet_<3>>{};
        list_<sizet_<0>, sizet_<0>, sizet_<0>, sizet_<1>, sizet_<1>, sizet_<1>>{} = call_<make_sequence_<lift_<div_3>>, sizet_<6>>{};

        list_<sizet_<0>, sizet_<0>, sizet_<0>, sizet_<1>, sizet_<1>, sizet_<1>, sizet_<2>, sizet_<2>, sizet_<2>>{} =
            call_<lift_<repeating_index_seq>, sizet_<3>>{};

        return 0;
    }
} // namespace make_sequence_test
