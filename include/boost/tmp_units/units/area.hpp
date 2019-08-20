#ifndef BOOST_TMP_AREA_HPP_INCLUDED
#define BOOST_TMP_AREA_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "length.hpp"

namespace boost::tmp::units
{	
	template<typename T = unity_ratio, typename P = long double>
    struct meter_sq_impl {
        constexpr meter_sq_impl<T, P>() : value(0) {}
        constexpr meter_sq_impl<T, P>(P val) : value(val) {}
        
		P value;
        using mod_ratio = T;
        using impl = list_<list_<meter_l, meter_l>, list_<>>;

		// Add verification of inputs?
		constexpr meter_sq_impl<T, P> operator+(meter_sq_impl<T, P> val)
		{
			return static_cast<meter_sq_impl<T, P>>(this->value + val.value);
		}

		template<typename U, typename P>
		constexpr bool operator==(meter_sq_impl<U, P> val)
		{
			// normalize
			auto self_ = convertTo<meter_sq<>>()(*this);
			auto other_ = convertTo<meter_sq<>>()(val);
			return (self_.value == other_.value);
		}
	};

	template<typename P = long double>
    using meter_sq      = meter_sq_impl<unity_ratio, P>;
	template<typename P = long double>
    using kilometer_sq  = meter_sq_impl<std::kilo, P>;
	template<typename P = long double>
	using millimeter_sq = meter_sq_impl<std::milli, P>;
	template<typename P = long double>
    using centimeter_sq = meter_sq_impl<std::centi, P>;
	template<typename P = long double>
	using micrometer_sq = meter_sq_impl<std::micro, P>;
	template<typename P = long double>
    using nanometer_sq  = meter_sq_impl<std::nano, P>;
	template<typename P = long double>
	using picometer_sq  = meter_sq_impl<std::pico, P>;
	template<typename P = long double>
	using femtometer_sq = meter_sq_impl<std::femto, P>;
	template<typename P = long double>
	using attometer_sq  = meter_sq_impl<std::atto, P>;

	// If ConvType > T
	// (multiplying) T * (ConvType / T)
	// else ConvType < T
	// (dividing) T * (T / ConvType)
    
    constexpr kilometer_sq<long double> operator ""_km2(long double val) {
		return static_cast<kilometer_sq<long double>>(val);
	}
    constexpr meter_sq<long double>  operator ""_m2(long double val) {
		return static_cast<meter_sq<long double>>(val);
	}
	constexpr centimeter_sq<long double> operator ""_cm2(long double val) {
		return static_cast<centimeter_sq<long double>>(val);
	}
    constexpr millimeter_sq<long double> operator ""_mm2(long double val) {
		return static_cast<millimeter_sq<long double>>(val);
	}
    constexpr micrometer_sq<long double> operator ""_um2(long double val) {
		return static_cast<micrometer_sq<long double>>(val);
	}
	constexpr nanometer_sq<long double> operator ""_nm2(long double val) {
		return static_cast<nanometer_sq<long double>>(val);
	}
    constexpr picometer_sq<long double> operator ""_pm2(long double val) {
		return static_cast<picometer_sq<long double>>(val);
	}

	constexpr kilometer_sq<unsigned long long> operator ""_km2(unsigned long long val) {
		return static_cast<kilometer_sq<unsigned long long>>(val);
	}
    constexpr meter_sq<unsigned long long>  operator ""_m2(unsigned long long val) {
		return static_cast<meter_sq<unsigned long long>>(val);
	}
	constexpr centimeter_sq<unsigned long long> operator ""_cm2(unsigned long long val) {
		return static_cast<centimeter_sq<unsigned long long>>(val);
	}
    constexpr millimeter_sq<unsigned long long> operator ""_mm2(unsigned long long val) {
		return static_cast<millimeter_sq<unsigned long long>>(val);
	}
    constexpr micrometer_sq<unsigned long long> operator ""_um2(unsigned long long val) {
		return static_cast<micrometer_sq<unsigned long long>>(val);
	}
	constexpr nanometer_sq<unsigned long long> operator ""_nm2(unsigned long long val) {
		return static_cast<nanometer_sq<unsigned long long>>(val);
	}
    constexpr picometer_sq<unsigned long long> operator ""_pm2(unsigned long long val) {
		return static_cast<picometer_sq<unsigned long long>>(val);
	}
}

#endif // BOOST_TMP_AREA_HPP_INCLUDED