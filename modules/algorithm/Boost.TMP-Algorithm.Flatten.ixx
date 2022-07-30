//  Copyright 2019-2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Flatten;

import :Base.List;
import :Base.Dispatch;
import :Sequence.Join;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename C = listify_>
	struct flatten_ {};

	template <typename C, typename... Ts>
	struct flatten_impl {
		using type = dispatch<0, join_<C>>::template f<Ts...>;
	};

	// Append to list function
	template <typename C, typename... T1s, typename X, typename... T2s>
	struct flatten_impl<C, list_<T1s...>, X, T2s...>
		: flatten_impl<C, list_<T1s..., X>, T2s...> {};

	// Remove from list function
	template <typename C, typename... T1s, template <typename...> class X, typename... T2s,
				typename... T3s>
	struct flatten_impl<C, list_<T1s...>, X<T2s...>, T3s...>
		: flatten_impl<C, list_<T1s...>, T2s..., T3s...> {};

	template <std::size_t N, typename C>
	struct dispatch<N, flatten_<C>> {
		template <typename... Ts>
		using f = flatten_impl<C, list_<>, Ts...>::type;
	};
} // namespace boost::tmp
