//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <utility>
#endif // __GNUC__

export module Test.RepeatSequence;

import Boost.TMP;

#if _MSC_VER
import std;
#endif // _MSC_VER

using namespace boost::tmp;

using repeat_1_10x = call_<repeat_sequence_<sizet_<69>, lift_<into_sequence>>, sizet_<1>>;

export namespace repeat_sequence_test {
	int run() {
		return 0;
	}
} // namespace repeat_sequence_test
