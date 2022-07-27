//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Algorithm.Transform;

import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename F = identity_, typename C = listify_>
	struct transform_ {};
	
	template <std::size_t N, typename F, typename C>
	struct dispatch<N, transform_<F, C>> {
		template <typename... Ts>
		using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<
				typename dispatch<1, F>::template f<Ts>...>;
	};

	template <std::size_t N, template <typename...> class F, typename FC, typename C>
	struct dispatch<N, transform_<lift_<F, FC>, C>> {
		template <typename... Ts>
		using f = typename dispatch<(N + (N > sizeof...(Ts))), C>::template f<F<Ts>...>;
	};
} // namespace boost::tmp
