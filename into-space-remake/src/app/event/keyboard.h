#ifndef _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_

#include "event.h"

namespace app::event {
	struct KeyboardEvent : public Event {
		enum Type : char {
			click,
			doubeClick,
			press,
			release,
			longPress,
		};

		const Type type;
		const int key;

		constexpr KeyboardEvent(Type type, int key) :
			Event{Event::Type::keyboard}, type{type},
			key{key} {}

		inline Event::Type eventType() const { return Event::type; }
	};
}

#endif