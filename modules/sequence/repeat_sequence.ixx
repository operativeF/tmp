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

export module Boost.TMP.Sequence.RepeatSequence;

import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Sequence.Join;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template<typename N = sizet_<0>, typename C = listify_>
	struct repeat_sequence_{};

	consteval std::size_t repeat_select(std::size_t N) {
		return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
	}

	template <std::size_t, typename C>
	struct repeat_seq_impl;

	template <typename C>
	struct repeat_seq_impl<0, C> {
		template <typename...>
		using f = typename dispatch<0, C>::template f<>;
	};

	template <typename C>
	struct repeat_seq_impl<1, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 1, C>::template f<T, Ts...>;
	};

	template <typename C>
	struct repeat_seq_impl<2, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 2, C>::template f<T, T, Ts...>;
	};

	template <typename C>
	struct repeat_seq_impl<3, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 3, C>::template f<T, T, T, Ts...>;
	};
	template <typename C>
	struct repeat_seq_impl<4, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 4, C>::template f<T, T, T, T, Ts...>;
	};
	template <typename C>
	struct repeat_seq_impl<5, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 5, C>::template f<T, T, T, T, T, Ts...>;
	};
	template <typename C>
	struct repeat_seq_impl<6, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 6, C>::template f<T, T, T, T, T, T, Ts...>;
	};
	template <typename C>
	struct repeat_seq_impl<7, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 7, C>::template f<T, T, T, T, T, T, T, Ts...>;
	};
	template <typename C>
	struct repeat_seq_impl<8, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 8, C>::template f<T, T, T, T, T, T, T, T, Ts...>;
	};
	template <typename C>
	struct repeat_seq_impl<16, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 16, C>::template f<T, T, T, T, T, T, T, T,
														T, T, T, T, T, T, T, T, Ts...>;
	};

	template <typename C>
	struct repeat_seq_impl<32, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 32, C>::template f<T, T, T, T, T, T, T, T,
														T, T, T, T, T, T, T, T,
														T, T, T, T, T, T, T, T,
														T, T, T, T, T, T, T, T, Ts...>;
	};

	template <typename C>
	struct repeat_seq_impl<64, C> {
		template <typename T, typename... Ts>
		using f = typename dispatch<sizeof...(Ts) + 64, C>::template f<
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T,
				T, T, T, T, T, T, T, T, Ts...>;
	};

	template <std::size_t P, typename C, std::size_t Step = repeat_select(P)>
	struct make_repeat : repeat_seq_impl<Step, repeat_sequence_<sizet_<(P - Step) + 1>, C>> {};

	template <std::size_t P, typename C>
	struct make_repeat<P, C, P> : repeat_seq_impl<P, C> {};

	template <std::size_t N, typename P, typename C>
	struct dispatch<N, repeat_sequence_<P, C>> : make_repeat<P::value, C> {};
} // namespace boost::tmp
