//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Partition;

import :Algorithm.Filter;
import :Algorithm.RemoveIf;
import :Base.Vocabulary;
import :Detail.Dispatch;
import :Sequence.Tee;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {
	/// \brief
	/// Given a unary predicate, separate a list into a list of two lists, with the first being
	/// the values where the predicate holds.
	export template <typename F, typename C = listify_>
	struct partition_ {};

	template <std::size_t N, typename F, typename C>
	struct dispatch<N, partition_<F, C>> : dispatch<N, tee_<filter_<F>, remove_if_<F>, C>> {};
} // namespace boost::tmp
