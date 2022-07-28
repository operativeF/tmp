//  Copyright 2019-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP:Algorithm.RemovePairs;

import :Base.Call;
import :Base.Comparison;
import :Base.Identity;
import :Base.If;
import :Base.Logic;
import :Base.Vocabulary;
import :Detail.Dispatch;
import :Sequence.Join;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	// Requires sets to be the input, unless 
	export template<typename C = listify_>
	struct remove_pairs_ {};

	template <typename C, typename... Ts>
	struct remove_pairs_impl {
		using type = typename dispatch<0, join_<C>>::template f<Ts...>;
	};

	// template <typename C, typename T1, typename T, typename T2>
	// struct remove_pairs_impl<C, list_<T1, T, T, T2>>
	//     : remove_pairs_impl<C, list_<T1, T2>> {};

	// Append to list function
	// template <typename C, typename... T1s, typename T, typename... T2s>
	// struct remove_pairs_impl<C, list_<T1s..., T, T, T2s...>>
	//     : remove_pairs_impl<C, list_<T1s..., T2s...>> {};

	template <typename C, typename T, typename... T2s>
	struct remove_pairs_impl<C, list_<T, T, T2s...>>
		: remove_pairs_impl<C, list_<T2s...>> {};

	template <std::size_t N, typename C>
	struct dispatch<N, remove_pairs_<C>> {
		template <typename... Ts>
		using f = typename remove_pairs_impl<C, list_<Ts...>>::type;
	};
} // namespace boost::tmp