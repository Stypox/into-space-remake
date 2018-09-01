#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSEROLL_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSEROLL_H_

#include "event.h"

namespace app::event {
	struct Scroll : public Event {
		enum Type {
			xAxis,
			yAxis,
		};

		const Type type;
		const double offset;
		const double xCursor, yCursor;

		constexpr Scroll(Type type, double offset, double xCursor, double yCursor) :
			Event{Event::Type::mouseRoll}, type{type},
			offset{offset}, xCursor{xCursor},
			yCursor{yCursor} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif