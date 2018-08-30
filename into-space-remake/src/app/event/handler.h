#ifndef _INTO_SPACE_REMAKE_APP_EVENT_HANDLER_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_HANDLER_H_

#include <queue>
#include <stack>
#include <memory>

#include "event.h"

namespace app::event {
	class EventHandler {
		std::queue<std::shared_ptr<Event>> m_events;
	public:
		EventHandler() = default;
		~EventHandler() = default;

		EventHandler(const EventHandler& other) = default;
		EventHandler& operator=(const EventHandler& other) = default;
		EventHandler(EventHandler&& other) = default;
		EventHandler& operator=(EventHandler&& other) = default;

		void push(Event* event);

		std::shared_ptr<Event> get();
		std::shared_ptr<Event> getKeep();
	};
}

#endif