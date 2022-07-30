//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Lift;

import :Base.Identity;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <template <typename...> class F, typename C = identity_>
	struct lift_ {};

	export template <typename C = identity_>
	struct result_ {};

	template <template <typename...> class F, typename C>
	struct dispatch<1, lift_<F, C>> {
		template <typename T>
		using f = dispatch<1, C>::template f<F<T>>;
	};
	template <template <typename...> class F, typename C>
	struct dispatch<2, lift_<F, C>> {
		template <typename T0, typename T1>
		using f = dispatch<1, C>::template f<F<T0, T1>>;
	};
	template <template <typename...> class F, typename C>
	struct dispatch<3, lift_<F, C>> {
		template <typename T0, typename T1, typename T2>
		using f = dispatch<1, C>::template f<F<T0, T1, T2>>;
	};
	template <template <typename...> class F, typename C>
	struct dispatch<4, lift_<F, C>> {
		template <typename T0, typename T1, typename T2, typename T3>
		using f = dispatch<1, C>::template f<F<T0, T1, T2, T3>>;
	};
	template <std::size_t N, template <typename...> class F, typename C>
	struct dispatch<N, lift_<F, C>> {
		template <typename... Ts>
		using f = dispatch<1, C>::template f<F<Ts...>>;
	};
	template <typename C>
	struct dispatch<1, result_<C>> {
		template <typename T>
		using f = dispatch<1, C>::template f<T::type>;
	};
} // namespace boost::tmp
