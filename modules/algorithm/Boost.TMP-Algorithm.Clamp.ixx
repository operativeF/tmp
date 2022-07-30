//  Copyright 2018-2019 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Clamp;

import :Algorithm.Filter;
import :Base.Identity;
import :Base.Dispatch;
import :Sequence.Tee;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename L, typename H, typename C = identity_>
	struct clamp_ {};

	template <std::size_t N, typename L, typename H, typename C>
	struct dispatch<N, clamp_<L, H, C>>
		: dispatch<N, tee_<filter_<less_<L>, filter_<greater_<H>>>, C>> {};
} // namespace boost::tmp
