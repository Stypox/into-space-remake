#ifndef _INTO_SPACE_REMAKE_APP_EVENT_EVENT_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_EVENT_H_

namespace app::event {
	struct Event {
		enum Type : char {
			empty,
			key,
			keyLong,
			keyPos,
			keyPosLong,
			mouseMove,
			scroll,
		};
		
		const Type type;
		
		constexpr Event(Type type) : type{type} {}

		virtual Type eventType() const;
		virtual operator bool() const;
	};

	constexpr Event::Type operator& (Event::Type a, Event::Type b) {
		return static_cast<Event::Type>(static_cast<int>(a) & static_cast<int>(b));
	}
	constexpr Event::Type operator| (Event::Type a, Event::Type b) {
		return static_cast<Event::Type>(static_cast<int>(a) | static_cast<int>(b));
	}
}

#endif