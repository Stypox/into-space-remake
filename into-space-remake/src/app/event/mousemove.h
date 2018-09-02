#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSEMOVE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSEMOVE_H_

#include "event.h"

namespace app::event {
	struct MouseMove : public Event {
		enum Type {
			xAxis,
			yAxis,
		};

		const Type type;
		const double offset;
		const double position;

		constexpr MouseMove(Type type, double offset, double position) :
			Event{Event::Type::mouseMove}, type{type},
			offset{offset}, position{position} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif