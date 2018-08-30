#include "event.h"

namespace app::event {
	Event::Type Event::eventType() const {
		return type;
	}
	Event::operator bool() const {
		return type != Type::empty;
	}
}