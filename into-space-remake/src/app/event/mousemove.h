#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSEMOVE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSEMOVE_H_

#include "event.h"

namespace app::event {
	struct MouseMove : public Event {
		const double xOffset, yOffset;
		const double x, y;

		constexpr MouseMove(double xOffset, double yOffset, double x, double y) :
			Event{Event::Type::mouseMove}, xOffset{xOffset},
			yOffset{yOffset}, x{x},
			y{y} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif