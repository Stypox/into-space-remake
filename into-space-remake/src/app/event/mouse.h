#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_

#include "event.h"

namespace app::event {
	struct MouseClickEvent : public Event {
		enum Type : char {
			click,
			doubeClick,
			press,
			release,
			longPress,
		};

		const Type type;
		const int key;
		const int x, y;

		constexpr MouseClickEvent(Type type, int key, int x, int y) :
			Event{Event::Type::mouseClick}, type{type},
			key{key}, x{x},
			y{y} {}

		inline Event::Type eventType() const { return Event::type; }
		inline operator bool() const { return Event::type != Event::Type::empty; }
	};

	struct MouseRollEvent : public Event {
		const int offset;
		const int x, y;

		constexpr MouseRollEvent(int offset, int x, int y) :
			Event{Event::Type::mouseRoll}, offset{offset},
			x{x}, y{y} {}

		inline Event::Type eventType() const { return Event::type; }
	};
}

#endif