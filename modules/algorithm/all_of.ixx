//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Algorithm.AllOf;

import Boost.TMP.Base.Logic;
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
	export template <typename F, typename C = identity_>
	struct all_of_ {};
		
	namespace detail {
		template <std::size_t N, typename F, typename C>
		struct dispatch<N, all_of_<F, C>>
            : dispatch<N, and_<F, C>> {};
	} // namespace detail
} // namespace boost::tmp
