//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Base.Char;

namespace boost::tmp {
	export template<char B>
	struct char_
	{
		static constexpr char value = B;
	};
} // namespace boost::tmp