//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstddef>
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP:Base.Vocabulary;

import :Base.Lift;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

export namespace boost::tmp {
	template <typename... Ts>
	struct list_ {};

	using listify_ = lift_<list_>;

	template <unsigned long long V>
	struct uint_ {
		static constexpr unsigned long long value = V;
	};
	template <long long I>
	struct int_ {
		static constexpr long long value = I;
	};

	template<std::size_t S>
	struct sizet_
	{
		static constexpr std::size_t value = S;
	};

	template<char C>
	struct char_
	{
		static constexpr char value = C;
	};

	template<std::byte B>
	struct byte_
	{
		static constexpr std::byte value = B;
	};

	template <bool B>
	struct bool_ {
		static constexpr bool value = B;
	};

	using true_  = bool_<true>;
	using false_ = bool_<false>;

	struct nothing_ {};
} // export namespace boost::tmp
