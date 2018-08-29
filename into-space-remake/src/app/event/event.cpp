#include "event.h"

namespace app::event {
	Event::Type Event::eventType() {
		return m_type;
	}
}