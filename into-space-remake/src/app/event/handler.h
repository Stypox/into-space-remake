#ifndef _INTO_SPACE_REMAKE_APP_EVENT_HANDLER_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_HANDLER_H_

#include <queue>
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

		template<typename T, typename = typename std::enable_if<std::is_same<T, Event>::value || std::is_base_of<Event, T>::value>::type>
		inline void push(T* event) { m_events.emplace(dynamic_cast<Event*>(event)); }

		std::shared_ptr<Event> get();
		std::shared_ptr<Event> getKeep();
	};
}

#endif