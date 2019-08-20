//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>
#include <boost/tmp.hpp>
#include <boost/tmp_units/composite.hpp>
#include <boost/tmp_units/units/length.hpp>
#include <boost/tmp_units/units/area.hpp>
#include "test_util.hpp"

namespace all_of_test {
	using namespace boost::tmp::units;

    template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;

	constexpr auto nill = 10.0_m + 20.0_m;

	// Assignment operator must be overloaded.
	// All operators must be overloaded. 
	// Must prohibit implicit conversions like below.
	constexpr auto aill = 1.0_m * 1.0_m;

	constexpr auto nillo = convertTo<millimeter_ld>()(10.04_m);

	int run() {
		static_assert(aill == 1000.0_mm2, "true");

		static_assert(nill == 0.030_km, "true");
		static_assert(nill == 30000.0_mm, "true");		

        bool_<true>{} = call_<unpack_<all_of_<lift_<is_even>>>, alist>{};
		return 0;
	}
} // namespace all_of_test