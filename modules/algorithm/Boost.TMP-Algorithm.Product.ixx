//  Copyright 2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Algorithm.Product;

import :Base.Lift;
import :Base.Vocabulary;
import :Detail.Dispatch;
import :Sequence.Join;

namespace boost::tmp {
	// \brief
	// Given two lists, generates the Cartesian product of said lists (n x m tuples generated).
	// \example
	// 	using xl0 = list_<x<1>, x<2>, ..., x<n>>;
	//	using xr0 = list_<x<1>, x<2>, ..., x<m>>;
	//
	//  using result = call_<product_<>, xl0, xr0>;
	//  \text Will generate the Cartesian product of the lists xl0 and xr0, from xl0[1]-xl0[n]
	//  and xr0[1]-xr0[m]: result = list_<list_<x<1>, x<1>>, list_<x<1>, x<2>>, ..., list_<x<1>,
	//  x<n>>, ..., list_<x<n>, x<1>>, list_<x<n>, x<2>>, ..., list_<x<n>, x<m>>>
	export template <typename F = listify_, typename C = listify_>
	struct product_ {};

	template <template <typename...> class F, typename T, typename... Ts>
	using product_helper_ = list_<F<T, Ts>...>;

	template <template <typename...> class F, typename C, typename T, typename U>
	struct product_unpacker {};

	template <template <typename...> class F, typename C, typename... Ts, typename... Us>
	struct product_unpacker<F, C, list_<Ts...>, list_<Us...>> {
		using type = dispatch<find_dispatch(sizeof...(Ts)),
									join_<C>>::template f<product_helper_<F, Ts, Us...>...>;
	};

	template <template <typename...> class F, typename C>
	struct dispatch<2, product_<lift_<F>, C>> {
		template <typename T, typename U>
		using f = product_unpacker<F, C, T, U>::type;
	};

	template <typename F, typename C>
	struct dispatch<2, product_<F, C>>
			: dispatch<2, product_<lift_<dispatch<2, F>::template f>, C>> {};
} // namespace boost::tmp
