#ifndef _INTO_SPACE_REMAKE_APP_EVENT_SCROLL_HPP_
#define _INTO_SPACE_REMAKE_APP_EVENT_SCROLL_HPP_

namespace app::event {
	struct Scroll {
		enum Type {
			xAxis,
			yAxis,
		};

		const Type type;
		const double offset;
		const double xCursor, yCursor;

		constexpr explicit Scroll(Type type) :
			type{type}, offset{},
			xCursor{}, yCursor{} {}
		constexpr Scroll(Type type, double offset, double xCursor, double yCursor) :
			type{type}, offset{offset},
			xCursor{xCursor}, yCursor{yCursor} {}
	};
}

#endif