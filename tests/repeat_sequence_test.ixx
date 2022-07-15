//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.RepeatSequence;

import Boost.TMP;

import std.core;

using namespace boost::tmp;

export namespace repeat_sequence_test {

    template<typename... Vs>
    using into_sequence = std::index_sequence<Vs::value...>;
    using repeat_1_10x = call_<repeat_sequence_<sizet_<69>, lift_<into_sequence>>, sizet_<1>>;
	int run() {
        // repeat_1_10x::nil{};
		return 0;
	}
} // namespace repeat_sequence_test
