//  Copyright 2019 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>

namespace boost {
    namespace tmp {

        // Returns a single list where common elements from both are removed.
        template<typename F = listify_, typename G = listify_, typename C = listify_>
        struct unary_symmetric_diff_ {};

        // Returns two lists where elements common to both of them are removed from each.
        template<typename F = listify_, typename G = listify_, typename C = listify_>
        struct binary_symmetric_diff_ {};

        namespace detail {
            template<unsigned N, typename F, typename G, typename C>
            struct dispatch<N, binary_symmetric_diff_<F, G, C>> {
                using f = call_<tee_<>, F, G>;
            };
        } // namespace detail
    } // namespace tmp
} // namespace boost