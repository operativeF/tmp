//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#include <utility>

export module Boost.TMP.Sequence.ZipWithIndex;

import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Sequence.MakeSequence;

export namespace boost::tmp {
		template <typename F = listify_, typename C = listify_>
		struct zip_with_index_ {};
		namespace detail {
			template <typename L>
			struct indexer;

			template <typename... Is>
			struct indexer<list_<Is...>> {
				template <typename F, template<typename...> class C, typename... Ts>
				using f = C<typename dispatch<2, F>::template f<Is, Ts>...>;
			};

			template <unsigned N>
			using make_index_for_zip = typename make_seq_impl<next_state(0, N)>::template f<N>;

			template <unsigned N, typename F, typename C>
			struct dispatch<N, zip_with_index_<F, C>> {
				template <typename... Ts>
				using f = typename indexer<make_index_for_zip<sizeof...(Ts)>>::template f<
				        F, dispatch<find_dispatch(sizeof...(Ts)), C>::template f, Ts...>;
			};
			template <unsigned N, typename F, template <typename...> class C>
			struct dispatch<N, zip_with_index_<F, lift_<C>>> {
				template <typename... Ts>
				using f = typename indexer<make_index_for_zip<sizeof...(Ts)>>::template f<F, C,
				                                                                          Ts...>;
			};
		} // namespace detail
} // export namespace boost::tmp
