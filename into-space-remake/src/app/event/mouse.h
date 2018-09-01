#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_

#include "event.h"

namespace app::event {
	struct MouseRoll : public Event {
		const int offset;
		const double x, y;

		constexpr MouseRoll(int offset, double x, double y) :
			Event{Event::Type::mouseRoll}, offset{offset},
			x{x}, y{y} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif