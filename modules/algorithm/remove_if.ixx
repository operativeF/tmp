//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Algorithm.RemoveIf;

import Boost.TMP.Algorithm.Transform;

import Boost.TMP.Base.Always;
import Boost.TMP.Base.Comparison;
import Boost.TMP.Base.If;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Sequence.Join;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

/// \brief Given a predicate F, check the variadic parameter pack passed in
/// and remove the value if the predicate holds true.
namespace boost::tmp {
	export template <typename F, typename C = listify_>
	struct remove_if_ {};

	namespace detail {
		template <std::size_t N, typename F, typename C>
		struct dispatch<N, remove_if_<F, C>>
			: dispatch<N, transform_<if_<F, always_<list_<>>, listify_>, join_<C>>> {};
	} // namespace detail
} // namespace boost::tmp
