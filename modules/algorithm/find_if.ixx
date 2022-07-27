//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#include <limits>
#endif // __GNUC__

export module Boost.TMP.Algorithm.FindIf;

import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

// FIXME: foldey is required outside of find_if.
namespace boost::tmp {
	export template <typename F, typename C = identity_>
	struct find_if_ {};

	template <typename T>
	// @TODO: Document this workaround more thoroughly.
	using id_ = T; // weird clang workaround
	template <bool Found, std::size_t At, template <typename...> class F>
	struct county {
		static constexpr auto value = std::numeric_limits<std::size_t>::max();
		template <typename T>
		using f = county<F<T>::value, (At + 1), F>;
	};
	template <std::size_t At, template <typename...> class F>
	struct county<true, At, F> {
		template <typename T>
		using f                    = county;
		static constexpr std::size_t value = At;
	};

	export consteval std::size_t select_foldey_loop(std::size_t rest_size) {
		return static_cast<std::size_t>(rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : 1008);
	}
	consteval std::size_t select_foldey(std::size_t chunk_size, std::size_t rest_size, std::size_t found_at_index) {
		return found_at_index == -1 ? select_foldey_loop(rest_size) :
										chunk_size - found_at_index;
	}
	export { // export foldey metaclosure
	template <std::size_t S>
	struct foldey {
		template <typename F, std::size_t N, typename...>
		using f = sizet_<N - S>;
	};
	template <>
	struct foldey<1000> {
		template <typename F, std::size_t N, typename... Ts>
		using f = nothing_;
	};
	template <>
	struct foldey<1001> {
		template <typename F, std::size_t N, typename T0, typename... Ts>
		using f = typename foldey<select_foldey(
				1, sizeof...(Ts), F::template f<T0>::value)>::template f<F, N + 1, Ts...>;
	};
	template <>
	struct foldey<1008> {
		template <typename F, std::size_t N, typename T0, typename T1, typename T2,
					typename T3, typename T4, typename T5, typename T6, typename T7,
					typename... Ts>
		using f = typename foldey<select_foldey(
				8, sizeof...(Ts),
				id_<typename F::template f<T0>::template f<T1>::template f<T2>::template f<
						T3>::template f<T4>::template f<T5>::template f<T6>::
							template f<T7>>::value)>::template f<F, N + 8, Ts...>;
	};

	template <>
	struct foldey<1000000> {};

	} // export foldey

	template <std::size_t N, typename F, typename C>
	struct dispatch<N, find_if_<F, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<
				typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
						county<false, std::numeric_limits<std::size_t>::max(), dispatch<1, F>::template f>, 0, Ts...>>;
	};

	template <std::size_t N, template <typename...> class F, typename C>
	struct dispatch<N, find_if_<lift_<F>, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
				sizeof...(Ts))>::template f<county<false, std::numeric_limits<std::size_t>::max(), F>, 0, Ts...>>;
	};
} // export namespace boost::tmp
