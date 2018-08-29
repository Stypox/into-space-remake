#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_

#include "event.h"

namespace app::event {
	class MouseEvent : public Event {
		const int m_key;
		const int m_x, m_y;
	public:
		MouseEvent(Event::Type type, int key, int x, int y);
		
		Event::Type type();
		int key();
		int x();
		int y();
	};
}

#endif