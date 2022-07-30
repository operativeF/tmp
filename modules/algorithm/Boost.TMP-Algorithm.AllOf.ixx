//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.AllOf;

import :Base.Identity;
import :Base.Logic;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename F, typename C = identity_>
	struct all_of_ {};
		
	template <std::size_t N, typename F, typename C>
	struct dispatch<N, all_of_<F, C>> : dispatch<N, and_<F, C>> {};
} // namespace boost::tmp
