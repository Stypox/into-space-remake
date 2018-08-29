#include "keyboard.h"

namespace app::event {
	KeyboardEvent::KeyboardEvent(Event::Type type, int key) :
	Event{type | Event::Type::keyboard}, m_key{key} {}

	Event::Type KeyboardEvent::type() {
		return Event::m_type;
	}
	int KeyboardEvent::key() {
		return m_key;
	}
}