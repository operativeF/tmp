//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Sort;

import Boost.TMP;

using namespace boost::tmp;

export namespace sort_test {
	template <typename T, typename U>
	using less = bool_<(T::value < U::value)>;

	template <typename T, typename U>
	using push_ = typename T::template push<U, less>;
	int run() {
		list_<sizet_<0>, sizet_<1>, sizet_<2>>{} =
		        call_<sort_<lift_<less>>, sizet_<1>, sizet_<0>, sizet_<2>>{};
		call_<make_sequence_<>, sizet_<100>>{} =
		        call_<sort_<lift_<less>>, sizet_<0>, sizet_<27>, sizet_<87>, sizet_<3>, sizet_<56>,
		              sizet_<76>, sizet_<94>, sizet_<17>, sizet_<74>, sizet_<55>, sizet_<96>, sizet_<54>,
		              sizet_<93>, sizet_<79>, sizet_<14>, sizet_<8>, sizet_<31>, sizet_<23>, sizet_<25>,
		              sizet_<34>, sizet_<9>, sizet_<44>, sizet_<63>, sizet_<4>, sizet_<72>, sizet_<46>,
		              sizet_<49>, sizet_<7>, sizet_<83>, sizet_<77>, sizet_<61>, sizet_<81>, sizet_<91>,
		              sizet_<69>, sizet_<52>, sizet_<28>, sizet_<19>, sizet_<57>, sizet_<64>, sizet_<75>,
		              sizet_<2>, sizet_<62>, sizet_<43>, sizet_<42>, sizet_<5>, sizet_<16>, sizet_<18>,
		              sizet_<41>, sizet_<39>, sizet_<6>, sizet_<92>, sizet_<60>, sizet_<1>, sizet_<35>,
		              sizet_<29>, sizet_<51>, sizet_<12>, sizet_<36>, sizet_<24>, sizet_<53>, sizet_<11>,
		              sizet_<32>, sizet_<67>, sizet_<58>, sizet_<80>, sizet_<86>, sizet_<33>, sizet_<85>,
		              sizet_<15>, sizet_<90>, sizet_<20>, sizet_<30>, sizet_<50>, sizet_<98>, sizet_<99>,
		              sizet_<70>, sizet_<21>, sizet_<95>, sizet_<73>, sizet_<78>, sizet_<26>, sizet_<38>,
		              sizet_<82>, sizet_<47>, sizet_<40>, sizet_<66>, sizet_<59>, sizet_<13>, sizet_<89>,
		              sizet_<71>, sizet_<88>, sizet_<37>, sizet_<22>, sizet_<84>, sizet_<10>, sizet_<97>,
		              sizet_<68>, sizet_<65>, sizet_<48>, sizet_<45>>{};

		return 0;
	}
} // namespace sort_test
