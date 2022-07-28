//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Reverse;

import Boost.TMP;

using namespace boost::tmp;

using rhs = make_sequence_<identity_, reverse_<reverse_<>>>;
using lhs = make_sequence_<>;
using alist = list_<sizet_<0>, sizet_<1>, sizet_<2>, sizet_<3>, sizet_<4>>;

export namespace reverse_test {
	int run() {
		list_<sizet_<0>>{} = call_<make_sequence_<identity_, reverse_<>>, sizet_<1>>{};

		list_<sizet_<1>, sizet_<0>>{} = call_<make_sequence_<identity_, reverse_<>>, sizet_<2>>{};

		list_<sizet_<2>, sizet_<1>, sizet_<0>>{} =
		        call_<make_sequence_<identity_, reverse_<>>, sizet_<3>>{};

		list_<sizet_<3>, sizet_<2>, sizet_<1>, sizet_<0>>{} =
		        call_<make_sequence_<identity_, reverse_<>>, sizet_<4>>{};

		list_<sizet_<4>, sizet_<3>, sizet_<2>, sizet_<1>, sizet_<0>>{} =
		        call_<make_sequence_<identity_, reverse_<>>, sizet_<5>>{};

		list_<sizet_<4>, sizet_<3>, sizet_<2>, sizet_<1>, sizet_<0>>{} =
		        call_<unpack_<reverse_<>>, alist>{};

		return 0;
	}
} // namespace reverse_test
