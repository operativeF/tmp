//  Copyright 2018-2019 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Algorithm.Clamp;

import Boost.TMP.Algorithm.Filter;

import Boost.TMP.Base.Comparison;
import Boost.TMP.Base.Identity;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Sequence.Tee;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename L, typename H, typename C = identity_>
	struct clamp_ {};

	template <std::size_t N, typename L, typename H, typename C>
	struct dispatch<N, clamp_<L, H, C>>
		: dispatch<N, tee_<filter_<less_<L>, filter_<greater_<H>>>, C>> {};
} // namespace boost::tmp
