#ifndef _INTO_SPACE_REMAKE_APP_EVENT_EVENT_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_EVENT_H_

namespace app::event {
	class Event {		
	public:
		enum Type {
			mouse = 1,
			keyboard = 2,

			click = 8,
			doubleClick = 16,
			press = 32,
			release = 64,
			longPress = 128,
			
			mClick = 9,
			mDoubleClick = 17,
			mPress = 33,
			mRelease = 65,
			mLongPress = 129,

			kClick = 10,
			kDoubleClick = 18,
			kPress = 34,
			kRelease = 66,
			kLongPress = 130,
		};
	protected:
		const Type m_type;
	public:
		constexpr Event(Type type) : m_type{type} {}
		
		virtual Type type();
	};

	constexpr Event::Type operator& (Event::Type a, Event::Type b) {
		return static_cast<Event::Type>(static_cast<int>(a) & static_cast<int>(b));
	}
	constexpr Event::Type operator| (Event::Type a, Event::Type b) {
		return static_cast<Event::Type>(static_cast<int>(a) | static_cast<int>(b));
	}
}

#endif