//  Copyright 2023 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#if defined(__GNUC__) || defined(__clang__) || !defined(ENABLE_CPP_MODULE)
#include "Boost.TMP.Base.hpp"
#include "Boost.NTTMP.hpp"

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#else //
import Boost.TMP;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER
#endif //

// Test helpers
namespace boost::tmp::test {

	template<auto V>
	using IsEvenV = bool_<V % 2 == 0>;

	template<typename T>
	concept IsTrue = std::same_as<T, true_>;

	template<typename T>
	concept IsFalse = std::same_as<T, false_>;

	template<typename T>
	concept IsEmptyValueList = std::same_as<T, list_v_<>>;

} // namespace boost::tmp::test

using namespace boost::tmp;


// TODO: Place StrLit somewhere.
// namespace array_into_list_tests {

// 	static constexpr std::array<int, 5> Arr1{1, 2, 3, 4, 5};
// 	static constexpr auto str = StrLit{"nameless"};

// 	template <typename T>
// 	    requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>)
// 	struct ArrayNowParamPack;

// 	using array_into_list_test_1 = ArrayNowParamPack<call_v_<lift_v_<array_into_list_>, Arr1>>;

// } // namespace array_into_list_tests

namespace all_of_v_tests {

	template<test::IsTrue T>
	struct AllAreEven;

	using all_of_v_test_1 = AllAreEven<call_v_<all_of_v_<lift_v_<test::IsEvenV>>, 2, 4, 6>>;

	template<test::IsFalse T>
	struct NotAllEven;

	using all_of_v_test_2 = NotAllEven<call_v_<all_of_v_<lift_v_<test::IsEvenV>>, 2, 1, 4, 3>>;

	template<test::IsFalse T>
	struct NoneAreEven;

	using all_of_v_test_3 = NoneAreEven<call_v_<all_of_v_<lift_v_<test::IsEvenV>>, 1, 3, 5, 9>>;

	// NOTE: In order to give expected behavior, an empty VPP input to all_of_v_ will result
	// in all_of_v_ returning true_; mirroring what is returned in the std algorithm version
	// of all_of.
	template<test::IsTrue T>
	struct EmptyListResultIsTrue;

	using all_of_v_test_4 = EmptyListResultIsTrue<call_v_<all_of_v_<lift_v_<test::IsEvenV>>>>;

} // namespace all_of_v_tests

namespace and_v_tests {

	template<test::IsTrue T>
	struct AllEvenNumbers;

	using and_v_test_1 = AllEvenNumbers<call_v_<and_v_<lift_v_<test::IsEvenV>>, 2, 4, 6>>;

	template<test::IsFalse T>
	struct AllEvenFalse;

	using and_v_test_2 = AllEvenFalse<call_v_<and_v_<lift_v_<test::IsEvenV>>, 2, 4, 8, 1>>;

} // namespace and_v_tests

namespace any_of_v_tests {

	template<test::IsTrue T>
	struct OneEvenNumber;

	using any_of_test_1 = OneEvenNumber<call_v_<any_of_v_<lift_v_<test::IsEvenV>>, 1, 3, 5, 8>>;

	template<test::IsFalse T>
	struct NoEvenNumbers;

	using any_of_test_2 = NoEvenNumbers<call_v_<any_of_v_<lift_v_<test::IsEvenV>>, 1, 3, 5, 9>>;

	template<test::IsTrue T>
	struct AllEvenNumbers;

	using any_of_test_3 = AllEvenNumbers<call_v_<any_of_v_<lift_v_<test::IsEvenV>>, 2, 4, 8, 12>>;

	template<test::IsFalse T>
	struct EmptyList;

	using any_of_test_4 = EmptyList<call_v_<any_of_v_<lift_v_<test::IsEvenV>>>>;

} // namespace any_of_v_tests

namespace contains_v_tests {

	template<test::IsTrue T>
	struct DoesContainNine;

	using contains_v_test_1 = DoesContainNine<call_v_<contains_v_<9>, 1, 3, 5, 9>>;

	template<test::IsFalse T>
	struct DoesNotContainSeven;

	using contains_v_test_2 = DoesNotContainSeven<call_v_<contains_v_<7>, 1, 3, 5, 9>>;

	template<test::IsFalse T>
	struct EmptyPackContainsNoNumbers_EvaluatesFalse;

	using contains_v_test_3 = EmptyPackContainsNoNumbers_EvaluatesFalse<call_v_<contains_v_<3>>>;

	template<test::IsFalse T>
	struct DoesNotContainTwo_AmorphousValues;

	using contains_v_tests_4 = DoesNotContainTwo_AmorphousValues<call_v_<contains_v_<2>, '3', 4, 1, char(2)>>;

} // namespace contains_v_tests

namespace drop_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<1>>)
	struct DropOneValueFromPack;

	using drop_v_test_1 = DropOneValueFromPack<call_v_<drop_v_<1>, 0, 1>>;

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2>>)
	struct DropZeroValuesFromPack;

	using drop_v_test_2 = DropZeroValuesFromPack<call_v_<drop_v_<0>, 1, 2>>;

	template<test::IsEmptyValueList T>
	struct DropAllValuesFromPack;

	using drop_v_test_3 = DropAllValuesFromPack<call_v_<drop_v_<3>, 0, 2, 4>>;

} // namespace drop_v_tests

namespace drop_last_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2>>)
	struct DropLastThreeNumbers;

	using drop_last_v_test_1 = DropLastThreeNumbers<call_v_<drop_last_v_<3>, 1, 2, 3, 4, 5>>;

	template<test::IsEmptyValueList T>
	struct DropAllNumbers;

	using drop_last_v_test_2 = DropAllNumbers<call_v_<drop_last_v_<4>, 0, 42, 3, 8>>;

} // namespace drop_last_v_tests

namespace each_v_tests {
	
	template<typename T> requires(std::same_as<T, list_v_<1, 30>>)
	struct EachValueGetsOwnFunction;

	template<auto V>
	struct add_some {
		template<auto V0>
		using f = list_v_<V + V0>;
	};

	using each_v_test_1 = EachValueGetsOwnFunction<call_v_<each_v_<lift_v_<add_some<1>::template f>,
																   lift_v_<add_some<20>::template f>,
																   join_v_<>>, 0, 10>>;

} // namespace each_v_tests

namespace erase_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<2, 3>>)
	struct EraseFirstElement;

	using erase_test_1 = EraseFirstElement<call_v_<erase_v_<0>, 1, 2, 3>>;

	// Erasing an element from a list with a single element will always result in empty list.
	template <test::IsEmptyValueList T>
	struct EraseSingleElementPack;

	using erase_test_2 = EraseSingleElementPack<call_v_<erase_v_<0>, 0>>;

	// UNDER RECONSIDERATION: Returns list_v_<nothing_{}> if no input is given.
	template <typename T>
	    requires(std::same_as<T, list_v_<nothing_{}>>)
	struct EraseEmptyPackReturnsNothingValue;

	using erase_test_3 = EraseEmptyPackReturnsNothingValue<call_v_<erase_v_<0>>>;

} // namespace erase_tests

namespace filter_v_tests {

	template<typename T>
		requires(std::same_as<T, list_v_<2, 4, 6, 8, 10>>)
	struct FilterOutOddValues;

	using filter_test_1 = FilterOutOddValues<call_v_<filter_v_<lift_v_<test::IsEvenV>>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>>;

}

namespace find_if_not_v_tests {

	template<typename T> requires(std::same_as<T, sizet_<3>>)
	struct FindIfNot_OddNumberAtIndexThree;

	using find_if_not_test_1 = FindIfNot_OddNumberAtIndexThree<call_v_<find_if_not_v_<lift_v_<test::IsEvenV>>, 2, 4, 6, 9>>;

} // namespace find_if_not_v_tests

// TODO: finish find_v_
/*
namespace find_v_tests {

template<typename T> requires(std::same_as<T, list_v_<4>>)
struct FindNumberOne;

using find_v_test_1 = FindNumberOne<call_v_<find_v_<default_type_lookup_table_>, 3>>;

} // namespace find_v_tests
*/

namespace fold_v_tests {

	template <typename T> requires(std::same_as<T, list_v_<20>>)
	struct FoldLeftValuesTo20;

	template<auto V>
	struct adder_ {
		template<auto U>
		using f = list_v_<V + U>;
	};

	template<typename TV, auto U>
	using add_in = call_<unpack_v_<lift_v_<adder_<U>::template f>>, TV>;

	using fold_left_v_test_1 =
	        FoldLeftValuesTo20<call_tv_<fold_left_v_<lift_tv_<add_in>>, list_v_<1>, 9, 10>>;

} // namespace fold_v_tests

namespace if_v_tests {

	template<typename T> requires(std::same_as<T, int_<99>>)
	struct NineReturnsNinetyNine;

	using if_v_test_1 = NineReturnsNinetyNine<call_v_<if_v_<is_v_<9>, always_v_<99, typify_default_>, always_v_<4, typify_default_>>, 9>>;

	template<typename T> requires(std::same_as<T, int_<4>>)
	struct AnythingElseReturnsFour;

	using if_v_test_2 = AnythingElseReturnsFour<call_v_<if_v_<is_v_<9>, always_v_<99, typify_default_>, always_v_<4, typify_default_>>, 'l'>>;

} // namespace if_v_tests

namespace index_v_tests {
	
	template<typename T> requires(std::same_as<T, int_<9>>)
	struct AtIndexTwo;

	using index_v_test_1 = AtIndexTwo<call_v_<iv2_<typify_default_>, 1, 4, 9, 10>>;

	template<typename T> requires(std::same_as<T, int_<2>>)
	struct AtUnpackedIndexTen;

	using index_v_test_2 = AtUnpackedIndexTen<call_<unpack_index_v_<10, typify_default_>, list_v_<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 2>>>;

} // namespace index_v_tests

namespace insert_v_tests {

	// Insert char_<'c'> at position 1
	template <typename T>
	    requires(std::same_as<T, list_v_<1, 'c', 2>>)
	struct Insert_C_AtPositionOne;

	using insert_test_1 =
	        Insert_C_AtPositionOne<call_v_<insert_v_<1, 'c'>, 1, 2>>;

	// Insert char_<'c'> at position 0
	template <typename T>
	    requires(std::same_as<T, list_v_<'c', 1, 2>>)
	struct Insert_C_AtPositionZero;

	using insert_test_2 =
	        Insert_C_AtPositionZero<call_v_<insert_v_<0, 'c'>, 1, 2>>;

	// Insert char_<'c'> at position 2
	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2, 'c'>>)
	struct Insert_C_AtPositionTwo;

	using insert_test_3 =
	        Insert_C_AtPositionTwo<call_v_<insert_v_<2, 'c'>, 1, 2>>;

	// Insert char_<'c'> into no list (returns a list_ with char_<'c'> in it)
	template <typename T>
	    requires(std::same_as<T, list_v_<'c'>>)
	struct EmptyPackInsertionReturnsSingleElementList;

	using insert_test_4 =
	        EmptyPackInsertionReturnsSingleElementList<call_v_<insert_v_<0, 'c'>>>;

} // namespace insert_v_tests

namespace is_v_tests {

	template<test::IsTrue T>
	struct ValueIsFive;

	using is_v_test_1 = ValueIsFive<call_v_<is_v_<5, typify_default_>, 5>>;

	template<test::IsFalse T>
	struct ValueCharCIsNotInt99;

	using is_v_test_2 = ValueCharCIsNotInt99<call_v_<is_v_<99, typify_default_>, 'c'>>;

} // namespace is_v_tests

namespace is_not_v_tests {

	template<test::IsTrue T>
	struct ValueIsNotFive_EvaluatesTrue;

	using is_not_v_test_1 = ValueIsNotFive_EvaluatesTrue<call_v_<is_not_v_<5, typify_default_>, 2>>;

	template<test::IsFalse T>
	struct ValueIsNine_EvaluatesFalse;

	using is_not_v_test_2 = ValueIsNine_EvaluatesFalse<call_v_<is_not_v_<9, typify_default_>, 9>>;

} // namespace is_v_tests

// TODO: Joining amorphous types and values i.e. 
// list_v_<1>, 1, 'c', list_v_<3> -> list_v_<1, 1, 'c', 3>
namespace join_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	struct JoinLists123;

	// Notice the use of call_ here, and *not* call_v_.
	// While we are dealing with combining values, types are being used to ferry the values.
	using join_v_test_1 = JoinLists123<call_<join_v_<>, list_v_<1>, list_v_<2>, list_v_<3>>>;

} // namespace join_v_tests

namespace map_value_tests {

	template<test::IsFalse T>
	struct FalseValueToFalseType;

	using map_value_test_1 = FalseValueToFalseType<call_v_<map_value_<default_type_lookup_table_>, false>>;

	template<test::IsTrue T>
	struct TrueValueToTrueType;

	using map_value_test_2 = TrueValueToTrueType<call_v_<map_value_<default_type_lookup_table_>, true>>;

	template<typename T> requires(std::same_as<T, sizet_<3>>)
	struct SizeValueToSizeType;

	using map_value_test_3 = SizeValueToSizeType<call_v_<map_value_<default_type_lookup_table_>, std::size_t(3)>>;

	template<typename T> requires(std::same_as<T,
	list_<
		int_<1>,
		char_<'c'>
	>>)
	struct TypifyMultipleValues;
	
	using map_value_test_4 = TypifyMultipleValues<call_v_<transform_v_<map_value_<default_type_lookup_table_>>, 1, char('c')>>;

} // namespace map_value_tests

namespace none_of_v_tests {

	template<test::IsTrue T>
	struct NoneOfTheNumbersAreEven;

	using none_of_v_test_1 = NoneOfTheNumbersAreEven<call_v_<none_of_v_<lift_v_<test::IsEvenV>>, 1, 3, 5, 9>>;

	template<test::IsFalse T>
	struct SomeNumbersAreEven;

	using none_of_v_test_2 = SomeNumbersAreEven<call_v_<none_of_v_<lift_v_<test::IsEvenV>>, 2, 1, 3, 7, 9, 10>>;

	template<test::IsTrue T>
	struct EmptyList;

	using none_of_v_test_3 = EmptyList<call_v_<none_of_v_<lift_v_<test::IsEvenV>>>>;

} // namespace none_of_tests

namespace not_v_tests {

	template<test::IsTrue T>
	struct ValueIsNotFalse_EvaluatesTrue;

	using not_v_test_1 = ValueIsNotFalse_EvaluatesTrue<call_v_<not_v_<typify_default_>, false>>;

	template<test::IsFalse T>
	struct ValueIsNotTrue_ResultsFalse;

	using not_v_test_2 = ValueIsNotTrue_ResultsFalse<call_v_<not_v_<typify_default_>, true>>;

} // namespace not_v_tests

namespace or_v_tests {

	template<test::IsTrue T>
	struct AtLeastOneEven_EvaluatesTrue;

	using or_v_test_1 = AtLeastOneEven_EvaluatesTrue<call_v_<or_v_<lift_v_<test::IsEvenV>>, 1, 3, 5, 6>>;

	template<test::IsFalse T>
	struct NoEvenNumbers_EvaluatesFalse;

	using or_v_test_2 = NoEvenNumbers_EvaluatesFalse<call_v_<or_v_<lift_v_<test::IsEvenV>>, 1, 11, 19, 71>>;

} // namespace or_v_tests

namespace pop_back_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	struct PopTheFourOffBack;

	using pop_back_test_1 = PopTheFourOffBack<call_v_<pop_back_v_<>, 1, 2, 3, 4>>;

	template<typename T> requires(std::same_as<T, list_v_<>>)
	struct PopOnlyValue;

	using pop_back_test_2 = PopOnlyValue<call_v_<pop_back_v_<>, 1>>;

	// TODO: Should this be the default behavior for no value?
	template<typename T> requires(std::same_as<T, list_v_<nothing_{}>>)
	struct PopNoValue;

	using pop_back_test_3 = PopNoValue<call_v_<pop_back_v_<>>>;

} // namespace pop_back_v_tests

namespace pop_front_v_tests {
		
	template<typename T> requires(std::same_as<T, list_v_<2, 3, 4, 5>>)
	struct PopOneOff;

	using pop_front_v_test_1 = PopOneOff<call_v_<pop_front_v_<>, 1, 2, 3, 4, 5>>;

	template<typename T> requires(std::same_as<T, list_v_<nothing_{}>>)
	struct PopEmptyList;

	using pop_front_v_test_2 = PopEmptyList<call_v_<pop_front_v_<>>>;

	template<typename T> requires(std::same_as<T, list_v_<>>)
	struct PopSingleElement;

	using pop_front_v_test_3 = PopSingleElement<call_v_<pop_front_v_<>, 1>>;

} // namespace pop_front_v_tests

namespace push_front_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<4, 1, 2, 3>>)
	struct Push4ToFront;

	using push_front_v_test_1 = Push4ToFront<call_v_<push_front_v_<4>, 1, 2, 3>>;

	template<typename T> requires(std::same_as<T, list_v_<4>>)
	struct Push4ToFrontOfNoList;

	using push_front_v_test_2 = Push4ToFrontOfNoList<call_v_<push_front_v_<4>>>;

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	struct PushNothingToFront;

	using push_front_v_test_3 = PushNothingToFront<call_v_<push_front_v_<>, 1, 2, 3>>;

} // namespace push_front_v_tests

namespace range_lo_hi_v_tests {

	template<test::IsFalse T>
	struct OutsideOf5To10;

	using range_lo_hi_v_test_1 = OutsideOf5To10<call_v_<range_lo_hi_v_<5, 10, typify_default_>, 7>>;

} // namespace range_lo_hi_v_tests

namespace reverse_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<9, 8, 7, 6, 5, 4, 3, 2, 1, 0>>)
	struct ReverseNineV;

    using reverse_v_test_1 = ReverseNineV<call_v_<reverse_v_<>, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>>;

	template <typename T>
	    requires(std::same_as<T, list_v_<15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0>>)
	struct Reverse17V;

    using reverse_v_test_2 = Reverse17V<call_v_<reverse_v_<>, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>>;

	template<test::IsEmptyValueList T>
	struct ReverseEmptyValuePack;

	using reverse_v_test_3 = ReverseEmptyValuePack<call_v_<reverse_v_<>>>;

} // namespace reverse_v_tests

namespace rotate_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<1, 3, 2>>)
	struct OneThreeTwo;

	using rotate_v_test_1 = OneThreeTwo<call_v_<rotate_v_<2>, 3, 2, 1>>;

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	struct NoRotation;

	using rotate_v_test_2 = NoRotation<call_v_<rotate_v_<0>, 1, 2, 3>>;

	template<typename T> requires(std::same_as<T, list_v_<2, 3, 1>>)
	struct RotateAround;

	// Equivalent to rotate_v_<1>
	using rotate_v_test_3 = RotateAround<call_v_<rotate_v_<7>, 1, 2, 3>>;

} // namespace rotate_v_tests

namespace sequence_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<1, 1, 1, 1, 1,
														  1, 1, 1, 1, 1>>)
	struct RepeatTenOnes;

	using sequence_v_test_1 = RepeatTenOnes<call_v_<repeat_sequence_v_<10>, 1>>;

	template<test::IsEmptyValueList T>
	struct RepeatZeroOnes;

	using sequence_v_test_2 = RepeatZeroOnes<call_v_<repeat_sequence_v_<0>, 1>>;

} // namespace sequence_v_tests

namespace size_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<std::size_t{3}>>)
	struct ThreeValuesInPack;

	using size_v_test_1 = ThreeValuesInPack<call_v_<size_v_<>, 1, 2, 3>>;

	template<typename T> requires(std::same_as<T, list_v_<std::size_t{0}>>)
	struct ZeroValuesInPack;

	using size_v_test_2 = ZeroValuesInPack<call_v_<size_v_<>>>;

} // namespace size_v_tests

namespace swap_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 0>>)
	struct SwapZeroOne;

	using swap_v_test_1 = SwapZeroOne<call_v_<swap_v_<>, 0, 1>>;

	template<typename T> requires(std::same_as<T, list_v_<'d', 3>>)
	struct SwapUnrelatedValues;

	using swap_v_test_2 = SwapUnrelatedValues<call_v_<swap_v_<>, 3, 'd'>>;

} // namespace swap_v_tests

namespace take_v_tests {
	template <typename T>
	    requires(std::same_as<T, list_v_<1>>)
	struct TakeVFirstElement_One;

	using take_v_test_1 = TakeVFirstElement_One<call_v_<take_v_<1>, 1, 2, 3>>;

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2>>)
	struct TakeVFirstTwoElements_OneTwo;

	using take_v_test_2 = TakeVFirstTwoElements_OneTwo<call_v_<take_v_<2>, 1, 2, 3>>;

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	struct TakeMoreThanListContains;

	using take_v_test_3 = TakeMoreThanListContains<call_v_<take_v_<5>, 1, 2, 3>>;

} // namespace take_v_tests

namespace take_last_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<4, 5, 6>>)
	struct LastThreeOfSeries;

	using take_last_v_test_1 = LastThreeOfSeries<call_v_<take_last_v_<3>, 1, 2, 3, 4, 5, 6>>;

	template<test::IsEmptyValueList T>
	struct TakeNoLastElements;

	using take_last_v_test_2 = TakeNoLastElements<call_v_<take_last_v_<0>, 1, 2, 3, 4>>;

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	struct TakeAllElements;

	using take_last_v_test_3 = TakeAllElements<call_v_<take_last_v_<3>, 1, 2, 3>>;

// Test here fails (as it should):
// template<typename T> requires(std::same_as<T, list_v_<1, 2, 3, 4>>)
// struct TakePastElementCount;

// using take_last_v_test_4 = TakePastElementCount<call_v_<take_last_v_<5>, 1, 2, 3, 4>>;

} // namespace take_last_v_tests

namespace tee_v_tests {

	template<typename T> requires(std::same_as<T, list_v_<1, 2, 3, 1, 2, 3>>)
	struct MakePattern_123123;

	using tee_v_test_1 = MakePattern_123123<call_v_<tee_v_<listify_v_, listify_v_, join_v_<>>, 1, 2, 3>>;

} // namespace tee_v_tests

namespace transform_v_tests {

	// template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
	// struct AddOneToEach;

	// template<auto V>
	// using add_one = call_v_<typify_default_, V + 1>;

	// using transform_v_test_1 = AddOneToEach<call_v_<transform_v_<lift_v_<add_one>, as_values_<>>, 0, 1, 2>>;

} // namespace transform_v_tests
