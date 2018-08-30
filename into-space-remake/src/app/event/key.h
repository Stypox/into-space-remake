#ifndef _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_

#include "event.h"

namespace app::event {
	struct Key : public Event {
		enum Type : char {
			press,
			doublePress,
			release,
		};

		const Type type;
		const int key;

		constexpr Key(Type type, int key) :
			Event{Event::Type::key}, type{type},
			key{key} {}

		inline Event::Type eventType() const { return Event::type; }
		inline operator bool() const { return Event::type != Event::Type::empty; }
	};

	struct KeyLong : public Event {
		enum Type : char {
			press,
			release,
		};

		const int key;
		const int delay;

		constexpr KeyLong(int key, int delay) :
			Event{Event::Type::keyLong}, key{key},
			delay{delay} {}

		inline Event::Type eventType() const { return Event::type; }
		inline operator bool() const { return Event::type != Event::Type::empty; }
	};
}

#endif