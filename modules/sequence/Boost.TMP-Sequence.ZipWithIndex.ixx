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

export module Boost.TMP:Sequence.ZipWithIndex;

import :Base.Lift;
import :Base.List;
import :Base.Dispatch;
import :Sequence.MakeSequence;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename F = listify_, typename C = listify_>
	struct zip_with_index_ {};

	template <typename L>
	struct indexer;

	template <typename... Is>
	struct indexer<list_<Is...>> {
		template <typename F, template<typename...> class C, typename... Ts>
		using f = C<typename dispatch<2, F>::template f<Is, Ts>...>;
	};

	template <std::size_t N>
	using make_index_for_zip = make_seq_impl<next_state(0, N)>::template f<N>;

	template <std::size_t N, typename F, typename C>
	struct dispatch<N, zip_with_index_<F, C>> {
		template <typename... Ts>
		using f = indexer<make_index_for_zip<sizeof...(Ts)>>::template f<
				F, dispatch<find_dispatch(sizeof...(Ts)), C>::template f, Ts...>;
	};
	template <std::size_t N, typename F, template <typename...> class C>
	struct dispatch<N, zip_with_index_<F, lift_<C>>> {
		template <typename... Ts>
		using f = indexer<make_index_for_zip<sizeof...(Ts)>>::template f<F, C,
																					Ts...>;
	};
} // namespace boost::tmp
