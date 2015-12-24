//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MAJUTSU_RAW_RECORD_BINDING_HPP_INCLUDED
#define MAJUTSU_RAW_RECORD_BINDING_HPP_INCLUDED

#include <majutsu/access_role.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/get.hpp>
#include <majutsu/init.hpp>
#include <majutsu/unwrap_role.hpp>
#include <majutsu/raw/combine_static_sizes.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/integral_size.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/record_impl.hpp>
#include <majutsu/raw/size_type.hpp>
#include <majutsu/raw/static_size.hpp>
#include <majutsu/raw/detail/copy_n.hpp>
#include <fcppt/decltype_sink.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Types
>
struct static_size<
	majutsu::raw::record<
		Types
	>
>
:
boost::mpl::fold<
	typename
	majutsu::raw::record<
		Types
	>::all_types,
	majutsu::raw::integral_size<
		0
	>,
	majutsu::raw::combine_static_sizes<
		majutsu::raw::static_size<
			boost::mpl::_1
		>,
		boost::mpl::_2
	>
>::type
{
};

FCPPT_PP_POP_WARNING

template<
	typename Types
>
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		majutsu::raw::record<
			Types
		>
	>,
	majutsu::raw::element_type<
		majutsu::raw::record<
			Types
		>
	> const &_value
)
{
	return
		fcppt::algorithm::fold(
			typename
			majutsu::raw::record<
				Types
			>::all_types{},
			fcppt::literal<
				majutsu::raw::size_type
			>(
				0
			),
			[
				&_value
			](
				auto const _tag,
				majutsu::raw::size_type const _size
			)
			{
				typedef
				fcppt::tag_type<
					FCPPT_DECLTYPE_SINK(
						_tag
					)
				>
				role;

				return
					majutsu::raw::needed_size<
						majutsu::access_role<
							role
						>
					>(
						majutsu::get<
							majutsu::unwrap_role<
								role
							>
						>(
							_value
						)
					)
					+
					_size;
			}
		);
}

template<
	typename Types
>
inline
void
place(
	majutsu::dispatch_type<
		majutsu::raw::record<
			Types
		>
	>,
	majutsu::raw::element_type<
		majutsu::raw::record<
			Types
		>
	> const &_value,
	majutsu::raw::pointer const _memory
)
{
	majutsu::raw::detail::copy_n(
		_value.data(),
		_value.size(),
		_memory
	);
}

template<
	typename Types
>
inline
majutsu::raw::element_type<
	majutsu::raw::record<
		Types
	>
>
make(
	majutsu::dispatch_type<
		majutsu::raw::record<
			Types
		>
	>,
	majutsu::raw::const_pointer _memory
)
{
	return
		majutsu::init<
			majutsu::raw::record<
				Types
			>
		>(
			[
				&_memory
			](
				auto const _role
			)
			{
				typedef
				majutsu::access_role<
					FCPPT_DECLTYPE_SINK(
						_role
					)
				>
				element;

				majutsu::raw::element_type<
					element
				> value(
					majutsu::raw::make<
						element
					>(
						_memory
					)
				);

				_memory +=
					majutsu::raw::needed_size<
						element
					>(
						value
					);

				return
					std::move(
						value
					);
			}
		);
}

}
}

#endif
