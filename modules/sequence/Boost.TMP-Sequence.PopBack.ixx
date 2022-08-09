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

export module Boost.TMP:Sequence.PopBack;


import :Base.Dispatch;
import :Base.List;
import :Base.Nothing;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename C = listify_>
    struct pop_back_ {};

	template <std::size_t N, typename C>
	struct dispatch<N, pop_back_<C>> {
		template <typename T, typename... Ts>
		using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
	};

	template <typename C>
	struct dispatch<0, pop_back_<C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<nothing_>;
	};
} // namespace boost::tmp

// TESTING:
namespace pop_back_test {

} // namespace pop_back_test
