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
/*
 *
 * typename dispatch<find_dispatch(sizeof...(Ts)),
                            drop_<usizet_<64>,make_binary_tree<
                                F,
                                lift_<tree::balance_tree64>,
                                typename
dispatch<find_dispatch(sizeof...(Ts)),take_<usizet_<64>,make_binary_tree<F>>>::template f<Ts...>
                        >>>::template f<Ts...>

boost::detail::tree::node<
    boost::detail::tree::node<
        boost::detail::tree::left_node<
            boost::detail::tree::leaf_node<
                boost::sizet_<1>
            >,
            boost::sizet_<2>
        >,
        boost::sizet_<3>,
        boost::detail::tree::node<
            boost::detail::tree::node<
                boost::detail::tree::node<
                    boost::detail::tree::right_node<
                        boost::sizet_<4>,
                        boost::detail::tree::left_node<
                             boost::detail::tree::right_node<
                                 boost::sizet_<5>,
                                     boost::detail::tree::leaf_node<boost::sizet_<6> >
                                 >,
                                 boost::sizet_<7>
                             >
                         >,
                         boost::sizet_<8>,
                         boost::detail::tree::right_node<
                             boost::sizet_<9>,
                             boost::detail::tree::node<
                                 boost::detail::tree::left_node<
                                     boost::detail::tree::leaf_node<boost::sizet_<10> >,
                                     boost::sizet_<11>
                                 >,
                             boost::sizet_<12>,
                         boost::detail::tree::leaf_node<boost::sizet_<13> >
                     >
                 >
             >,
             'Äboost::sizet_<14>,
boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::sizet_<15> >, boost::sizet_<16> >
>, boost::sizet_<17>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::leaf_node<boost::sizet_<18>
>, boost::sizet_<19>, boost::detail::tree::right_node<boost::sizet_<20>,
boost::detail::tree::right_node<boost::sizet_<21>, boost::detail::tree::leaf_node<boost::sizet_<22> >
> > >, boost::sizet_<23>, boost::detail::tree::node<boost::detail::tree::leaf_node<boost::sizet_<24>
>, boost::sizet_<25>, boost::detail::tree::leaf_node<boost::sizet_<26> > > > > >, boost::sizet_<27>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<28>,
boost::detail::tree::right_node<boost::sizet_<29>, boost::detail::tree::leaf_node<boost::sizet_<30> >
> >, boost::sizet_<31>, boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<32>,
boost::detail::tree::leaf_node<boost::sizet_<33> > >, boost::sizet_<34>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<35>,
boost::detail::tree::right_node<boost::sizet_<36>,
boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::sizet_<37> >, boost::sizet_<38> >
> >, boost::sizet_<39>, boost::detail::tree::leaf_node<boost::sizet_<40> > >, boost::sizet_<41> >,
boost::sizet_<42> >, boost::sizet_<43> >, boost::sizet_<44>,
boost::detail::tree::node<boost::detail::tree::leaf_node<boost::sizet_<45> >, boost::sizet_<46>,
boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<47>,
boost::detail::tree::leaf_node<boost::sizet_<48> > >, boost::sizet_<49>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::sizet_<50>
>, boost::sizet_<51> >, boost::sizet_<52>, boost::detail::tree::leaf_node<boost::sizet_<53> > > > > > >
>, boost::sizet_<54> >, boost::sizet_<55> >, boost::sizet_<56>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<57>,
boost::detail::tree::left_node<boost::detail::tree::right_node<boost::sizet_<58>,
boost::detail::tree::leaf_node<boost::sizet_<59> > >, boost::sizet_<60> > >, boost::sizet_<61>,
boost::detail::tree::leaf_node<boost::sizet_<62> > >, boost::sizet_<63>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<64>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::sizet_<65>
>, boost::sizet_<66> >, boost::sizet_<67>, boost::detail::tree::leaf_node<boost::sizet_<68> > > >,
boost::sizet_<69>, boost::detail::tree::right_node<boost::sizet_<70>,
boost::detail::tree::leaf_node<boost::sizet_<71> > > >, boost::sizet_<72>,
boost::detail::tree::leaf_node<boost::sizet_<73> > > >, boost::sizet_<74>,
boost::detail::tree::leaf_node<boost::sizet_<75> > >, boost::sizet_<76>,
boost::detail::tree::node<boost::detail::tree::right_node<boost::sizet_<77>,
boost::detail::tree::leaf_node<boost::sizet_<78> > >, boost::sizet_<79>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::leaf_node<boost::sizet_<80>
>, boost::sizet_<81>, boost::detail::tree::leaf_node<boost::sizet_<82> > >, boost::sizet_<83>,
boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::sizet_<84>
>, boost::sizet_<85> >, boost::sizet_<86> > > > > >, boost::sizet_<87>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::sizet_<88>
>, boost::sizet_<89> >, boost::sizet_<90> >, boost::sizet_<91>,
boost::detail::tree::leaf_node<boost::sizet_<92> > >, boost::sizet_<93> >, boost::sizet_<94>,
boost::detail::tree::node<boost::detail::tree::leaf_node<boost::sizet_<95> >, boost::sizet_<96>,
boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::leaf_node<boost::sizet_<97>
>, boost::sizet_<98>, boost::detail::tree::leaf_node<boost::sizet_<99> > >, boost::sizet_<100> > > > >
>'} to non-scalar type 'boost::call_<boost::make_sequence_<>, boost::usizet_<100> >' {aka
'boost::list_<boost::usizet_<0>, boost::usizet_<1>, boost::usizet_<2>, boost::usizet_<3>,
boost::usizet_<4>, boost::usizet_<5>, boost::usizet_<6>, boost::usizet_<7>, boost::usizet_<8>,
boost::usizet_<9>, boost::usizet_<10>, boost::usizet_<11>, boost::usizet_<12>, boost::usizet_<13>,
boost::usizet_<14>, boost::usizet_<15>, boost::usizet_<16>, boost::usizet_<17>, boost::usizet_<18>,
boost::usizet_<19>, boost::usizet_<20>, boost::usizet_<21>, boost::usizet_<22>, boost::usizet_<23>,
boost::usizet_<24>, boost::usizet_<25>, boost::usizet_<26>, boost::usizet_<27>, boost::usizet_<28>,
boost::usizet_<29>, boost::usizet_<30>, boost::usizet_<31>, boost::usizet_<32>, boost::usizet_<33>,
boost::usizet_<34>, boost::usizet_<35>, boost::usizet_<36>, boost::usizet_<37>, boost::usizet_<38>,
boost::usizet_<39>, boost::usizet_<40>, boost::usizet_<41>, boost::usizet_<42>, boost::usizet_<43>,
boost::usizet_<44>, boost::usizet_<45>, boost::usizet_<46>, boost::usizet_<47>, boost::usizet_<48>,
boost::usizet_<49>, boost::usizet_<50>, boost::usizet_<51>, boost::usizet_<52>, boost::usizet_<53>,
boost::usizet_<54>, boost::usizet_<55>, boost::usizet_<56>, boost::usizet_<57>, boost::usizet_<58>,
boost::usizet_<59>, boost::usizet_<60>, boost::usizet_<61>, boost::usizet_<62>, boost::usizet_<63>,
boost::usizet_<64>, boost::usizet_<65>, boost::usizet_<66>, boost::usizet_<67>, boost::usizet_<68>,
boost::usizet_<69>, boost::usizet_<70>, boost::usizet_<71>, boost::usizet_<72>, boost::usizet_<73>,
boost::usizet_<74>, boost::usizet_<75>, boost::usizet_<76>, boost::usizet_<77>, boost::usizet_<78>,
boost::usizet_<79>, boost::usizet_<80>, boost::usizet_<81>, boost::usizet_<82>, boost::usizet_<83>,
boost::usizet_<84>, boost::usizet_<85>, boost::usizet_<86>, boost::usizet_<87>, boost::usizet_<88>,
boost::usizet_<89>, boost::usizet_<90>, boost::usizet_<91>, boost::usizet_<92>, boost::usizet_<93>,
boost::usizet_<94>, boost::usizet_<95>, boost::usizet_<96>, boost::usizet_<97>, boost::usizet_<98>,
boost::usizet_<99> >'} requested
             _
             _

   call_<make_sequence_<>,usizet_<100>> r1 = call_<detail::make_binary_tree<lift_<less>>,sizet_<27>,
sizet_<87>, sizet_<3>, sizet_<56>, sizet_<76>, sizet_<94>, sizet_<17>, sizet_<74>, sizet_<55>, sizet_<96>,
sizet_<54>, sizet_<93>, sizet_<79>, sizet_<14>, sizet_<8>, sizet_<31>, sizet_<23>, sizet_<25>, sizet_<34>,
sizet_<9>, sizet_<44>, sizet_<63>, sizet_<4>, sizet_<72>, sizet_<46>, sizet_<49>, sizet_<7>, sizet_<100>,
sizet_<83>, sizet_<77>, sizet_<61>, sizet_<81>, sizet_<91>, sizet_<69>, sizet_<52>, sizet_<28>, sizet_<19>,
sizet_<57>, sizet_<64>, sizet_<75>, sizet_<2>, sizet_<62>, sizet_<43>, sizet_<42>, sizet_<5>, sizet_<16>,
sizet_<18>, sizet_<41>, sizet_<39>, sizet_<6>, sizet_<92>, sizet_<60>, sizet_<1>, sizet_<35>, sizet_<29>,
sizet_<51>, sizet_<12>, sizet_<36>, sizet_<24>, sizet_<53>, sizet_<11>, sizet_<32>, sizet_<67>, sizet_<58>,
sizet_<80>, sizet_<86>, sizet_<33>, sizet_<85>, sizet_<15>, sizet_<90>, sizet_<20>, sizet_<30>, sizet_<50>,
sizet_<98>, sizet_<99>, sizet_<70>, sizet_<21>, sizet_<95>, sizet_<73>, sizet_<78>, sizet_<26>, sizet_<38>,
sizet_<82>, sizet_<47>, sizet_<40>, sizet_<66>, sizet_<59>, sizet_<13>, sizet_<89>, sizet_<71>, sizet_<88>,
sizet_<37>, sizet_<22>, sizet_<84>, sizet_<10>, sizet_<97>, sizet_<68>, sizet_<65>, sizet_<48>,
sizet_<45>>{};


boost::list_<
        boost::sizet_<1>, boost::sizet_<1>, boost::sizet_<2>, boost::sizet_<2>, boost::sizet_<3>,
boost::sizet_<4>, boost::sizet_<5>, boost::sizet_<5>, boost::sizet_<6>, boost::sizet_<6>,
boost::sizet_<7>, boost::sizet_<8>, boost::sizet_<9>, boost::sizet_<10>, boost::sizet_<10>,
boost::sizet_<11>, boost::sizet_<11>, boost::sizet_<12>, boost::sizet_<12>, boost::sizet_<13>,
boost::sizet_<13>, boost::sizet_<14>, boost::sizet_<15>, boost::sizet_<16>, boost::sizet_<16>,
boost::sizet_<17>, boost::sizet_<18>, boost::sizet_<18>, boost::sizet_<19>, boost::sizet_<20>,
boost::sizet_<21>, boost::sizet_<22>, boost::sizet_<22>, boost::sizet_<23>, boost::sizet_<24>,
boost::sizet_<24>, boost::sizet_<25>, boost::sizet_<26>, boost::sizet_<27>, boost::sizet_<28>,
boost::sizet_<29>, boost::sizet_<29>, boost::sizet_<30>, boost::sizet_<31>, boost::sizet_<32>,
boost::sizet_<32>, boost::sizet_<33>, boost::sizet_<34>, boost::sizet_<35>, boost::sizet_<35>,
boost::sizet_<36>, boost::sizet_<36>, boost::sizet_<37>, boost::sizet_<37>, boost::sizet_<38>,
boost::sizet_<39>, boost::sizet_<39>, boost::sizet_<40>, boost::sizet_<40>, boost::sizet_<41>,
boost::sizet_<41>, boost::sizet_<42>, boost::sizet_<42>, boost::sizet_<43>, boost::sizet_<43>,
boost::sizet_<44>, boost::sizet_<45>, boost::sizet_<45>, boost::sizet_<46>, boost::sizet_<47>,
boost::sizet_<48>, boost::sizet_<48>, boost::sizet_<49>, boost::sizet_<50>, boost::sizet_<51>,
boost::sizet_<51>, boost::sizet_<52>, boost::sizet_<53>, boost::sizet_<53>, boost::sizet_<54>,
boost::sizet_<55>, boost::sizet_<56>, boost::sizet_<57>, boost::sizet_<58>, boost::sizet_<58>,
boost::sizet_<59>, boost::sizet_<59>, boost::sizet_<60>, boost::sizet_<60>, boost::sizet_<61>,
boost::sizet_<62>, boost::sizet_<62>, boost::sizet_<63>, boost::sizet_<64>, boost::sizet_<65>,
boost::sizet_<65>, boost::sizet_<66>, boost::sizet_<66>, boost::sizet_<67>, boost::sizet_<67>,
boost::sizet_<68>, boost::sizet_<68>, boost::sizet_<69>, boost::sizet_<70>, boost::sizet_<71>,
boost::sizet_<71>, boost::sizet_<72>, boost::sizet_<73>, boost::sizet_<74>, boost::sizet_<75>,
boost::sizet_<76>, boost::sizet_<77>, boost::sizet_<78>, boost::sizet_<79>, boost::sizet_<80>,
boost::sizet_<81>, boost::sizet_<82>, boost::sizet_<83>, boost::sizet_<84>, boost::sizet_<84>,
boost::sizet_<85>, boost::sizet_<86>, boost::sizet_<87>, boost::sizet_<88>, boost::sizet_<88>,
boost::sizet_<89>, boost::sizet_<89>, boost::sizet_<90>, boost::sizet_<91>, boost::sizet_<92>,
boost::sizet_<92>, boost::sizet_<93>, boost::sizet_<94>, boost::sizet_<95>, boost::sizet_<96>,
boost::sizet_<97>, boost::sizet_<97>, boost::sizet_<98>, boost::sizet_<99>, boost::sizet_<100> > >'


::tree::balance_tree64_impl<boost::list_<
        boost::sizet_<1>, boost::sizet_<2>, boost::sizet_<3>, boost::sizet_<4>, boost::sizet_<5>,
boost::sizet_<6>, boost::sizet_<7>, boost::sizet_<8>, boost::sizet_<9>, boost::sizet_<10>,
        boost::sizet_<11>, boost::sizet_<12>, boost::sizet_<13>, boost::sizet_<14>, boost::sizet_<15>,
boost::sizet_<16>, boost::sizet_<17>, boost::sizet_<18>, boost::sizet_<19>, boost::sizet_<20>,
        boost::sizet_<21>, boost::sizet_<22>, boost::sizet_<23>, boost::sizet_<24>, boost::sizet_<25>,
boost::sizet_<26>, boost::sizet_<27>, boost::sizet_<28>, boost::sizet_<29>, boost::sizet_<30>,
        boost::sizet_<31>, boost::sizet_<32>, boost::sizet_<33>, boost::sizet_<34>, boost::sizet_<35>,
boost::sizet_<36>, boost::sizet_<37>, boost::sizet_<38>, boost::sizet_<39>, boost::sizet_<40>,
        boost::sizet_<41>, boost::sizet_<42>, boost::sizet_<43>, boost::sizet_<44>, boost::sizet_<45>,
boost::sizet_<46>, boost::sizet_<47>, boost::sizet_<48>, boost::sizet_<49>, boost::sizet_<50>,
        boost::sizet_<51>, boost::sizet_<52>, boost::sizet_<53>, boost::sizet_<54>, boost::sizet_<55>,
boost::sizet_<56>, boost::sizet_<57>, boost::sizet_<58>, boost::sizet_<59>, boost::sizet_<60>,
        boost::sizet_<61>, boost::sizet_<62>, boost::sizet_<63>, boost::sizet_<64>, boost::sizet_<65>,
boost::sizet_<66>, boost::sizet_<67>, boost::sizet_<68>, boost::sizet_<69>, boost::sizet_<70>,
        boost::sizet_<71>, boost::sizet_<72>, boost::sizet_<73>, boost::sizet_<74>, boost::sizet_<75>,
boost::sizet_<76>, boost::sizet_<77>, boost::sizet_<78>, boost::sizet_<79>, boost::sizet_<80>,
        boost::sizet_<81>, boost::sizet_<82>, boost::sizet_<83>, boost::sizet_<84>, boost::sizet_<85>,
boost::sizet_<86>, boost::sizet_<87>, boost::sizet_<88>, boost::sizet_<89>, boost::sizet_<90>,
        boost::sizet_<91>, boost::sizet_<92>, boost::sizet_<93>, boost::sizet_<94>, boost::sizet_<95>,
boost::sizet_<96>, boost::sizet_<97>, boost::sizet_<98>, boost::sizet_<99>, boost::sizet_<100> > >'

 */
