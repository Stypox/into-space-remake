#include "mouse.h"

namespace app::event {
	MouseClickEvent::MouseClickEvent(Type type, int key, int x, int y) :
	Event{Event::Type::mouseClick}, m_type{type},
	m_key{key},	m_x{x},
	m_y{y} {}

	MouseClickEvent::Type MouseClickEvent::type() {
		return m_type;
	}
	Event::Type MouseClickEvent::eventType() {
		return Event::m_type;
	}

	int MouseClickEvent::key() {
		return m_key;
	}
	int MouseClickEvent::x() {
		return m_x;
	}
	int MouseClickEvent::y() {
		return m_y;
	}


	MouseRollEvent::MouseRollEvent(int offset, int x, int y) :
	Event{Event::Type::mouseRoll}, m_offset{offset},
	m_x{x}, m_y{y} {}

	Event::Type MouseRollEvent::eventType() {
		return Event::m_type;
	}

	int MouseRollEvent::offset() {
		return m_offset;
	}
	int MouseRollEvent::x() {
		return m_x;
	}
	int MouseRollEvent::y() {
		return m_y;
	}
}