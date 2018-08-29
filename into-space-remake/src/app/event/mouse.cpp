#include "mouse.h"

namespace app::event {
	MouseEvent::MouseEvent(Event::Type type, int key, int x, int y) :
	Event{type | Event::Type::mouse}, m_key{key}, m_x{x}, m_y{y} {}

	Event::Type MouseEvent::type() {
		return Event::m_type;
	}
	int MouseEvent::key() {
		return m_key;
	}
	int MouseEvent::x() {
		return m_x;
	}
	int MouseEvent::y() {
		return m_y;
	}
}