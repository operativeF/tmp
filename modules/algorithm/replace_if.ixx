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

export module Boost.TMP.Algorithm.ReplaceIf;

import Boost.TMP.Base.Always;
import Boost.TMP.Base.Call;
import Boost.TMP.Base.If;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Algorithm.Transform;
import Boost.TMP.Sequence.Join;

import std;

/// \brief Given a variadic parameter pack, replace every value that fulfills
/// the predicate F with the value Input.
namespace boost::tmp {
	export template <typename Input, typename F, typename C = listify_>
	struct replace_if_ {};

	namespace detail {
		template <std::size_t N, typename Input, typename F, typename C>
		struct dispatch<N, replace_if_<Input, F, C>>
			: dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
	} // namespace detail
} // namespace boost::tmp
