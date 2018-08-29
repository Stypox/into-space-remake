#ifndef _INTO_SPACE_REMAKE_APP_EVENT_EVENT_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_EVENT_H_

namespace app::event {
	class Event {		
	public:
		enum Type : char {
			mouseClick,
			mouseRoll,
			keyboard,
		};
	protected:
		const Type m_type;
	public:
		constexpr Event(Type type) : m_type{type} {}
		
		virtual Type eventType();
	};

	constexpr Event::Type operator& (Event::Type a, Event::Type b) {
		return static_cast<Event::Type>(static_cast<int>(a) & static_cast<int>(b));
	}
	constexpr Event::Type operator| (Event::Type a, Event::Type b) {
		return static_cast<Event::Type>(static_cast<int>(a) | static_cast<int>(b));
	}
}

#endif