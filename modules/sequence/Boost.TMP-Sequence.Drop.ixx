//  Copyright 2018 Odin Holmes.
//	          2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP:Sequence.Drop;

import :Base.Call;
import :Base.Vocabulary;
import :Detail.Dispatch;
import :Sequence.Rotate;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	/// \brief Drop n values, starting from the front,
	/// off the passed in list.
	export template <typename N = sizet_<0>, typename C = listify_>
	struct drop_ {};

	consteval std::size_t drop_select(std::size_t N) {
		return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
	}
	template <std::size_t, typename C>
	struct drop_impl;
	template <typename C>
	struct drop_impl<0, C> {
		template <typename... Ts>
		using f = call_<C, Ts...>;
	};
	template <typename C>
	struct drop_impl<1, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<2, C> {
		template <typename T0, typename T1, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<3, C> {
		template <typename T0, typename T1, typename T2, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<4, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<5, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<6, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<7, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<8, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename T7, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<16, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename T7, typename T8, typename T9,
					typename T10, typename T11, typename T12, typename T13, typename T14,
					typename T15, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<32, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename T7, typename T8, typename T9,
					typename T10, typename T11, typename T12, typename T13, typename T14,
					typename T15, typename T16, typename T17, typename T18, typename T19,
					typename T20, typename T21, typename T22, typename T23, typename T24,
					typename T25, typename T26, typename T27, typename T28, typename T29,
					typename T30, typename T31, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};
	template <typename C>
	struct drop_impl<64, C> {
		template <typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename T7, typename T8, typename T9,
					typename T10, typename T11, typename T12, typename T13, typename T14,
					typename T15, typename T16, typename T17, typename T18, typename T19,
					typename T20, typename T21, typename T22, typename T23, typename T24,
					typename T25, typename T26, typename T27, typename T28, typename T29,
					typename T30, typename T31, typename T32, typename T33, typename T34,
					typename T35, typename T36, typename T37, typename T38, typename T39,
					typename T40, typename T41, typename T42, typename T43, typename T44,
					typename T45, typename T46, typename T47, typename T48, typename T49,
					typename T50, typename T51, typename T52, typename T53, typename T54,
					typename T55, typename T56, typename T57, typename T58, typename T59,
					typename T60, typename T61, typename T62, typename T63, typename... Ts>
		using f = typename dispatch<sizeof...(Ts), C>::template f<Ts...>;
	};

	template <std::size_t P, typename C, std::size_t Step = drop_select(P)>
	struct make_drop : drop_impl<Step, drop_<sizet_<(P - Step)>, C>> { /* not done */
	};
	template <std::size_t P, typename C>
	struct make_drop<P, C, P> : drop_impl<P, C> {};

	template <std::size_t N, typename P, typename C>
	struct dispatch<N, drop_<P, C>> : make_drop<P::value, C> {};
} // namespace boost::tmp
