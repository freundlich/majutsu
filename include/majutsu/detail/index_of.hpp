//          Copyright Carl Philipp Reh 2014 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MAJUTSU_DETAIL_INDEX_OF_HPP_INCLUDED
#define MAJUTSU_DETAIL_INDEX_OF_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{
namespace detail
{

template<
	typename Elements,
	typename Iterator
>
using index_of
=
typename
boost::mpl::distance<
	typename boost::mpl::begin<
		Elements
	>::type,
	Iterator
>::type;

}
}

#endif
