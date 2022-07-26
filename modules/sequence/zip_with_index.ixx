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

export module Boost.TMP.Sequence.ZipWithIndex;

import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Sequence.MakeSequence;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename F = listify_, typename C = listify_>
	struct zip_with_index_ {};

	namespace detail {
		template <typename L>
		struct indexer;

		template <typename... Is>
		struct indexer<list_<Is...>> {
			template <typename F, template<typename...> class C, typename... Ts>
			using f = C<typename dispatch<2, F>::template f<Is, Ts>...>;
		};

		template <std::size_t N>
		using make_index_for_zip = typename make_seq_impl<next_state(0, N)>::template f<N>;

		template <std::size_t N, typename F, typename C>
		struct dispatch<N, zip_with_index_<F, C>> {
			template <typename... Ts>
			using f = typename indexer<make_index_for_zip<sizeof...(Ts)>>::template f<
				    F, dispatch<find_dispatch(sizeof...(Ts)), C>::template f, Ts...>;
		};
		template <std::size_t N, typename F, template <typename...> class C>
		struct dispatch<N, zip_with_index_<F, lift_<C>>> {
			template <typename... Ts>
			using f = typename indexer<make_index_for_zip<sizeof...(Ts)>>::template f<F, C,
				                                                                        Ts...>;
		};
	} // namespace detail
} // namespace boost::tmp
