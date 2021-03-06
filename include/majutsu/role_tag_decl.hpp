//          Copyright Carl Philipp Reh 2014 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MAJUTSU_ROLE_TAG_DECL_HPP_INCLUDED
#define MAJUTSU_ROLE_TAG_DECL_HPP_INCLUDED

#include <majutsu/role_init_fwd.hpp>
#include <majutsu/role_tag_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{

template<
	typename Tag
>
struct role_tag
{
	typedef
	Tag
	tag;

	template<
		typename Arg
	>
	majutsu::role_init<
		Tag,
		typename
		std::decay<
			Arg
		>::type
	>
	operator=(
		Arg &&
	);
};

}

#endif
