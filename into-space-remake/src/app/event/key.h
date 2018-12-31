#ifndef _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_

#include "event.h"
#include "../input/key.h"

namespace app::event {
	struct Key : public Event {
		enum Type : char {
			press,
			doublePress,
			release,
		};

		const Type type;
		const input::Key key;

		constexpr Key(Type type, input::Key key) :
			Event{Event::Type::key}, type{type},
			key{key} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};

	struct KeyLong : public Event {
		enum Type : char {
			press,
			release,
		};

		const Type type;
		const input::Key key;
		const float delayAfterAction, delayInBetween;

		constexpr KeyLong(Type type, input::Key key, float delayAfterAction, float delayInBetween) :
			Event{Event::Type::keyLong}, type{type},
			key{key}, delayAfterAction{delayAfterAction},
			delayInBetween{delayInBetween} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};

	struct KeyPos : public Event {
		const Key::Type type;
		const input::Key key;
		double x, y;

		constexpr KeyPos(Key::Type type, input::Key key, double x, double y) :
			Event{Event::Type::keyPos}, type{type},
			key{key}, x{x},
			y{y} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};

	struct KeyPosLong : public Event {
		const KeyLong::Type type;
		const input::Key key;
		double x, y;
		const float delayAfterAction, delayInBetween;

		constexpr KeyPosLong(KeyLong::Type type, input::Key key, double x, double y, float delayAfterAction, float delayInBetween) :
			Event{Event::Type::keyPosLong}, type{type},
			key{key}, x{x},
			y{y}, delayAfterAction{delayAfterAction},
			delayInBetween{delayInBetween} {}

		inline Event::Type eventType() const override { return Event::type; }
		inline operator bool() const override { return Event::type != Event::Type::empty; }
	};
}

#endif