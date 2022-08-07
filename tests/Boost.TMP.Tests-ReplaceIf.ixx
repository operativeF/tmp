//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:ReplaceIf;

import Boost.TMP;
import :Helpers;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace replace_if_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, list_<uint_<1>, char_<'c'>, uint_<1>>>)
    struct ReplaceTwoWithC;

    template<typename T> requires(std::same_as<T, list_<>>)
    struct EmptyPackReturnsAnEmptyList;

    ReplaceTwoWithC<call_<replace_if_<char_<'c'>, lift_<is_even>>, uint_<1>, uint_<2>, uint_<1>>>;

    EmptyPackReturnsAnEmptyList<call_<replace_if_<char_<'c'>, lift_<is_even>>>>;

} // namespace replace_if_test
