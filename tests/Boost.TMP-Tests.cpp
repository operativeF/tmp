//  Copyright 2018-2019 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#if defined(__GNUC__) || defined(__clang__) || !defined(ENABLE_CPP_MODULE)
#include "Boost.TMP.Base.hpp"
#include "Boost.TMP.hpp"

#include <array>
#include <concepts>
#include <cstdint>
#include <type_traits>
#else //
import Boost.TMP;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER
#endif //

namespace boost::tmp::test {

	template <typename T, typename U>
	using add_pair = int_<T::value + U::value>;

	template <typename T>
	using is_even = bool_<T::value % 2 == 0>;

	template <typename T>
	using greater_than_two = bool_<(T::value > 2)>;

	template <typename T, typename U>
	using less = bool_<(T::value < U::value)>;

} // namespace boost::tmp::test

using namespace boost::tmp;

namespace chunk_tests {

	template <typename T>
	    requires(std::same_as<T, list_<list_<int_<0>, int_<1>, int_<2>>,
	                                   list_<int_<3>, int_<4>, int_<5>>, list_<int_<6>, int_<7>>>>)
	struct ChunkEveryThreeElements;

	using chunk_test_1 =
	        ChunkEveryThreeElements<call_<chunk_<sizet_<3>>, int_<0>, int_<1>, int_<2>, int_<3>,
	                                      int_<4>, int_<5>, int_<6>, int_<7>>>;

} // namespace chunk_tests

namespace clamp_tests {

	template <typename T>
	    requires(std::same_as<T, list_<uint_<4>>>)
	struct ClampListWithOnlyFour;

	using clamp_test_1 = ClampListWithOnlyFour<
	        call_<clamp_<uint_<3>, uint_<10>>, uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>>;

} // namespace clamp_tests

namespace contains_tests {

	template <typename T>
	    requires(std::same_as<T, false_>)
	struct DoesNotContainType;

	using contains_test_1 = DoesNotContainType<call_<contains_<int_<0>>, int_<1>>>;

	using contains_test_2 = DoesNotContainType<call_<contains_<int_<1>>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct ContainsType;

	using contains_test_3 = ContainsType<call_<contains_<int_<2>>, int_<0>, int_<1>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct ContainsSubrange123;

	using contains_subrange_test_1 =
	        ContainsSubrange123<call_<contains_subrange_<list_<int_<1>, int_<2>, int_<3>>>, int_<0>,
	                                  int_<1>, int_<2>, int_<3>, int_<4>>>;


	template <typename T>
	    requires(std::same_as<T, false_>)
	struct DoesNotContainSubrange321;

	using contains_subrange_test_2 =
	        DoesNotContainSubrange321<call_<contains_subrange_<list_<int_<3>, int_<2>, int_<1>>>, int_<0>,
	                                  int_<1>, int_<2>, int_<3>, int_<4>>>;

} // namespace contains_tests

namespace drop_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>>>)
	struct DropOneOffOfList;

	using drop_test_1 = DropOneOffOfList<call_<drop_<sizet_<1>>, int_<0>, int_<1>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>>>)
	struct DropZeroReturnsInputList;

	using drop_test_2 = DropZeroReturnsInputList<call_<drop_<sizet_<0>>, int_<1>, int_<2>>>;

	// Dropping off of no input returns empty list
	// UNDER CONSIDERATION: Dropping input off of no input fails.
	// Should this return an empty list?
	// list_<>{} = call_<drop_<uint_<7>>>{};

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>>>)
	struct DropThreeOffEnd;

	using drop_last_test_1 = DropThreeOffEnd<
	        call_<drop_last_<sizet_<3>>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>;

} // namespace drop_tests

namespace each_tests {}

namespace erase_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<2>, int_<3>>>)
	struct EraseFirstElement;

	using erase_test_1 = EraseFirstElement<call_<erase_<sizet_<0>>, int_<1>, int_<2>, int_<3>>>;

	// Erasing an element from a list with a single element will always result in empty list.
	template <typename T>
	    requires(std::same_as<T, list_<>>)
	struct EraseSingleElement;

	using erase_test_2 = EraseSingleElement<call_<erase_<sizet_<0>>, int_<0>>>;

	// UNDER RECONSIDERATION: Returns list_<nothing_> if no input is given.
	template <typename T>
	    requires(std::same_as<T, list_<nothing_>>)
	struct EraseEmptyPackReturnsNothingType;

	using erase_test_3 = EraseEmptyPackReturnsNothingType<call_<erase_<sizet_<0>>>>;

} // namespace erase_tests

namespace filter_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<2>, int_<4>, int_<6>, int_<8>, int_<10>>>)
	struct FilterOutOddNumbers;

	using filter_test_1 =
	        FilterOutOddNumbers<call_<filter_<lift_<test::is_even>>, int_<1>, int_<2>, int_<3>, int_<4>,
	                                  int_<5>, int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>>;
} // namespace filter_tests

namespace find_tests {

	using alt_type_lookup_table =
		list_<
			list_<bool, bool_<false>>,
			list_<int,  int_<8>>,
			list_<unsigned int, uint_<3>>,
			list_<char, char_<'c'>>
		>;

	template<typename T> requires(std::same_as<T, char_<'c'>>)
	struct ValueFoundAtIndex3;

	using find_test_1 = ValueFoundAtIndex3<call_<find_<alt_type_lookup_table>, char>>;
	
	template<typename T> requires(std::same_as<T, false_>)
	struct ValueFoundAtIndex0;

	using find_test_2 = ValueFoundAtIndex0<call_<find_<alt_type_lookup_table>, bool>>;

} // namespace find_tests

namespace flatten_tests {

	template <typename T>
	    requires(std::same_as<T, list_<uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>>)
	struct SingleFlattenedList;

	using flatten_test_1 = SingleFlattenedList<call_<
	        flatten_<>, list_<list_<uint_<0>, uint_<1>>, uint_<2>, list_<uint_<3>>, uint_<4>>>>;

} // namespace flatten_tests

namespace fold_tests {

	// TODO: Redo fold_left_ tests
	template <typename T>
	    requires(std::same_as<T, int_<20>>)
	struct FoldRightAddsUpToTwenty;

	using fold_right_test_1 =
	        FoldRightAddsUpToTwenty<call_<fold_right_<lift_<test::add_pair>>, int_<1>, int_<10>, int_<9>>>;

} // namespace fold_tests

namespace function_if_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<3>>>)
	struct RemoveIfOnlyOddNumbersLeft;

	using remove_if_test_1 = RemoveIfOnlyOddNumbersLeft<
	        call_<remove_if_<lift_<test::is_even>>, int_<1>, int_<2>, int_<3>>>;

	template <typename T>
	    requires(std::same_as<T, sizet_<0>>)
	struct CountIfNoEvenNumbers;

	using count_if_test_1 =
	        CountIfNoEvenNumbers<call_<count_if_<lift_<test::is_even>>, int_<1>, int_<3>>>;

	// Empty input pack returns 0
	using count_if_test_2 = CountIfNoEvenNumbers<call_<count_if_<lift_<test::is_even>>>>;

	template <typename T>
	    requires(std::same_as<T, sizet_<3>>)
	struct CountIfHasThreeEvenNumbers;

	using count_if_test_3 =
	        CountIfHasThreeEvenNumbers<call_<count_if_<lift_<test::is_even>>, int_<0>, int_<2>, int_<4>>>;

	template <typename T>
	    requires(std::same_as<T, list_<uint_<1>, char_<'c'>, uint_<1>>>)
	struct ReplaceTwoWithC;

	using replace_if_test_1 = ReplaceTwoWithC<
	        call_<replace_if_<char_<'c'>, lift_<test::is_even>>, uint_<1>, uint_<2>, uint_<1>>>;

	template <typename T>
	    requires(std::same_as<T, list_<>>)
	struct ReplaceIfEmptyPackReturnsAnEmptyList;

	using replace_if_test_2 =
	        ReplaceIfEmptyPackReturnsAnEmptyList<call_<replace_if_<char_<'c'>, lift_<test::is_even>>>>;

	template <typename T>
	    requires(std::same_as<T, sizet_<3>>)
	struct FindIfEvenNumberAtPositionThree;

	using find_if_test_1 = FindIfEvenNumberAtPositionThree<
	        call_<find_if_<lift_<test::is_even>>, int_<1>, int_<1>, int_<1>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, nothing_>)
	struct FindIfReturnNothingForNoValueFound;

	// find_if_ returns nothing_ when there is no value found that satisfies the predicate.
	using find_if_test_2 =
	        FindIfReturnNothingForNoValueFound<call_<find_if_<lift_<test::is_even>>, int_<1>>>;

	template <typename T>
	    requires(std::same_as<T, sizet_<2>>)
	struct FindIfNotOddNumberAtPositionTwo;

	using find_if_not_test_1 = FindIfNotOddNumberAtPositionTwo<
	        call_<find_if_not_<lift_<test::is_even>>, int_<2>, int_<4>, int_<1>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, nothing_>)
	struct FindIfNotReturnNothingForNoValueFound;

	// find_if_ returns nothing_ when there is no value found that satisfies the predicate.
	using find_if_not_test_2 =
	        FindIfNotReturnNothingForNoValueFound<call_<find_if_not_<lift_<test::is_even>>, int_<2>>>;

} // namespace function_if_tests

namespace index_tests {

	template <typename T>
	    requires(std::same_as<T, int_<3>>)
	struct ElementAtIndexTwoIsThree;

	// Get index 2 of pack (int_<3>)
	using index_test_1 = ElementAtIndexTwoIsThree<
	        call_<index_<sizet_<2>>, int_<1>, char_<'c'>, int_<3>, int_<4>>>;

	template <typename T>
	    requires(std::same_as<T, int_<1>>)
	struct UnpackedElementAtIndexZeroIsOne;

	// Unpack simple_list, then take index 0
	using unpack_index_test_1 =
	        UnpackedElementAtIndexZeroIsOne<call_<ui0_<>, list_<int_<1>, int_<2>, int_<3>>>>;

	template <typename T>
	    requires(std::same_as<T, int_<1>>)
	struct ElementAtFrontIsOne;

	template <typename T>
	    requires(std::same_as<T, int_<1>>)
	struct EighthElement;

	// Get first element of pack
	using front_test_1 = ElementAtFrontIsOne<call_<front_<>, int_<1>, int_<2>, int_<3>>>;

} // namespace index_tests

namespace insert_tests {

	// Insert char_<'c'> at position 1
	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, char_<'c'>, int_<2>>>)
	struct Insert_C_AtPositionOne;

	using insert_test_1 =
	        Insert_C_AtPositionOne<call_<insert_<sizet_<1>, char_<'c'>>, int_<1>, int_<2>>>;

	// Insert char_<'c'> at position 0
	template <typename T>
	    requires(std::same_as<T, list_<char_<'c'>, int_<1>, int_<2>>>)
	struct Insert_C_AtPositionZero;

	using insert_test_2 =
	        Insert_C_AtPositionZero<call_<insert_<sizet_<0>, char_<'c'>>, int_<1>, int_<2>>>;

	// Insert char_<'c'> at position 2
	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>, char_<'c'>>>)
	struct Insert_C_AtPositionTwo;

	using insert_test_3 =
	        Insert_C_AtPositionTwo<call_<insert_<sizet_<2>, char_<'c'>>, int_<1>, int_<2>>>;

	// Insert char_<'c'> into no list (returns a list_ with char_<'c'> in it)
	template <typename T>
	    requires(std::same_as<T, list_<char_<'c'>>>)
	struct EmptyPackInsertionReturnsSingleElementList;

	using insert_test_4 =
	        EmptyPackInsertionReturnsSingleElementList<call_<insert_<sizet_<0>, char_<'c'>>>>;

} // namespace insert_tests

namespace join_tests {

	// TODO: join_ must flatten nested lists.
	// template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
	// struct Joined123;

	// using join_test_1 = Joined123<call_<join_<>, list_<list_<int_<1>>>, list_<int_<2>>,
	// list_<int_<3>>>>;

	// using joined_sequences = call_<join_seq_<lift_<into_sequence>>, std::index_sequence<1, 2>,
	// std::index_sequence<3, 4>>;

	// joined_sequences{} = std::index_sequence<1, 2, 3, 4>{};

} // namespace join_tests

namespace list_into_array_tests {

	static constexpr auto larr = list_into_array_<list_<int_<0>, int_<1>, int_<2>>>::value;

	static_assert(
	        std::same_as<decltype(larr), const std::array<int, 3>>); // const because of constexpr

} // namespace list_into_array_tests

namespace logic_tests {

	template <typename T>
	    requires(std::same_as<T, false_>)
	struct AllNumbersOdd;

	using and_test_1 = AllNumbersOdd<call_<and_<lift_<test::is_even>>, int_<1>, int_<1>, int_<1>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct AllNumbersEven;

	using and_test_2 = AllNumbersEven<call_<and_<lift_<test::is_even>>, int_<2>, int_<2>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct OneNumberEven;

	using or_test_1 = OneNumberEven<call_<or_<lift_<test::is_even>>, int_<1>, int_<2>, int_<1>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct OneNumberOdd;

	using or_test_2 = OneNumberOdd<call_<or_<lift_<test::is_even>>, int_<2>, int_<1>, int_<2>>>;

	// template<int A, int B>
	// struct two_ints {
	//     int a{A};
	//     int b{B};
	// };

	// false_{} = call_<less_f_<lift_<std::alignment_of>>, two_ints<1, 2>, char_<'c'>>{};
	// true_{}  = call_<less_f_<lift_<std::alignment_of>>, char_<'c'>,     two_ints<1, 2>>{};

	template <typename T>
	    requires(std::same_as<T, false_>)
	struct NoneOfTheNumbersAreOdd;

	using none_of_test_1 = NoneOfTheNumbersAreOdd<
	        call_<none_of_<lift_<test::is_even>>, int_<2>, int_<100>, int_<4>, int_<500>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct NoneOfTheNumbersAreEven;

	using none_of_test_2 =
	        NoneOfTheNumbersAreEven<call_<none_of_<lift_<test::is_even>>, int_<1>, int_<3>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct EmptyList;

	using none_of_test_3 =
	        NoneOfTheNumbersAreEven<call_<none_of_<lift_<test::is_even>>>>;

	template <typename T>
	    requires(std::same_as<T, false_>)
	struct SomeOfTheNumbersAreEven;

	using none_of_test_4 =
	        SomeOfTheNumbersAreEven<call_<none_of_<lift_<test::is_even>>, int_<1>, int_<4>, int_<3>, int_<6>>>;


} // namespace logic_tests

namespace nth_values_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>>>)
	struct KeysOfMap;

	using keys_test_1 =
	        KeysOfMap<call_<keys_<>, list_<int_<1>, int_<22>>, list_<int_<2>, int_<10>>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<44>, int_<45>>>)
	struct ValuesOfMap;

	using values_test_1 =
	        ValuesOfMap<call_<values_<>, list_<int_<1>, int_<44>>, list_<int_<2>, int_<45>>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<22>, int_<23>>>)
	struct IndexTwoValuesList;

	using nth_values_test_1 =
	        IndexTwoValuesList<call_<nth_values_<sizet_<2>>, list_<int_<1>, int_<22>, int_<22>>,
	                                 list_<int_<2>, int_<10>, int_<23>>>>;

} // namespace nth_values_tests

namespace partition_tests {

	template <typename T>
	    requires(std::same_as<T, list_<list_<int_<3>, int_<4>>, list_<int_<1>, int_<2>>>>)
	struct SplitIntoTwoListWithGreaterThanTwo;

	using partition_test_1 = SplitIntoTwoListWithGreaterThanTwo<
	        call_<partition_<lift_<test::greater_than_two>>, int_<1>, int_<2>, int_<3>, int_<4>>>;

} // namespace partition_tests

// TODO: Implement product_test
namespace product_tests {

	// using xl1 = list_<uint_<1>, uint_<2>, uint_<3>>;
	// using xr1 = list_<uint_<1>, uint_<2>, uint_<3>>;

	// using result1 = call_<product_<>, xl1, xr1>;

	// list_<list_<uint_<1>, uint_<1>>, list_<uint_<1>, uint_<2>>, list_<uint_<1>, uint_<3>>,
	//         list_<uint_<2>, uint_<1>>, list_<uint_<2>, uint_<2>>, list_<uint_<2>, uint_<3>>,
	//         list_<uint_<3>, uint_<1>>, list_<uint_<3>, uint_<2>>, list_<uint_<3>, uint_<3>>>{} =
	//         result1{};

} // namespace product_tests

namespace push_pop_tests {

	// push_back_ tests
	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>, char_<'c'>>>)
	struct PushBack_C {};

	using push_back_test_1 = PushBack_C<call_<push_back_<char_<'c'>>, int_<1>, int_<2>>>;

	// pop_front_ tests
	template <typename T>
	    requires(std::same_as<T, list_<>>)
	struct NoElementsLeft;

	// Pop front off of single element list to return an empty list.
	using pop_front_test_1 = NoElementsLeft<call_<pop_front_<>, list_<int_<1>>>>;

	// Pop front off of empty list_ to return an empty list_
	using pop_front_test_2 = NoElementsLeft<call_<pop_front_<>, list_<>>>;

	template <typename T>
	    requires(std::same_as<T, list_<nothing_>>)
	struct EmptyPackReturnsListWithNothingType;

	// UNDER CONSIDERATION: Removal / modification of behavior of
	// pop_front_ on no input. Currently returns a list_<nothing_>
	using pop_front_test_3 = EmptyPackReturnsListWithNothingType<call_<pop_front_<>>>;

	// push_front tests
	template <typename T>
	    requires(std::same_as<T, list_<int_<4>, int_<1>, int_<2>>>)
	struct PushFourToFront;

	using push_front_test_1 = PushFourToFront<call_<push_front_<int_<4>>, int_<1>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>>>)
	struct PushOneToEmptyPack;

	using push_front_test_2 = PushOneToEmptyPack<call_<push_front_<int_<1>>>>;

	// pop_back_ tests
	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>>>)
	struct Pop_int_3_OffOfBack;

	using pop_back_test_1 = Pop_int_3_OffOfBack<call_<pop_back_<>, int_<1>, int_<2>, int_<3>>>;

	template <typename T>
	    requires(std::same_as<T, list_<>>)
	struct PopBackEmptyList;

	using pop_back_test_2 = PopBackEmptyList<call_<pop_back_<>, list_<>>>;

	template <typename T>
	    requires(std::same_as<T, list_<nothing_>>)
	struct PopBackEmptyPack;

	using pop_back_test_3 = PopBackEmptyPack<call_<pop_back_<>>>;

} // namespace push_pop_tests

namespace reverse_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<2>, int_<1>, int_<0>>>)
	struct ListTwoOneZero;

	using reverse_test_1 = ListTwoOneZero<call_<reverse_<>, int_<0>, int_<1>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, list_<>>)
	struct EmptyListReturnsEmptyList;

	// Reversing empty input results in empty list
	using reverse_test_2 = EmptyListReturnsEmptyList<call_<reverse_<>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>>>)
	struct SingleElementReturnsListOfSingleElement;

	// Reversing single input results in single input list
	using reverse_test_3 = SingleElementReturnsListOfSingleElement<call_<reverse_<>, int_<1>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
	struct DoubleReverseIsOriginal;

	using reverse_test_4 =
	        DoubleReverseIsOriginal<call_<reverse_<reverse_<>>, int_<1>, int_<2>, int_<3>>>;

} // namespace reverse_tests

namespace rotate_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
	struct ZeroRotation;

	using rotate_test_1 = ZeroRotation<call_<rotate_<int_<0>>, int_<1>, int_<2>, int_<3>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<2>, int_<3>, int_<1>>>)
	struct DoOneRotation;

	using rotate_test_2 = DoOneRotation<call_<rotate_<int_<1>>, int_<1>, int_<2>, int_<3>>>;

	template <typename T>
	    requires(std::same_as<T, list_<>>)
	struct RotateEmptyList;

	using rotate_test_3 = RotateEmptyList<call_<rotate_<int_<0>>>>;

	// TODO: Allow rotations in opposite direction.
	// list_<int_<3>, int_<1>, int_<2>>{} = call_<rotate_<int_<-1>>, int_<1>, int_<2>, int_<3>>{};

} // namespace rotate_tests

namespace sequence_tests {

	template <typename T>
	using and_one = sizet_<T::value + 1>;

	template <typename T>
	struct always_one {
		template <typename N>
		using f = sizet_<T::value>;
	};

	template <typename T>
	    requires(std::same_as<T, list_<sizet_<0>, sizet_<1>, sizet_<2>>>)
	struct ListZeroOneTwo;

	template <typename T>
	    requires(std::same_as<T, list_<sizet_<1>, sizet_<2>, sizet_<3>>>)
	struct ListOneTwoThree;

	using make_sequence_test_1 = ListZeroOneTwo<call_<make_sequence_<>, sizet_<3>>>;
	using make_sequence_test_2 = ListOneTwoThree<call_<make_sequence_<lift_<and_one>>, sizet_<3>>>;

	// TODO: Implement repeat_sequence_test
	// std::index_sequence<1, 1, 1, 1, 1, 1, 1, 1, 1, 1>{} = call_<repeat_sequence_<sizet_<10>,
	// lift_<into_sequence>>, sizet_<1>>{}; list_<sizet_<1>, sizet_<1>, sizet_<1>, sizet_<2>,
	// sizet_<2>, sizet_<2>, sizet_<3>, sizet_<3>, sizet_<3>>{} =
	// call_<transform_<repeat_sequence_<sizet_<3>>, join_<>>, sizet_<1>, sizet_<2>, sizet_<3>>{};

} // namespace sequence_tests

namespace size_tests {

	template <typename T>
	    requires(std::same_as<T, sizet_<3>>)
	struct SizeThreeElementsInPack;

	using size_test_1 = SizeThreeElementsInPack<call_<size_<>, int_<0>, int_<2>, int_<4>>>;

	template <typename T>
	    requires(std::same_as<T, sizet_<0>>)
	struct SizeEmptyPackIsZero;

	// No input list is zero size.
	using size_test_2 = SizeEmptyPackIsZero<call_<size_<>>>;

} // namespace size_tests

namespace slice_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<5>, int_<6>, int_<7>, int_<8>>>)
	struct SliceLBFourUBTwo;

	using slice_test_1 =
	        SliceLBFourUBTwo<call_<slice_<sizet_<4>, sizet_<2>>, int_<1>, int_<2>, int_<3>, int_<4>,
	                               int_<5>, int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>>;

} // namespace slice_tests

namespace slide_tests {

	template <typename T>
	    requires(std::same_as<T, list_<list_<int_<1>, int_<2>>, list_<int_<2>, int_<3>>,
	                                   list_<int_<3>, int_<4>>>>)
	struct SlideTwoIncrByOne;

	using slide_test_1 =
	        SlideTwoIncrByOne<call_<slide_<sizet_<2>>, int_<1>, int_<2>, int_<3>, int_<4>>>;

	template <typename T>
	    requires(std::same_as<
	             T, list_<list_<int_<1>, int_<2>, int_<3>>, list_<int_<2>, int_<3>, int_<4>>>>)
	struct SlideThreeIncrByOne;

	using slide_test_2 =
	        SlideThreeIncrByOne<call_<slide_<sizet_<3>>, int_<1>, int_<2>, int_<3>, int_<4>>>;

	template <typename T>
	    requires(std::same_as<T, list_<list_<int_<1>, int_<2>, int_<3>, int_<4>>>>)
	struct SlideFourIncrByOne;

	using slide_test_3 =
	        SlideFourIncrByOne<call_<slide_<sizet_<4>>, int_<1>, int_<2>, int_<3>, int_<4>>>;

} // namespace slide_tests

namespace split_tests {

	template <typename T>
	    requires(std::same_as<T, list_<list_<int_<1>, int_<2>, int_<3>, int_<4>>,
	                                   list_<int_<5>, int_<6>, int_<7>, int_<8>>>>)
	struct SplitAtIndexFour;

	using split_test_1 = SplitAtIndexFour<call_<split_<sizet_<4>>, int_<1>, int_<2>, int_<3>,
	                                            int_<4>, int_<5>, int_<6>, int_<7>, int_<8>>>;

} // namespace split_tests

namespace sort_tests {

	template <typename T>
	    requires(std::same_as<T, list_<sizet_<0>, sizet_<1>, sizet_<2>>>)
	struct ListZeroOneTwo;

	using sort_test_1 = ListZeroOneTwo<call_<sort_<lift_<test::less>>, sizet_<1>, sizet_<0>, sizet_<2>>>;

} // namespace sort_tests

namespace starts_ends_tests {

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct StartsWithAB;

	using starts_with_test_1 = StartsWithAB<
	        call_<starts_with_<list_<char_<'A'>, char_<'B'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

	template <typename T>
	    requires(std::same_as<T, false_>)
	struct DoesNotStartWithAD;

	using starts_with_test_2 = DoesNotStartWithAD<
	        call_<starts_with_<list_<char_<'A'>, char_<'D'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

	template <typename T>
	    requires(std::same_as<T, true_>)
	struct EndsWithBD;

	using ends_with_test_1 = EndsWithBD<
	        call_<starts_with_<list_<char_<'A'>, char_<'B'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

	template <typename T>
	    requires(std::same_as<T, false_>)
	struct DoesNotEndWithAD;

	using ends_with_test_2 = DoesNotEndWithAD<
	        call_<starts_with_<list_<char_<'A'>, char_<'D'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

} // namespace starts_ends_tests

namespace stride_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>)
	struct EveryZerothElement;

	template <typename T>
	    requires(std::same_as<T, list_<int_<0>, int_<2>, int_<4>>>)
	struct EverySecondElement;

	template <typename T>
	    requires(std::same_as<T, list_<char_<'a'>, char_<'d'>, char_<'g'>>>)
	struct EveryThirdElement;

	using stride_test_1 =
	        EveryThirdElement<call_<stride_<sizet_<3>>, char_<'a'>, char_<'b'>, char_<'c'>,
	                                char_<'d'>, char_<'e'>, char_<'f'>, char_<'g'>>>;

} // namespace stride_tests

namespace swap_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<0>>>)
	struct ListOneZero;

	using swap_test_1 = ListOneZero<call_<swap_<>, int_<0>, int_<1>>>;
	// using too_many_swap_test = call_<swap_<>, int_<1>, int_<2>, int_<3>>;
} // namespace swap_tests

namespace take_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>>>)
	struct TakeFirstElement_One;

	using take_test_1 = TakeFirstElement_One<call_<take_<sizet_<1>>, int_<1>, int_<2>, int_<3>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>>>)
	struct TakeFirstTwoElements_OneTwo;

	using take_test_2 =
	        TakeFirstTwoElements_OneTwo<call_<take_<sizet_<2>>, int_<1>, int_<2>, int_<3>>>;

	// UNDER CONSIDERATION: Taking more than the list results in compilation failure.
	// UNDER CONSIDERATION: Taking from an empty input results in compilation failure.
	// list_<>{} = call_<take_<uint_<4>>>{};

	template <typename T>
	    requires(std::same_as<T, list_<int_<4>, int_<5>>>)
	struct LastTwoElements;

	using take_last_test_1 = LastTwoElements<
	        call_<take_last_<sizet_<2>>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<2>, int_<4>, int_<8>>>)
	struct TakeFirstEvenElements;

	using take_while_test_1 = TakeFirstEvenElements<
	        call_<take_while_<lift_<test::is_even>>, int_<2>, int_<4>, int_<8>, int_<7>, int_<10>>>;

} // namespace take_tests

// TODO: Narrow tests down.
namespace tee_tests {

	// list_<list_<>>{}          = call_<tee_<listify_, listify_>>{};
	// list_<list_<int>>{}       = call_<tee_<listify_, listify_>, int>{};
	// list_<list_<int, bool>>{} = call_<tee_<listify_, listify_>, int, bool>{};

	// true_{}  = call_<tee_<is_<int>, and_<>>, int>{};
	// false_{} = call_<tee_<is_<int>, is_<int>, and_<>>, char>{};
	// false_{} = call_<tee_<is_<int>, is_<int>, is_<int>, and_<>>, char>{};
	// false_{} = call_<tee_<is_<int>, identity_, and_<>>,
	//                     char>{}; // short circuiting should save from hard error
	// false_{} = call_<tee_<is_<int>, identity_, is_<int>, and_<>>,
	//                     char>{}; // short circuiting should save from hard error

	// true_{}  = call_<tee_<is_<int>, or_<>>, int>{};
	// false_{} = call_<tee_<is_<int>, is_<int>, or_<>>, char>{};
	// false_{} = call_<tee_<is_<int>, is_<int>, is_<int>, or_<>>, char>{};
	// true_{}  = call_<tee_<is_<int>, identity_, or_<>>,
	//                 int>{}; // short circuiting should save from hard error
	// true_{}  = call_<tee_<is_<int>, identity_, is_<int>, or_<>>,
	//                 int>{}; // short circuiting should save from hard error

} // namespace tee_tests

// TODO: Implement transform_ tests
namespace transform_tests {} // namespace transform_tests

namespace trim_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<1>>>)
	struct DropEvenNumbersAtFront;

	using drop_while_test_1 = DropEvenNumbersAtFront<
	        call_<drop_while_<lift_<test::is_even>>, int_<2>, int_<2>, int_<1>, int_<1>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<1>>>)
	struct DropEvenNumbersAtBack;

	using drop_while_back_test_1 = DropEvenNumbersAtBack<
	        call_<drop_while_back_<lift_<test::is_even>>, int_<1>, int_<1>, int_<2>, int_<2>>>;

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<6>, int_<1>>>)
	struct TrimEvenNumbersUntilOdd;

	using trim_test_1 = TrimEvenNumbersUntilOdd<
	        call_<trim_<lift_<test::is_even>>, int_<2>, int_<1>, int_<6>, int_<1>, int_<2>>>;

} // namespace trim_tests

namespace try_tests {

	// TODO: Implement try_test
	// template <typename T>
	// using call_type = T::type;

	// struct has_type {
	//     using type = int;
	// };

	// nothing_{}   = call_<try_<call_type>, int>{}; // should SFINAE, int has no ::type
	// list_<int>{} = list_<call_<try_<call_type>, has_type>>{}; // should not SFINAE
	// list_<int>{} = call_<try_<call_type, listify_>, has_type>{}; // test the continuation

} // namespace try_tests

namespace unique_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<3>, int_<1>, int_<2>>>)
	struct OnlyUniqueNums;

	using unique_test_1 =
	        OnlyUniqueNums<call_<unique_<>, int_<3>, int_<1>, int_<2>, int_<2>, int_<1>, int_<2>>>;

} // namespace unique_tests

namespace values_tests {

} // namespace values_tests

namespace window_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
	struct GetTheMiddle123;

	using window_test_1 = GetTheMiddle123<call_<window_<sizet_<1>, sizet_<3>>, int_<0>, int_<1>,
	                                            int_<2>, int_<3>, int_<5>, int_<7>>>;

} // namespace window_tests

namespace zip_tests {

	template <typename T>
	    requires(std::same_as<T, list_<int_<3>, int_<7>>>)
	struct AddPairsTogetherWithZip;

	// Performs an addition of pairs of elements component wise i.e. (x0 + x1), (y0 + y1), ...
	using zip_test_1 = AddPairsTogetherWithZip<
	        call_<zip_<lift_<test::add_pair>>, list_<int_<1>, int_<3>>, list_<int_<2>, int_<4>>>>;

	template <typename T>
	    requires(std::same_as<T, list_<list_<int_<1>, int_<2>>, list_<int_<3>, int_<4>>>>)
	struct ZipPairsIntoList;

	// Pairs elements in each list together i.e. (x0, y0), (x1, y1), ...
	using zip_test_2 = ZipPairsIntoList<
	        call_<zip_<listify_>, list_<int_<1>, int_<3>>, list_<int_<2>, int_<4>>>>;

	template <typename T>
	    requires(std::same_as<T, list_<list_<sizet_<0>, char_<'a'>>, list_<sizet_<1>, char_<'b'>>,
	                                   list_<sizet_<2>, char_<'c'>>>>)
	struct ZipABCWith123;

	using zip_with_test_1 =
	        ZipABCWith123<call_<zip_with_index_<>, char_<'a'>, char_<'b'>, char_<'c'>>>;

} // namespace zip_tests
