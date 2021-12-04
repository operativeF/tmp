//  Copyright 2019-2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Algorithm.RemovePairs;

import Boost.TMP.Base.Call;
import Boost.TMP.Base.Comparison;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.If;
import Boost.TMP.Base.Logic;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Sequence.Join;

export namespace boost::tmp {
		// Requires sets to be the input, unless 
		template<typename C = listify_>
		struct remove_pairs_;

		namespace detail {
			template <typename C, typename... Ts>
			struct remove_pairs_impl {
				using type = typename dispatch<0, join_<C>>::template f<Ts...>;
			};

			// template <typename C, typename T1, typename T, typename T2>
			// struct remove_pairs_impl<C, list_<T1, T, T, T2>>
			//     : remove_pairs_impl<C, list_<T1, T2>> {};

			// Append to list function
			// template <typename C, typename... T1s, typename T, typename... T2s>
			// struct remove_pairs_impl<C, list_<T1s..., T, T, T2s...>>
			//     : remove_pairs_impl<C, list_<T1s..., T2s...>> {};

			template <typename C, typename T, typename... T2s>
			struct remove_pairs_impl<C, list_<T, T, T2s...>>
			    : remove_pairs_impl<C, list_<T2s...>> {};

			template <unsigned N, typename C>
			struct dispatch<N, remove_pairs_<C>> {
				template <typename... Ts>
				using f = typename detail::remove_pairs_impl<C, list_<Ts...>>::type;
			};
		} // namespace detail
} // export namespace boost::tmp
