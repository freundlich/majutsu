//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MAJUTSU_RAW_ELEMENT_TYPE_HPP_INCLUDED
#define MAJUTSU_RAW_ELEMENT_TYPE_HPP_INCLUDED


namespace majutsu
{
namespace raw
{

template<
	typename Element
>
using
element_type
=
typename
Element::element_type;

}
}

#endif