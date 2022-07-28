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

export module Boost.TMP:Sequence.PushFront;

import :Base.Vocabulary;
import :Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename T, typename C = listify_>
	struct push_front_ {};
	
	template <std::size_t N, typename T, typename C>
	struct dispatch<N, push_front_<T, C>> {
		template <typename... Ts>
		using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<T,
																						Ts...>;
	};
} // namespace boost::tmp
