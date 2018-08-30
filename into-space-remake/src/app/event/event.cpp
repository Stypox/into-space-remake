#include "event.h"

namespace app::event {
	Event::Type Event::eventType() const {
		return type;
	}
}