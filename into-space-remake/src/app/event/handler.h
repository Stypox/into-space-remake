#ifndef _INTO_SPACE_REMAKE_APP_EVENT_HANDLER_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_HANDLER_H_

#include <queue>
#include <stack>
#include <memory>

#include "event.h"

namespace app::event {
	class Handler {
		std::queue<std::shared_ptr<Event>> m_events;
	public:
		Handler() = default;
		~Handler() = default;

		Handler(const Handler& other) = default;
		Handler& operator=(const Handler& other) = default;
		Handler(Handler&& other) = default;
		Handler& operator=(Handler&& other) = default;

		void push(Event* event);

		std::shared_ptr<Event> get();
		std::shared_ptr<Event> getKeep();
	};
}

#endif