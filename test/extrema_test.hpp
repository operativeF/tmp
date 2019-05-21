//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace extrema_test {
    using alist = list_<uint_<6>, uint_<5>, uint_<11>>;
	template <typename T, typename U>
	using add = uint_<(T::value + U::value)>;

	template <typename T, typename U>
	using lesser_v = uint_<(T::value < U::value) ? T::value : U::value>;

	template <typename T, typename U>
	using greater_v = uint_<(U::value < T::value) ? U::value : T::value>;

	int run() {
    uint_<5>{} = call_<unpack_<extrema_<lift_<lesser_v>>>, alist>{};

		return 0;
	}
} // namespace extrema_test
