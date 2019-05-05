#ifndef BOOST_TMP_PRODUCT_HPP_INCLUDED
#define BOOST_TMP_PRODUCT_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../vocabulary.hpp"
#include "../sequence/join.hpp"

// \brief
// Given n lists, generates the Cartesian product of those n lists (n-tuples).
// \example
// 	using xl0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;
//	using xr0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;
//
//  using result = call_<product_<>, xl0, xr0>;
//  \text Will generate the Cartesian product of the lists xl0 and xr0:
//  result = list_<list_<x<1>, x<1>>, list_<x<1>, x<2>>, ..., list_<x<1>, x<10>>, ..., list_<x<10>, x<1>>, list_<x<10>, x<2>>, ..., list_<x<10>, x<10>>>
namespace boost { 
	namespace tmp {
		template <typename F = listify_, typename C = listify_>
		struct product_ {};

		namespace detail {
			template <template <typename...> class F, typename T, typename... Ts>
			using product_helper_ = list_<F<T, Ts>...>;

			template <template <typename...> class F, typename C, typename T, typename U>
			struct product_unpacker {};

			template <template <typename...> class F, typename C, typename... Ts, typename... Us>
			struct product_unpacker<F, C, list_<Ts...>, list_<Us...>> {
				using type =
				        typename dispatch<find_dispatch(sizeof...(Ts)),
				                          join_<C>>::template f<product_helper_<F, Ts, Us...>...>;
			};

			template <template <typename...> class F, typename C>
			struct dispatch<2, product_<lift_<F>, C>> {
				template <typename T, typename U>
				using f = typename product_unpacker<F, C, T, U>::type;
			};

			template <typename F, typename C>
			struct dispatch<2, product_<F, C>>
					: dispatch<2, product_<lift_<dispatch<2, F>::template f>, C>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif