//  Copyright 2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Helpers;

import Boost.TMP;

using namespace boost::tmp;

export template <typename T, typename U>
using add = uint_<(T::value + U::value)>;

export template <typename T>
using is_even = bool_<(T::value % 2 == 0)>;
