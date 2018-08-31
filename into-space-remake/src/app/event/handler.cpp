#include "handler.h"

namespace app::event {
	std::shared_ptr<Event> Handler::get() {
		if (m_events.empty()) {
			return std::shared_ptr<Event>{new Event{Event::Type::empty}};
		}
		else {
			std::shared_ptr<Event> tempEvent{m_events.front()};
			m_events.pop();
			return tempEvent;
		}
	}
	std::shared_ptr<Event> Handler::getKeep() {
		if (m_events.empty()) {
			return std::shared_ptr<Event>{new Event{Event::Type::empty}};
		}
		else {
			return m_events.front();
		}
	}
}