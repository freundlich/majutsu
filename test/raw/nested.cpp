#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <majutsu/raw/fundamental.hpp>
#include <majutsu/raw/record.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	raw_nested
)
{
FCPPT_PP_POP_WARNING

	typedef
	majutsu::raw::fundamental<
		int
	>
	int_;

	typedef
	majutsu::raw::fundamental<
		bool
	>
	bool_;

	MAJUTSU_MAKE_ROLE_TAG(
		int_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		record_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		bool_role
	);

	typedef
	majutsu::raw::record<
		boost::mpl::vector2<
			majutsu::role<
				bool_,
				bool_role
			>,
			majutsu::role<
				int_,
				int_role
			>
		>
	>
	inner_record;

	typedef
	majutsu::raw::record<
		boost::mpl::vector2<
			majutsu::role<
				int_,
				int_role
			>,
			majutsu::role<
				inner_record,
				record_role
			>
		>
	>
	test_record;

	test_record const test{
		int_role{} = 42,
		record_role{} =
			inner_record{
				bool_role{} = false,
				int_role{} = 500
			}
	};

	BOOST_CHECK_EQUAL(
		majutsu::get<
			int_role
		>(
			test
		),
		42
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			bool_role
		>(
			majutsu::get<
				record_role
			>(
				test
			)
		),
		false
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			int_role
		>(
			majutsu::get<
				record_role
			>(
				test
			)
		),
		500
	);
}