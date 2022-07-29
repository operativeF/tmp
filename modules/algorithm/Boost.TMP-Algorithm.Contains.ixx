//  Copyright 2018 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Contains;

import :Base.Comparison;
import :Base.Identity;
import :Base.Logic;
import :Detail.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename V, typename C = identity_>
	struct contains_ {};

	template <std::size_t N, typename V, typename C>
	struct dispatch<N, contains_<V, C>> : dispatch<N, or_<is_<V>, C>> {};
} // namespace boost::tmp
