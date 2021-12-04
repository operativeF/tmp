//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Sequence.Size;

import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Detail.Dispatch;

export namespace boost::tmp {
		template <typename C = identity_>
		struct size_ {};
		namespace detail {
			template <unsigned N, typename C>
			struct dispatch<N, size_<C>> {
				template <typename... Ls>
				using f = typename dispatch<1, C>::template f<uint_<sizeof...(Ls)>>;
			};
		} // namespace detail
} // export namespace boost::tmp
