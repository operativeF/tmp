//  Copyright 2018-2019 Odin Holmes.
//            2020-2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Algorithm.AnyOf;

import Boost.TMP.Base.Always;
import Boost.TMP.Base.Comparison;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.If;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Algorithm.FindIf;

import Boost.TMP.Detail.Dispatch;

export namespace boost::tmp {
		template <typename F = identity_, typename C = identity_>
		struct any_of_;

		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, any_of_<F, C>>
			    : dispatch<N,
			               find_if_<F, if_<is_<nothing_>, always_<false_, C>, always_<true_, C>>>> {
			};
		} // namespace detail
} // export namespace boost::tmp
