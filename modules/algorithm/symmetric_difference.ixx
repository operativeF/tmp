//  Copyright 2019-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Algorithm.SymmetricDiff;

import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Sequence.Join;

namespace boost::tmp {
	// Returns a single list where common elements from both are removed.
	export template<typename F = listify_, typename C = listify_>
	struct unary_symmetric_diff_ {};

	// Returns list of two lists where elements common to both input lists are removed from each.
	export template<typename F = listify_, typename C = listify_>
	struct binary_symmetric_diff_ {};

	namespace detail {
		template <template <typename...> class F, typename T, typename... Ts>
		using binary_symmetric_diff_helper_ = list_<F<T, Ts>...>;

		template <template <typename...> class F, typename C, typename T, typename U>
		struct binary_symmetric_diff_unpacker_ {};

		template <template <typename...> class F, typename C, typename... Ts, typename... Us>
		struct binary_symmetric_diff_unpacker_<F, C, list_<Ts...>, list_<Us...>> {
			using type =
					typename dispatch<find_dispatch(sizeof...(Ts)),
										join_<C>>::template f<binary_symmetric_diff_helper_<F, Ts, Us...>...>;
		};

		template <template <typename...> class F, typename C>
		struct dispatch<2, binary_symmetric_diff_<lift_<F>, C>> {
			template <typename T, typename U>
			using f = typename binary_symmetric_diff_unpacker_<F, C, T, U>::type;
		};

		template <typename F, typename C>
		struct dispatch<2, binary_symmetric_diff_<F, C>>
				: dispatch<2, binary_symmetric_diff_<lift_<dispatch<2, F>::template f>, C>> {};
	} // namespace detail
} // namespace boost::tmp
