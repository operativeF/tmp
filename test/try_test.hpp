//  Copyright 2018-2019 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/try.hpp>
#include "test_util.hpp"

namespace try_test {
	template <typename T>
	using call_type = typename T::type;

	struct has_type {
		using type = int;
	};
	int run() {
		nothing_{}   = call_<try_<call_type>, int>{}; // should SFINAE, int has no ::type
		list_<int>{} = list_<call_<try_<call_type>, has_type>>{}; // should not SFINAE
		list_<int>{} = call_<try_<call_type, listify_>, has_type>{}; // test the continuation

		return 0;
	}
} // namespace try_test
