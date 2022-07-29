//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Sequence.Container;

import :Base.Identity;
import :Base.Lift;
import :Base.Vocabulary;
import :Detail.Dispatch;

namespace boost::tmp {
	/// \brief
	export template <typename C = identity_>
	struct container_ {};

	template <typename L, typename C>
	struct container_impl {
		using type = dispatch<1, C>::template f<nothing_>;
	};
	template <template <typename...> class Seq, typename C, typename... Ls>
	struct container_impl<Seq<Ls...>, C> {
		using type = dispatch<1, C>::template f<lift_<Seq>>;
	};

	template <typename C>
	struct dispatch<1, container_<C>> {
		template <typename L>
		using f = container_impl<L, C>::type;
	};
} // namespace boost::tmp
