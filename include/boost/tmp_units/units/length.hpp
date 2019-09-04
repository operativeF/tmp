#ifndef BOOST_TMP_LENGTH_HPP_INCLUDED
#define BOOST_TMP_LENGTH_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/sequence/set.hpp>
#include <boost/tmp/vocabulary.hpp>
#include "evaluators.hpp"
#include "type_dispatcher.hpp"

namespace boost::tmp::units
{
	template<typename T, typename P>
	struct unitless_;

	// Make this a constexpr lambda?
	template<typename ConvType>
	struct convertTo {
		template<typename T>
		constexpr auto operator()(const T& val)
		{
			if(std::ratio_greater_v<ConvType::mod_ratio, T::mod_ratio>)
			{
				using conv_factor = std::ratio_divide<ConvType::mod_ratio, T::mod_ratio>;
				return static_cast<ConvType>(val.value * conv_factor::den / conv_factor::num);
			}
			else
			{
				using conv_factor = std::ratio_divide<T::mod_ratio, ConvType::mod_ratio>;
				return static_cast<ConvType>(val.value * conv_factor::num / conv_factor::den);
			}
		}
	};

    template<typename T = unity_ratio, typename P = long double>
    struct meter_impl {
        constexpr meter_impl<T, P>() : value(0) {}
        constexpr meter_impl<T, P>(P val) : value(val) {}
        
		P value;
        using mod_ratio = T;
		using impl = list_<list_<meter_l>, list_<>>;
	};

    using meter_ld      = meter_impl<unity_ratio, long double>;

    using kilometer_ld  = meter_impl<std::kilo, long double>;

	using millimeter_ld = meter_impl<std::milli, long double>;

    using centimeter_ld = meter_impl<std::centi, long double>;

	using micrometer_ld = meter_impl<std::micro, long double>;

    using nanometer_ld  = meter_impl<std::nano, long double>;

	using picometer_ld  = meter_impl<std::pico, long double>;

	using femtometer_ld = meter_impl<std::femto, long double>;

	using attometer_ld  = meter_impl<std::atto, long double>;

	using meter_ull      = meter_impl<unity_ratio, unsigned long long>;

    using kilometer_ull  = meter_impl<std::kilo, unsigned long long>;

	using millimeter_ull = meter_impl<std::milli, unsigned long long>;

    using centimeter_ull = meter_impl<std::centi, unsigned long long>;

	using micrometer_ull = meter_impl<std::micro, unsigned long long>;

    using nanometer_ull  = meter_impl<std::nano, unsigned long long>;

	using picometer_ull  = meter_impl<std::pico, unsigned long long>;

	using femtometer_ull = meter_impl<std::femto, unsigned long long>;

	using attometer_ull  = meter_impl<std::atto, unsigned long long>;


	// If ConvType > T
	// (multiplying) T * (ConvType / T)
	// else ConvType < T
	// (dividing) T * (T / ConvType)
    
    constexpr kilometer_ld operator ""_km(long double val) {
		return static_cast<kilometer_ld>(val);
	}
    constexpr meter_ld  operator ""_m(long double val) {
		return static_cast<meter_ld>(val);
	}
	constexpr centimeter_ld operator ""_cm(long double val) {
		return static_cast<centimeter_ld>(val);
	}
    constexpr millimeter_ld operator ""_mm(long double val) {
		return static_cast<millimeter_ld>(val);
	}
    constexpr micrometer_ld operator ""_um(long double val) {
		return static_cast<micrometer_ld>(val);
	}
	constexpr nanometer_ld operator ""_nm(long double val) {
		return static_cast<nanometer_ld>(val);
	}
    constexpr picometer_ld operator ""_pm(long double val) {
		return static_cast<picometer_ld>(val);
	}

	constexpr kilometer_ull operator ""_km(unsigned long long val) {
		return static_cast<kilometer_ull>(val);
	}
    constexpr meter_ull  operator ""_m(unsigned long long val) {
		return static_cast<meter_ull>(val);
	}
	constexpr centimeter_ull operator ""_cm(unsigned long long val) {
		return static_cast<centimeter_ull>(val);
	}
    constexpr millimeter_ull operator ""_mm(unsigned long long val) {
		return static_cast<millimeter_ull>(val);
	}
    constexpr micrometer_ull operator ""_um(unsigned long long val) {
		return static_cast<micrometer_ull>(val);
	}
	constexpr nanometer_ull operator ""_nm(unsigned long long val) {
		return static_cast<nanometer_ull>(val);
	}
    constexpr picometer_ull operator ""_pm(unsigned long long val) {
		return static_cast<picometer_ull>(val);
	}
}

#endif // BOOST_TMP_LENGTH_HPP_INCLUDED