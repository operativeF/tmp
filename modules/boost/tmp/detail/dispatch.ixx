//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Detail.Dispatch;

export namespace boost::tmp::detail {
			constexpr unsigned find_dispatch(unsigned n) {
				return n <= 8 ? n :
				                n < 16 ?
				                9 :
				                n == 16 ?
				                16 :
				                n < 32 ?
				                17 :
				                n == 32 ?
				                32 :
				                n < 64 ? 33 : n == 64 ? 64 : n < 128 ? 65 : n == 128 ? 128 : 129;
			}

			template <unsigned N, typename T>
			struct dispatch;

			template <typename C>
			struct dispatch_unknown {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
			};
} // export namespace boost::tmp::detail
