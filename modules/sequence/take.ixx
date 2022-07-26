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

export module Boost.TMP.Sequence.Take;

import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Sequence.Drop;
import Boost.TMP.Sequence.Rotate;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename N = sizet_<0>, typename C = listify_>
	struct take_ {};

	namespace detail {
		template <std::size_t N, typename P, typename C>
		struct dispatch<N, take_<P, C>> {
			template <typename... Ts>
			using f = typename dispatch<
				    find_dispatch(sizeof...(Ts)),
				    rotate_<P, drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>>::template f<Ts...>;
		};
	} // namespace detail
} // namespace boost::tmp