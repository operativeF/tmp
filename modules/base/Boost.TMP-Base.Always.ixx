//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Always;

import :Base.Identity;
import :Detail.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename T, typename C = identity_>
	struct always_ {};

	template <std::size_t N, typename T, typename C>
	struct dispatch<N, always_<T, C>> {
		template <typename...>
		using f = dispatch<1, C>::template f<T>;
	};
} // namespace boost::tmp
