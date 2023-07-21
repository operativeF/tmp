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

namespace drop_v_tests {
	template <typename T>
	    requires(std::same_as<T, list_v_<1>>)
	struct DropVOneOffOfList;

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2>>)
	struct DropVZeroReturnsInputList;

	using drop_v_test_1 = DropVOneOffOfList<call_v_<drop_v_<1>, 0, 1>>;

	using drop_v_test_2 = DropVZeroReturnsInputList<call_v_<drop_v_<0>, 1, 2>>;
} // namespace drop_v_tests

namespace drop_last_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2>>)
	struct DropVLastThreeOffEnd;

	using drop_last_v_test_1 = DropVLastThreeOffEnd<
	        call_v_<drop_last_v_<3>, 1, 2, 3, 4, 5>>;

} // namespace drop_last_v_tests

namespace erase_v_tests {
	template <typename T>
	    requires(std::same_as<T, list_v_<2, 3>>)
	struct EraseFirstElement;

	// Erasing an element from a list with a single element will always result in empty list.
	template <typename T>
	    requires(std::same_as<T, list_v_<>>)
	struct EraseSingleElement;

	// UNDER RECONSIDERATION: Returns list_<nothing_> if no input is given.
	template <typename T>
	    requires(std::same_as<T, list_v_<nothing_{}>>)
	struct EraseEmptyPackReturnsNothingType;

	using erase_test_1 = EraseFirstElement<call_v_<erase_v_<0>, 1, 2, 3>>;

	using erase_test_2 = EraseSingleElement<call_v_<erase_v_<0>, 0>>;

	using erase_test_3 = EraseEmptyPackReturnsNothingType<call_v_<erase_v_<0>>>;
} // namespace erase_tests

namespace filter_v_tests {
	template<typename T>
		requires(std::same_as<T, list_v_<2, 4, 6, 8, 10>>)
	struct FilterOutOddValues;

	template <auto T>
	using is_even_val = bool_<T % 2 == 0>;

	using filter_test_1 = FilterOutOddValues<call_v_<filter_v_<lift_v_<is_even_val>>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>>;
}

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

	template<auto V0>
	struct added_in {
		template<auto V1>
		using f = list_v_<V0 + V1>;
	};

	template<typename T, auto U>
	using add_up_left = call_<unpack_v_<lift_v_<added_in<U>::template f>>, T>;

	using fold_left_v_test_1 =
	        FoldLeftValuesTo20<call_tv_<fold_left_v_<lift_tv_<add_up_left>>, list_v_<1>, 10, 9>>;

} // namespace fold_v_tests

namespace index_v_tests {
	
	template<typename T> requires(std::same_as<T, list_v_<9>>)
	struct AtIndexTwo;

	using index_v_test_1 = AtIndexTwo<call_v_<iv2_<listify_v_>, 1, 4, 9, 10>>;

	template<typename T> requires(std::same_as<T, list_v_<2>>)
	struct AtUnpackedIndexTen;

	using index_v_test_2 = AtUnpackedIndexTen<call_<unpack_index_v_<10>, list_v_<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 2>>>;

} // namespace index_v_tests

namespace insert_v_tests {

	// Insert char_<'c'> at position 1
	template <typename T>
	    requires(std::same_as<T, list_v_<1, 'c', 2>>)
	struct Insert_C_AtPositionOne;

	// Insert char_<'c'> at position 0
	template <typename T>
	    requires(std::same_as<T, list_v_<'c', 1, 2>>)
	struct Insert_C_AtPositionZero;

	// Insert char_<'c'> at position 2
	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2, 'c'>>)
	struct Insert_C_AtPositionTwo;

	// Insert char_<'c'> into no list (returns a list_ with char_<'c'> in it)
	template <typename T>
	    requires(std::same_as<T, list_v_<'c'>>)
	struct EmptyPackInsertionReturnsSingleElementList;

	using insert_test_1 =
	        Insert_C_AtPositionZero<call_v_<insert_v_<0, 'c'>, 1, 2>>;

	using insert_test_2 =
	        Insert_C_AtPositionOne<call_v_<insert_v_<1, 'c'>, 1, 2>>;

	using insert_test_3 =
	        Insert_C_AtPositionTwo<call_v_<insert_v_<2, 'c'>, 1, 2>>;

	using insert_test_4 =
	        EmptyPackInsertionReturnsSingleElementList<call_v_<insert_v_<0, 'c'>>>;

} // namespace insert_v_tests

namespace is_v_tests {

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueIsFive;

using is_v_test_1 = ValueIsFive<call_v_<is_v_<5>, 5>>;

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueCharCIsInt99;

using is_v_test_2 = ValueCharCIsInt99<call_v_<is_v_<99>, 'c'>>;

} // namespace is_v_tests

namespace is_not_v_tests {

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueIsNotFive;

using is_not_v_test_1 = ValueIsNotFive<call_v_<is_not_v_<5>, 2>>;

} // namespace is_v_tests

namespace not_v_tests {

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueIsNotTrue;

using not_v_test_1 = ValueIsNotTrue<call_v_<not_v_<>, false>>;

} // namespace not_v_tests

namespace range_lo_hi_v_tests {

template<typename T> requires(std::same_as<T, list_v_<false>>)
struct OutsideOf5To10;

using range_lo_hi_v_test_1 = OutsideOf5To10<call_v_<range_lo_hi_v_<5, 10>, 7>>;

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
} // namespace reverse_v_tests

namespace rotate_v_tests {

template<typename T> requires(std::same_as<T, list_v_<1, 3, 2>>)
struct OneThreeTwo;

using RotateTwice = OneThreeTwo<call_v_<rotate_v_<2>, 3, 2, 1>>;

} // namespace rotate_v_tests

namespace sequence_v_tests {

template<typename T> requires(std::same_as<T, list_v_<1, 1, 1, 1, 1,
													  1, 1, 1, 1, 1>>)
struct RepeatedOnes;

using sequence_v_test_1 = RepeatedOnes<call_v_<repeat_sequence_v_<10>, 1>>;

} // namespace sequence_v_tests

namespace size_v_tests {

template<typename T> requires(std::same_as<T, list_v_<std::size_t{3}>>)
struct FiveValueListV;

using size_v_test_1 = FiveValueListV<call_v_<size_v_<listify_v_>, 1, 2, 3>>;

} // namespace size_v_tests

namespace swap_v_tests {

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 0>>)
	struct ListVOneZero;

	using swap_v_test_1 = ListVOneZero<call_v_<swap_v_<>, 0, 1>>;

} // namespace swap_v_tests

namespace take_v_tests {
	template <typename T>
	    requires(std::same_as<T, list_v_<1>>)
	struct TakeVFirstElement_One;

	template <typename T>
	    requires(std::same_as<T, list_v_<1, 2>>)
	struct TakeVFirstTwoElements_OneTwo;

	using take_v_test_1 = TakeVFirstElement_One<call_v_<take_v_<1>, 1, 2, 3>>;
	using take_v_test_2 = TakeVFirstTwoElements_OneTwo<call_v_<take_v_<2>, 1, 2, 3>>;

} // namespace take_v_tests

namespace take_last_v_tests {

template<typename T> requires(std::same_as<T, list_v_<4, 5, 6>>)
struct LastThreeOfSeries;

using take_last_v_test_1 = LastThreeOfSeries<call_v_<take_last_v_<3>, 1, 2, 3, 4, 5, 6>>;

template<typename T> requires(std::same_as<T, list_v_<>>)
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

namespace transform_v_tests {

template<typename T> requires(std::same_as<T, list_v_<1, 2, 3>>)
struct AddOneToEach;

constexpr auto add_one = [](auto V) consteval {
    return V + 1;
};

using transform_v_test_1 = AddOneToEach<call_v_<transform_v_<add_one>, 0, 1, 2>>;

} // namespace transform_v_tests

// TODO: Implement value_to_type_
/*
namespace value_to_type_tests {

	template<typename T> requires(std::same_as<T,
		list_<
			int_<1>,
			uint_<2>,
			char_<'c'>,
			false_
		>>)
	struct TransmogValueToType;
	using value_to_type_test_1 = TransmogValueToType<call_v_<transform_v_<value_to_type_<default_type_lookup_table_>>,
		1,
		2U,
		'c',
		false>>;

} // namespace value_to_type_tests
*/