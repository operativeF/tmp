//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Algorithm.CountIf;

import Boost.TMP.Base.Always;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.If;
import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Sequence.Join;
import Boost.TMP.Sequence.Size;

import Boost.TMP.Algorithm.Transform;

/// \brief Given a predicate F, check the variadic parameter pack passed in and count
/// each time that the predicate holds true. Returns n counts as uint_<n>.
/// \example
///
export namespace boost::tmp {
		template <typename F, typename C = identity_>
		struct count_if_ {};
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, count_if_<F, C>>
			    : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
			                             join_<size_<C>>>> {};
		} // namespace detail
} // export namespace boost::tmp
