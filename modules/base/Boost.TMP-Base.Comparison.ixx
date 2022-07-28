//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#include <type_traits>
#endif // __GNUC__

export module Boost.TMP:Base.Comparison;

import :Base.Identity;
import :Base.Vocabulary;
import :Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename P, typename C = identity_>
	struct is_ {};

	export template <typename V = nothing_, typename C = identity_>
	struct less_ {};

	export template <typename V = nothing_, typename C = identity_>
	struct less_eq_ {};

	export template <typename V = nothing_, typename C = identity_>
	struct greater_ {};

	export template<typename V = nothing_, typename C = identity_>
	struct bounded_open {};

	export template<typename V = nothing_, typename C = identity_>
	struct bounded_closed {};

	export template<typename V = nothing_, typename C = identity_>
	struct bounded_clopen_lo {};

	export template<typename V = nothing_, typename C = identity_>
	struct bounded_clopen_hi {};

	template <typename P, typename C>
	struct dispatch<1, is_<P, C>> {
		template <typename T>
		using f = typename dispatch<1, C>::template f<bool_<std::is_same_v<P, T>>>;
	};

	// NOTE: Internal compiler error occurs when no parentheses are used around the values.
	// Error is C1001; compiler file msc1.cpp, line 1596
	template <typename C>
	struct dispatch<2, less_<C>> {
		template <typename T, typename U>
		using f = typename dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
	};

	template <typename U, typename C>
	struct dispatch<1, less_<U, C>> {
		template<typename T>
		using f = typename dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
	};

	template <typename C>
	struct dispatch<2, less_eq_<C>> {
		template <typename T, typename U>
		using f = typename dispatch<1, C>::template f<bool_<(T::value)<=(U::value)>>;
	};

	template <typename U, typename C>
	struct dispatch<1, less_eq_<U, C>> {
		template<typename T>
		using f = typename dispatch<1, C>::template f<bool_<(U::value)<=(T::value)>>;
	};

	template <typename C>
	struct dispatch<2, greater_<C>> {
		template <typename T, typename U>
		using f = typename dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
	};

	template <typename U, typename C>
	struct dispatch<1, greater_<U, C>> {
		template<typename T>
		using f = typename dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
	};
} // namespace boost::tmp
