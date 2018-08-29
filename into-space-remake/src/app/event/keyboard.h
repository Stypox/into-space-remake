#ifndef _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_

#include "event.h"

namespace app::event {
	class KeyboardEvent : public Event {
		const int m_key;
	public:
		KeyboardEvent(Event::Type type, int key);

		Event::Type type();
		int key();
	};
}

#endif