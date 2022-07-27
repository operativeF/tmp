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

export module Boost.TMP.Sequence.PopFront;

import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename C = listify_>
	struct pop_front_ {};
	
	template <std::size_t N, typename C>
	struct dispatch<N, pop_front_<C>> {
		template <typename T, typename... Ts>
		using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
	};
	template <typename C>
	struct dispatch<0, pop_front_<C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<nothing_>;
	};
} // namespace boost::tmp
