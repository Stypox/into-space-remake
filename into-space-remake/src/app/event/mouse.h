#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_

#include "event.h"

namespace app::event {
	struct Click : public Event {
		enum Type : char {
			press,
			doublePress,
			release,
		};

		const Type type;
		const int key;
		const int x, y;

		constexpr Click(Type type, int key, int x, int y) :
			Event{Event::Type::click}, type{type},
			key{key}, x{x},
			y{y} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};

	struct LongClick : public Event {
		enum Type : char {
			press,
			release,
		};

		const Type type;
		const int key;
		const int x, y;
		const float delayAfterAction, delayInBetween;

		constexpr LongClick(Type type, int key, int x, int y, float delayAfterAction, float delayInBetween) :
			Event{Event::Type::click}, type{type},
			key{key}, x{x},
			y{y}, delayAfterAction{delayAfterAction},
			delayInBetween{delayInBetween} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};

	struct MouseRoll : public Event {
		const int offset;
		const int x, y;

		constexpr MouseRoll(int offset, int x, int y) :
			Event{Event::Type::mouseRoll}, offset{offset},
			x{x}, y{y} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif