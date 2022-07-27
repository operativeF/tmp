//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Base.Identity;

import Boost.TMP.Detail;

namespace boost::tmp {
	export struct identity_ {};

	template <>
	struct dispatch<1, identity_> {
		template <typename T>
		using f = T;
	};
} // namespace boost::tmp
