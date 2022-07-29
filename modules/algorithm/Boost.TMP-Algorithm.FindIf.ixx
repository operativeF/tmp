//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#include <limits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.FindIf;

import :Base.Foldey;
import :Base.Identity;
import :Detail.Dispatch;

#if _MSC_VER
import std;
#endif

// FIXME: foldey is required outside of find_if.
namespace boost::tmp {
	export template <typename F, typename C = identity_>
	struct find_if_ {};

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

	template <std::size_t N, typename F, typename C>
	struct dispatch<N, find_if_<F, C>> {
		template <typename... Ts>
		using f = dispatch<1, C>::template f<
				   typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
						typename county<false, std::numeric_limits<std::size_t>::max(),
							typename dispatch<1, F>::template f>, 0, Ts...>>;
	};

	template <std::size_t N, template <typename...> class F, typename C>
	struct dispatch<N, find_if_<lift_<F>, C>> {
		template <typename... Ts>
		using f = dispatch<1, C>::template f<typename foldey<select_foldey_loop(
				sizeof...(Ts))>::template f<typename county<false, std::numeric_limits<std::size_t>::max(), F>, 0, Ts...>>;
	};
} // export namespace boost::tmp
