//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Base.Always;

import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Base.Identity;

export namespace boost::tmp {
		template <typename T, typename C = identity_>
		struct always_ {};

		namespace detail {
			template <unsigned N, typename T, typename C>
			struct dispatch<N, always_<T, C>> {
				template <typename...>
				using f = typename dispatch<1, C>::template f<T>;
			};
		} // namespace detail
} // export namespace boost::tmp
