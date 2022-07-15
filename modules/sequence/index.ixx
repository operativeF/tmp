//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Sequence.Index;

import Boost.TMP.Detail;

import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Sequence.Drop;
import Boost.TMP.Sequence.Unpack;

#ifdef __GNUC__
import <cstdint>;
#elif __clang__
import std;
#elif _MSC_VER
import std.core;
#endif

export namespace boost::tmp {
	template <typename I, typename C = identity_>
	struct index_ {};
	template <typename I, typename C = identity_>
	using unpack_index_ = unpack_<index_<I, C>>;
	template <typename C = identity_>
	using front_ = index_<sizet_<0>, C>;

	template <typename C = identity_>
	using i0_ = index_<sizet_<0>, C>;
	template <typename C = identity_>
	using i1_ = index_<sizet_<1>, C>;
	template <typename C = identity_>
	using i2_ = index_<sizet_<2>, C>;
	template <typename C = identity_>
	using i3_ = index_<sizet_<3>, C>;
	template <typename C = identity_>
	using i4_ = index_<sizet_<4>, C>;
	template <typename C = identity_>
	using i5_ = index_<sizet_<5>, C>;
	template <typename C = identity_>
	using i6_ = index_<sizet_<6>, C>;
	template <typename C = identity_>
	using i7_ = index_<sizet_<7>, C>;
	template <typename C = identity_>
	using ui0_ = unpack_<index_<sizet_<0>, C>>;
	template <typename C = identity_>
	using ui1_ = unpack_<index_<sizet_<1>, C>>;
	template <typename C = identity_>
	using ui2_ = unpack_<index_<sizet_<2>, C>>;
	template <typename C = identity_>
	using ui3_ = unpack_<index_<sizet_<3>, C>>;
	template <typename C = identity_>
	using ui4_ = unpack_<index_<sizet_<4>, C>>;
	template <typename C = identity_>
	using ui5_ = unpack_<index_<sizet_<5>, C>>;
	template <typename C = identity_>
	using ui6_ = unpack_<index_<sizet_<6>, C>>;
	template <typename C = identity_>
	using ui7_ = unpack_<index_<sizet_<7>, C>>;

	namespace detail {
		template <std::size_t N, typename I, typename C>
		struct dispatch<N, index_<I, C>> : dispatch<N, drop_<I, front_<C>>> {};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<nothing_, C>> {
			template <typename... Ts>
			using f = nothing_;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<0>, C>> {
			template <typename T0, typename... Ts>
			using f = typename dispatch<1, C>::template f<T0>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<1>, C>> {
			template <typename T0, typename T1, typename... Ts>
			using f = typename dispatch<1, C>::template f<T1>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<2>, C>> {
			template <typename T0, typename T1, typename T2, typename... Ts>
			using f = typename dispatch<1, C>::template f<T2>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<3>, C>> {
			template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
			using f = typename dispatch<1, C>::template f<T3>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<4>, C>> {
			template <typename T0, typename T1, typename T2, typename T3, typename T4,
				        typename... Ts>
			using f = typename dispatch<1, C>::template f<T4>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<5>, C>> {
			template <typename T0, typename T1, typename T2, typename T3, typename T4,
				        typename T5, typename... Ts>
			using f = typename dispatch<1, C>::template f<T5>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<6>, C>> {
			template <typename T0, typename T1, typename T2, typename T3, typename T4,
				        typename T5, typename T6, typename... Ts>
			using f = typename dispatch<1, C>::template f<T6>;
		};
		template <std::size_t N, typename C>
		struct dispatch<N, index_<sizet_<7>, C>> {
			template <typename T0, typename T1, typename T2, typename T3, typename T4,
				        typename T5, typename T6, typename T7, typename... Ts>
			using f = typename dispatch<1, C>::template f<T7>;
		};
	} // namespace detail
} // export namespace boost::tmp
