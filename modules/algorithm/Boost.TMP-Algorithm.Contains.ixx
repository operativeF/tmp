//  Copyright 2018 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP:Algorithm.Contains;

import :Base.Identity;
import :Base.Logic;
import :Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename V, typename C = identity_>
	struct contains_ {};

	template <std::size_t N, typename V, typename C>
	struct dispatch<N, contains_<V, C>> : dispatch<N, or_<is_<V>, C>> {};
} // namespace boost::tmp
