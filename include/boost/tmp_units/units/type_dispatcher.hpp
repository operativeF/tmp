#ifndef BOOST_TMP_TYPE_DISPATCHER_HPP_INCLUDED
#define BOOST_TMP_TYPE_DISPATCHER_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/sequence/set.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost::tmp::units
{
    // Base units
    struct meter_l : uint_<1> {};
    using unity_ratio = std::ratio<1, 1>;

    // Forward declarations of units
    template<typename T, typename P>
    struct meter_impl;
	template<typename T, typename P>
    struct meter_sq_impl;

    // Type dispatcher

    template<typename L>
	struct dispatcher {
        static_assert(true, "Type does not currently exist.");
		using f = nothing_;
	};
	/*
	template<>
	struct dispatcher<list_<list_<>, list_<>>> {
		template<typename T = unity_ratio, typename P = long double>
		using f = P;
	};
	*/

	template<>
	struct dispatcher<list_<list_<meter_l>, list_<>>> {
		template<typename T = unity_ratio, typename P = long double>
		using f = meter_impl<T, P>;
	};

	template<>
	struct dispatcher<list_<list_<meter_l, meter_l>, list_<>>> {
		template<typename T = unity_ratio, typename P = long double>
		using f = meter_sq_impl<T, P>;
	};
} // namespace boost::tmp::units

#endif // BOOST_TMP_TYPE_DISPATCHER_HPP_INCLUDED