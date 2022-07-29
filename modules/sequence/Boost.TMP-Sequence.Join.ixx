//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#include <utility>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Sequence.Join;

import :Base.Lift;
import :Base.Vocabulary;
import :Detail.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename C = listify_>
	struct join_ {};

	export template<typename C = listify_>
	struct join_seq_ {};
	
	export template<typename... Ts>
	using into_sequence = std::index_sequence<Ts::value...>;

	template <template <typename...> class C, typename...>
	struct joiner;
	template <template <typename...> class C, typename... T0s, typename... T1s,
				typename... T2s, typename... T3s, typename... T4s, typename... T5s,
				typename... T6s, typename... T7s>
	struct joiner<C, list_<T0s...>, list_<T1s...>, list_<T2s...>, list_<T3s...>,
					list_<T4s...>, list_<T5s...>, list_<T6s...>, list_<T7s...>> {
		template <typename... Vs>
		using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., Vs...>;
	};
	template <template <typename...> class C, typename... T0s, typename... T1s,
				typename... T2s, typename... T3s, typename... T4s, typename... T5s,
				typename... T6s, typename... T7s, typename... T8s, typename... T9s,
				typename... T10s, typename... T11s, typename... T12s, typename... T13s,
				typename... T14s, typename... T15s, typename... T16s, typename... T17s,
				typename... T18s, typename... T19s, typename... T20s, typename... T21s,
				typename... T22s, typename... T23s, typename... T24s, typename... T25s,
				typename... T26s, typename... T27s, typename... T28s, typename... T29s,
				typename... T30s, typename... T31s>
	struct joiner<C, list_<T0s...>, list_<T1s...>, list_<T2s...>, list_<T3s...>,
					list_<T4s...>, list_<T5s...>, list_<T6s...>, list_<T7s...>, list_<T8s...>,
					list_<T9s...>, list_<T10s...>, list_<T11s...>, list_<T12s...>,
					list_<T13s...>, list_<T14s...>, list_<T15s...>, list_<T16s...>,
					list_<T17s...>, list_<T18s...>, list_<T19s...>, list_<T20s...>,
					list_<T21s...>, list_<T22s...>, list_<T23s...>, list_<T24s...>,
					list_<T25s...>, list_<T26s...>, list_<T27s...>, list_<T28s...>,
					list_<T29s...>, list_<T30s...>, list_<T31s...>> {
		template <typename... Vs>
		using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s...,
					T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s...,
					T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s..., T24s...,
					T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., Vs...>;
	};
	template <std::size_t N>
	struct join_loop;
	template <>
	struct join_loop<1> {
		template <template <typename...> class C, typename T0 = list_<>,
					typename T1 = list_<>, typename T2 = list_<>, typename T3 = list_<>,
					typename T4 = list_<>, typename T5 = list_<>, typename T6 = list_<>,
					typename T7 = list_<>, typename T8 = list_<>, typename T9 = list_<>,
					typename T10 = list_<>, typename T11 = list_<>, typename T12 = list_<>,
					typename T13 = list_<>, typename T14 = list_<>, typename T15 = list_<>,
					typename T16 = list_<>, typename T17 = list_<>, typename T18 = list_<>,
					typename T19 = list_<>, typename T20 = list_<>, typename T21 = list_<>,
					typename T22 = list_<>, typename T23 = list_<>, typename T24 = list_<>,
					typename T25 = list_<>, typename T26 = list_<>, typename T27 = list_<>,
					typename T28 = list_<>, typename T29 = list_<>, typename T30 = list_<>,
					typename T31 = list_<>, typename... Ts>
		using f = typename join_loop<(sizeof...(Ts) > 8)>::template f<
				joiner<C, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
						T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
						T29, T30, T31>::template f,
				Ts...>;
	};
	template <>
	struct join_loop<0> {
		template <template <typename...> class C, typename T0 = list_<>,
					typename T1 = list_<>, typename T2 = list_<>, typename T3 = list_<>,
					typename T4 = list_<>, typename T5 = list_<>, typename T6 = list_<>,
					typename T7 = list_<>, typename T8 = list_<>>
		using f = typename joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
	};
	template <std::size_t N, template <typename...> class C>
	struct dispatch<N, join_<lift_<C>>> {
		template <typename... Ts>
		using f = typename join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
	};

	template <std::size_t N, typename C>
	struct dispatch<N, join_<C>> {
		template <typename... Ts>
		using f = typename join_loop<(
				sizeof...(Ts) > 8)>::template f<dispatch_unknown<C>::template f, Ts...>;
	};

	// Sequence joining metaclosures
	template <template <typename...> class C, typename...>
	struct seq_joiner;
	template <template <typename...> class C, std::size_t... T0s, std::size_t... T1s,
				std::size_t... T2s, std::size_t... T3s, std::size_t... T4s, std::size_t... T5s,
				std::size_t... T6s, std::size_t... T7s>
	struct seq_joiner<C, std::index_sequence<T0s...>, std::index_sequence<T1s...>, std::index_sequence<T2s...>, std::index_sequence<T3s...>,
					std::index_sequence<T4s...>, std::index_sequence<T5s...>, std::index_sequence<T6s...>, std::index_sequence<T7s...>> {
		template <typename... Vs>
		using f = C<sizet_<T0s>..., sizet_<T1s>..., sizet_<T2s>..., sizet_<T3s>..., sizet_<T4s>..., sizet_<T5s>..., sizet_<T6s>..., sizet_<T7s>..., Vs...>;
	};
	template <template <typename...> class C, std::size_t... T0s, std::size_t... T1s,
				std::size_t... T2s, std::size_t... T3s, std::size_t... T4s, std::size_t... T5s,
				std::size_t... T6s, std::size_t... T7s, std::size_t... T8s, std::size_t... T9s,
				std::size_t... T10s, std::size_t... T11s, std::size_t... T12s, std::size_t... T13s,
				std::size_t... T14s, std::size_t... T15s, std::size_t... T16s, std::size_t... T17s,
				std::size_t... T18s, std::size_t... T19s, std::size_t... T20s, std::size_t... T21s,
				std::size_t... T22s, std::size_t... T23s, std::size_t... T24s, std::size_t... T25s,
				std::size_t... T26s, std::size_t... T27s, std::size_t... T28s, std::size_t... T29s,
				std::size_t... T30s, std::size_t... T31s>
	struct seq_joiner<C, std::index_sequence<T0s...>, std::index_sequence<T1s...>, std::index_sequence<T2s...>, std::index_sequence<T3s...>,
					std::index_sequence<T4s...>, std::index_sequence<T5s...>, std::index_sequence<T6s...>, std::index_sequence<T7s...>, std::index_sequence<T8s...>,
					std::index_sequence<T9s...>, std::index_sequence<T10s...>, std::index_sequence<T11s...>, std::index_sequence<T12s...>,
					std::index_sequence<T13s...>, std::index_sequence<T14s...>, std::index_sequence<T15s...>, std::index_sequence<T16s...>,
					std::index_sequence<T17s...>, std::index_sequence<T18s...>, std::index_sequence<T19s...>, std::index_sequence<T20s...>,
					std::index_sequence<T21s...>, std::index_sequence<T22s...>, std::index_sequence<T23s...>, std::index_sequence<T24s...>,
					std::index_sequence<T25s...>, std::index_sequence<T26s...>, std::index_sequence<T27s...>, std::index_sequence<T28s...>,
					std::index_sequence<T29s...>, std::index_sequence<T30s...>, std::index_sequence<T31s...>> {
		template <typename... Vs>
		using f = C<sizet_<T0s>..., sizet_<T1s>..., sizet_<T2s>..., sizet_<T3s>..., sizet_<T4s>..., sizet_<T5s>..., sizet_<T6s>..., sizet_<T7s>..., sizet_<T8s>...,
					sizet_<T9s>..., sizet_<T10s>..., sizet_<T11s>..., sizet_<T12s>..., sizet_<T13s>..., sizet_<T14s>..., sizet_<T15s>..., sizet_<T16s>...,
					sizet_<T17s>..., sizet_<T18s>..., sizet_<T19s>..., sizet_<T20s>..., sizet_<T21s>..., sizet_<T22s>..., sizet_<T23s>..., sizet_<T24s>...,
					sizet_<T25s>..., sizet_<T26s>..., sizet_<T27s>..., sizet_<T28s>..., sizet_<T29s>..., sizet_<T30s>..., sizet_<T31s>..., Vs...>;
	};
	template <std::size_t N>
	struct seq_join_loop;
	template <>
	struct seq_join_loop<1> {
		template <template <typename...> class C, typename T0 = std::index_sequence<>,
					typename T1 = std::index_sequence<>, typename T2 = std::index_sequence<>, typename T3 = std::index_sequence<>,
					typename T4 = std::index_sequence<>, typename T5 = std::index_sequence<>, typename T6 = std::index_sequence<>,
					typename T7 = std::index_sequence<>, typename T8 = std::index_sequence<>, typename T9 = std::index_sequence<>,
					typename T10 = std::index_sequence<>, typename T11 = std::index_sequence<>, typename T12 = std::index_sequence<>,
					typename T13 = std::index_sequence<>, typename T14 = std::index_sequence<>, typename T15 = std::index_sequence<>,
					typename T16 = std::index_sequence<>, typename T17 = std::index_sequence<>, typename T18 = std::index_sequence<>,
					typename T19 = std::index_sequence<>, typename T20 = std::index_sequence<>, typename T21 = std::index_sequence<>,
					typename T22 = std::index_sequence<>, typename T23 = std::index_sequence<>, typename T24 = std::index_sequence<>,
					typename T25 = std::index_sequence<>, typename T26 = std::index_sequence<>, typename T27 = std::index_sequence<>,
					typename T28 = std::index_sequence<>, typename T29 = std::index_sequence<>, typename T30 = std::index_sequence<>,
					typename T31 = std::index_sequence<>, typename... Ts>
		using f = typename seq_join_loop<(sizeof...(Ts) > 8)>::template f<
				seq_joiner<C, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
						T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
						T29, T30, T31>::template f,
				Ts...>;
	};
	template <>
	struct seq_join_loop<0> {
		template <template <typename...> class C, typename T0 = std::index_sequence<>,
					typename T1 = std::index_sequence<>, typename T2 = std::index_sequence<>, typename T3 = std::index_sequence<>,
					typename T4 = std::index_sequence<>, typename T5 = std::index_sequence<>, typename T6 = std::index_sequence<>,
					typename T7 = std::index_sequence<>, typename T8 = std::index_sequence<>>
		using f = typename seq_joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
	};
	template <std::size_t N, template <typename...> class C>
	struct dispatch<N, join_seq_<lift_<C>>> {
		template <typename... Ts>
		using f = typename seq_join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
	};

	template <std::size_t N, typename C>
	struct dispatch<N, join_seq_<C>> {
		template <typename... Ts>
		using f = typename seq_join_loop<(
				sizeof...(Ts) > 8)>::template f<dispatch_unknown<C>::template f, Ts...>;
	};
} // namespace boost::tmp
