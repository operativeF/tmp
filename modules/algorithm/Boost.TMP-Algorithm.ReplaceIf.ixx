//  Copyright 2018-2019 Odin Holmes.
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

export module Boost.TMP:Algorithm.ReplaceIf;

import :Algorithm.Transform;
import :Base.Always;
import :Base.Identity;
import :Base.If;
import :Base.Vocabulary;
import :Detail.Dispatch;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER

/// \brief Given a variadic parameter pack, replace every value that fulfills
/// the predicate F with the value Input.
namespace boost::tmp {
	export template <typename Input, typename F, typename C = listify_>
	struct replace_if_ {};

	template <std::size_t N, typename Input, typename F, typename C>
	struct dispatch<N, replace_if_<Input, F, C>>
		: dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
} // namespace boost::tmp
