//  Copyright 2019 Odin Holmes.
//            2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Algorithm.Gather;

import Boost.TMP.Base.Call;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Sequence.Join;

export namespace boost::tmp {
        // Sorts, and then groups items into a list of lists of the same type.
        template<typename F, typename C = listify_>
        struct gather_;

		namespace detail {
            template <unsigned N, typename F, typename C>
			struct dispatch<N, gather_<F, C>>{};

		} // namespace detail
} // export namespace boost::tmp
