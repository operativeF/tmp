//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Base.List;

import :Base.Lift;

namespace boost::tmp {
	export template <typename... Ts>
	struct list_ {};

	export using listify_ = lift_<list_>;
} // namespace boost::tmp
