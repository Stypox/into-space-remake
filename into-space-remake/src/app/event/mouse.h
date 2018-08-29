#ifndef _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_MOUSE_H_

#include "event.h"

namespace app::event {
	class MouseClickEvent : public Event {
	public:
		enum Type : char {
			click,
			doubeClick,
			press,
			release,
			longPress,
		};
	private:
		const Type m_type;
		const int m_key;
		const int m_x, m_y;
	public:
		MouseClickEvent(Type type, int key, int x, int y);
		
		Type type();
		Event::Type eventType();

		int key();
		int x();
		int y();
	};

	class MouseRollEvent : public Event {
		const int m_offset;
		const int m_x, m_y;
	public:
		MouseRollEvent(int offset, int x, int y);
		
		Event::Type eventType();

		int offset();
		int x();
		int y();
	};
}

#endif