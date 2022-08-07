//  Copyright 2018 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.RangeMath;

import :Algorithm.FoldLeft;
import :Algorithm.FoldRight;
import :Algorithm.Sort;
import :Algorithm.Transform;
import :Base.Identity;
import :Base.Lift;
import :Base.Vocabulary;
import :Base.Dispatch;
import :Sequence.Tee;
import :Sequence.Unpack;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename C = identity_>
    struct accumulate_ {};

    export template <typename C = identity_>
    struct decimate_right_ {};

    export template <typename C = identity_>
    struct decimate_left_ {};

    export template <typename C = identity_>
    struct sorted_decimate_ {};

    export template <typename C = identity_>
    struct multiplicate_ {};

    template <typename T, typename U>
    using add_ = int_<(T::value + U::value)>;

    template <typename T, typename U>
    using subtract_ = int_<(T::value - U::value)>;

    template <typename T, typename U>
    using multiply_ = int_<(T::value * U::value)>;

    template <typename T, typename U>
    using less = bool_<(T::value < U::value)>;

    template <std::size_t N, typename C>
    struct dispatch<N, accumulate_<C>> : dispatch<N, fold_right_<lift_<add_>, C>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, sorted_decimate_<C>>
        : dispatch<N, sort_<lift_<less, C>, fold_right_<lift_<subtract_>, C>>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, decimate_right_<C>> : dispatch<N, fold_right_<lift_<subtract_>, C>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, decimate_left_<C>> : dispatch<N, fold_left_<lift_<subtract_>, C>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, multiplicate_<C>> : dispatch<N, fold_right_<lift_<multiply_>, C>> {};
} // namespace boost::tmp

// TESTING:
namespace range_math_test {
    using namespace boost::tmp;

    // TODO: Implement range_math_test
    // using alist = list_<int_<-2>, int_<100>, int_<4>, int_<500>>;
    // using blist = list_<int_<10>, int_<20>, int_<5>, int_<1>>;

    // int_<602>{} = call_<unpack_<accumulate_<>>, alist>{};

    // int_<-606>{} = call_<unpack_<decimate_left_<>>, alist>{};
    // int_<398>{}  = call_<unpack_<decimate_right_<>>, alist>{};

    // int_<4>{}   = call_<unpack_<sorted_decimate_<>>, blist>{};
    // int_<-34>{} = call_<unpack_<decimate_right_<>>, blist>{};
    // int_<-16>{} = call_<unpack_<decimate_left_<>>, blist>{};

    // int_<-400000>{} = call_<unpack_<multiplicate_<>>, alist>{};
} // namespace range_math_test
