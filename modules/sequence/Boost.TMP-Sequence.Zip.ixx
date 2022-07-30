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

export module Boost.TMP:Sequence.Zip;

import :Algorithm.Transform;
import :Base.List;
import :Base.Dispatch;
import :Sequence.Unpack;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename F, typename C = listify_>
	struct zip_ {};

	template<typename F, typename C, typename T, typename U>
	struct zip2;
	template<typename F, typename C, typename...Ts, typename...Us>
	struct zip2<F,C,list_<Ts...>,list_<Us...>>{
		using type = dispatch<find_dispatch(sizeof...(Ts)),C>::template f<typename dispatch<2,F>::template f<Ts,Us>...>;
	};
	template <typename F, typename C>
	struct dispatch<1, zip_<F, C>> : dispatch<1, unpack_<transform_<F, C>>> {};
	template <typename F, typename C>
	struct dispatch<2, zip_<F, C>> {
		template<typename T, typename U>
		using f = zip2<F, C, T, U>::type;
	};
} // namespace boost::tmp
