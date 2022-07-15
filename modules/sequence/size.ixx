//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Sequence.Size;

import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Detail.Dispatch;

#ifdef __GNUC__
import <cstdint>;
#elif __clang__
import std;
#elif _MSC_VER
import std.core;
#endif

namespace boost::tmp {
	export template <typename C = identity_>
	struct size_ {};

	namespace detail {
		template <std::size_t N, typename C>
		struct dispatch<N, size_<C>> {
			template <typename... Ls>
			using f = typename dispatch<1, C>::template f<sizet_<sizeof...(Ls)>>;
		};
	} // namespace detail
} // namespace boost::tmp
