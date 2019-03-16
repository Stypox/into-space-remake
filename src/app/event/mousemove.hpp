#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSEMOVE_HPP_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSEMOVE_HPP_

namespace app::event {
	struct MouseMove {
		enum Type {
			xAxis,
			yAxis,
		};

		const Type type;
		const double offset;
		const double position;

		constexpr explicit MouseMove(Type type) :
			type{type}, offset{},
			position{} {}
		constexpr MouseMove(Type type, double offset, double position) :
			type{type}, offset{offset},
			position{position} {}
	};
}

#endif