//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP:Algorithm.AllOf;

import :Base.Identity;
import :Base.Logic;
import :Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename F, typename C = identity_>
	struct all_of_ {};
		
	template <std::size_t N, typename F, typename C>
	struct dispatch<N, all_of_<F, C>>
		: dispatch<N, and_<F, C>> {};
} // namespace boost::tmp
