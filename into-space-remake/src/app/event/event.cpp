#include "event.h"

namespace app::event {
	Event::Type Event::type() {
		return m_type;
	}
}