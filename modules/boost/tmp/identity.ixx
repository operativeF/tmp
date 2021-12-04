//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Base.Identity;

import Boost.TMP.Detail;

export namespace boost::tmp {
		struct identity_ {};
#ifdef BOOST_TMP_CPP14
		namespace fusion {
			template <>
			struct rebind<identity_> {
				using type = identity_;
			};
		} // namespace fusion
#endif
		namespace detail {
			template <>
			struct dispatch<1, identity_> {
				template <typename T>
				using f = T;
			};
		} // namespace detail
} // export namespace boost::tmp
