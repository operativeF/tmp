//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include <iostream>
#include "test_util.hpp"

namespace all_of_test {

	// Enable empty base class optimization with multiple inheritance on Visual Studio.
	#if defined(_MSC_VER) && _MSC_VER >= 1910
	#  define FLUENT_EBCO __declspec(empty_bases)
	#else
	#  define FLUENT_EBCO
	#endif
	
	template<typename T>
	using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

	template <typename T, typename Parameter, template<typename> class... Skills>
	class FLUENT_EBCO NamedType : public Skills<NamedType<T, Parameter, Skills...>>...
	{
	public:
		using UnderlyingType = T;
		
		// constructor
		explicit constexpr NamedType(T const& value) : value_(value) {}
		template<typename T_ = T, typename = IsNotReference<T_>>
		explicit constexpr NamedType(T&& value) : value_(std::move(value)) {}
		
		// get
		constexpr auto& get() { return value_; }
		constexpr std::remove_reference_t<T> const& get() const {return value_; }

		// conversions
		using ref = NamedType<T&, Parameter, Skills...>;
		operator ref ()
		{
			return ref(value_);
		}
		
		struct argument
		{
			template<typename U>
			NamedType operator=(U&& value) const
			{
				return NamedType(std::forward<U>(value));
			}
			argument() = default;
			argument(argument const&) = delete;
			argument(argument &&) = delete;
			argument& operator=(argument const&) = delete;
			argument& operator=(argument &&) = delete;
		};
		
	private:
		T value_;
	};

	template<template<typename T> class StrongType, typename T>
	constexpr StrongType<T> make_named(T const& value)
	{
		return StrongType<T>(value);
	}
    template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	template<typename T, typename U>
	using same_as = std::is_same<T, U>;

	template <typename T, template<typename...> class crtpType>
	struct crtp
	{
		T& underlying() { return static_cast<T&>(*this); }
		T const& underlying() const { return static_cast<T const&>(*this); }
	};

	template <typename T>
	struct Printable : crtp<T, Printable>
	{
		void print(std::ostream& os) const { os << this->underlying().get(); }
	};

	template <typename T, typename Parameter, template<typename> class... Skills>
	std::ostream& operator<<(std::ostream& os, NamedType<T, Parameter, Skills...> const& object)
	{
		object.print(os);
		return os;
	}

	template<typename T, typename U>
	struct composite_;

	template <typename T>
	struct Multiplicable : crtp<T, Multiplicable>
	{
		template<typename U>
		typename composite_<T, U>::type operator*(U const& other) const { return composite_<T, U>::type(this->underlying().get() * other.get()); }
	};

	template <typename T>
	struct Addable : crtp<T, Addable>
	{
		T operator+(T const& other) const { return T(this->underlying().get() + other.get()); }
	};


	using Meter = NamedType<double, struct MeterParameter, Printable, Multiplicable, Addable>;
	using Meter_2 = NamedType<double, struct Meter2Parameter, Printable, Addable>;

	template<typename T, typename U>
	struct composite_ {
		using type = call_<if_<is_<same_as<T, U>>, always_<Meter>, always_<Meter_2>>, identity_>;
	};

	struct PreIncrementable
	{
		template<typename T, typename U>
		typename composite_<T, U>::type voila(T a, U b) { return a * b; }
	};

	Meter operator"" _meter(unsigned long long value) { return Meter(value); }
	Meter_2 operator"" _meter_2(unsigned long long value) { return Meter_2(value); }
	Meter operator"" _meter(long double value) { return Meter(value); }
	Meter_2 operator"" _meter_2(long double value) { return Meter_2(value); }

	using Width = NamedType<Meter, struct WidthParameter>;
	using Height = NamedType<Meter, struct HeightParameter, Multiplicable>;
	using Area = NamedType<Meter_2, struct AreaParameter>;

	template<typename T>
	using MultiplicableType = NamedType<T, struct MultiplicableTag, Multiplicable, Printable>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;

	class Rectangle
	{
	public:
		Rectangle(Width width, Height height) : width_(width.get()), height_(height.get()) {}
		Meter getWidth() const { return width_; }
		Meter getHeight() const { return height_; }
		auto getArea() const { return typename composite_<decltype(width_), decltype(height_)>::type(width_ * height_); }
	private:
		Meter width_;
		Meter height_;
		Area area_ = Area(0_meter_2);
	};


	int run() {

		//PreIncrementable pe;
		//auto num = pe.voila(2.1, 10);

		Rectangle me(Width(10.124_meter), Height(10.014_meter));
		Rectangle be(Width(10_meter), Height(10_meter));

		auto num_be = (me.getHeight() * me.getWidth()).get();

		auto num_bek = be.getHeight() * be.getHeight(); // Messy type; not evaluated yet

		auto num_area = me.getArea() + be.getArea();

		//std::cout << num << '\n';
		std::cout << num_be << '\n';
		std::cout << num_bek << '\n';
		std::cout << num_area << '\n';


        bool_<true>{} = call_<unpack_<all_of_<lift_<is_even>>>, alist>{};
		return 0;
	}
} // namespace all_of_test