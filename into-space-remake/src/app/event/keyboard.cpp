#include "keyboard.h"

namespace app::event {
	KeyboardEvent::KeyboardEvent(Type type, int key) :
	Event{Event::Type::keyboard}, m_type{type},
	m_key{key} {}

	KeyboardEvent::Type KeyboardEvent::type() {
		return m_type;
	}
	Event::Type KeyboardEvent::eventType() {
		return Event::m_type;
	}

	int KeyboardEvent::key() {
		return m_key;
	}
}