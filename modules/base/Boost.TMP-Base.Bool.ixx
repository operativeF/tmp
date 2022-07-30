//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Base.Bool;

namespace boost::tmp {
    export template <bool B>
	struct bool_ {
		static constexpr bool value = B;
	};

	export using true_  = bool_<true>;
	export using false_ = bool_<false>;
} // namespace boost::tmp
