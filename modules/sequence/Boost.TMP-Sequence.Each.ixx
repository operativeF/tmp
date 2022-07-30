//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Sequence.Each;

import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename... Fs>
	struct each_ {};
	
	template <typename F, typename C>
	struct dispatch<1, each_<F, C>> {
		template <typename T>
		using f = dispatch<1, C>::template f<dispatch<1, F>::template f<T>>;
	};
	template <typename F0, typename F1, typename C>
	struct dispatch<2, each_<F0, F1, C>> {
		template <typename T0, typename T1>
		using f = dispatch<2, C>::template f<dispatch<1, F0>::template f<T0>,
											 dispatch<1, F1>::template f<T1>>;
	};
	template <typename F0, typename F1, typename F2, typename C>
	struct dispatch<3, each_<F0, F1, F2, C>> {
		template <typename T0, typename T1, typename T2>
		using f = dispatch<2, C>::template f<dispatch<1, F0>::template f<T0>,
											 dispatch<1, F1>::template f<T1>,
											 dispatch<1, F2>::template f<T2>>;
	};
	template <typename F0, typename F1, typename F2, typename F3, typename C>
	struct dispatch<4, each_<F0, F1, F2, F3, C>> {
		template <typename T0, typename T1, typename T2, typename T3>
		using f = dispatch<2, C>::template f<dispatch<1, F0>::template f<T0>,
											 dispatch<1, F1>::template f<T1>,
											 dispatch<1, F2>::template f<T2>,
											 dispatch<1, F3>::template f<T3>>;
	};
} // namespace boost::tmp
