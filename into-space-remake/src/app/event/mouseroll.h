#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSEROLL_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSEROLL_H_

#include "event.h"

namespace app::event {
	struct MouseRoll : public Event {
		const double offset;
		const double x, y;

		constexpr MouseRoll(double offset, double x, double y) :
			Event{Event::Type::mouseRoll}, offset{offset},
			x{x}, y{y} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif