//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Sequence.Erase;

import :Base.Integral;
import :Base.List;
import :Base.Dispatch;
import :Sequence.Drop;
import :Sequence.PopFront;
import :Sequence.Rotate;

#if _MSC_VER
import std;
#endif

// Given a VPP, remove the nth value in the pack.
// Reduces the size of the list by 1.
namespace boost::tmp {
	export template <typename N = sizet_<0>, typename C = listify_>
	struct erase_ {};

	template <std::size_t N, typename I, typename C>
	struct dispatch<N, erase_<I, C>> {
		template <typename... Ts>
		using f = dispatch<N,
				   rotate_<I,
				   	pop_front_<
					 rotate_<sizet_<(sizeof...(Ts) - I::value - 1)>, C>>>>::template f<Ts...>;
	};
	template <typename I, typename C>
	struct dispatch<0, erase_<I, C>> {
		template <typename... Ts>
		using f = dispatch<1, C>::template f<nothing_>;
	};
} // namespace boost::tmp
