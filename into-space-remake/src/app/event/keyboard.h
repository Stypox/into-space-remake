#ifndef _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_

#include "event.h"

namespace app::event {
	class KeyboardEvent : public Event {
	public:
		enum Type : char {
			click,
			doubeClick,
			press,
			release,
			longPress,
		};
	private:
		Type m_type;
		const int m_key;
	public:
		KeyboardEvent(Type type, int key);

		Type type();
		Event::Type eventType();

		int key();
	};
}

#endif