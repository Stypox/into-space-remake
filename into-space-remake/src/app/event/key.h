#ifndef _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_
#define _INTO_SPACE_REMAKE_APP_EVENT_KEYBOARD_H_

#include "../input/key.h"

namespace app::event {
	struct Key {
		enum Type : char {
			press,
			doublePress,
			release,
		};

		const Type type;
		const input::Key key;

		constexpr Key(Type type, input::Key key) :
			type{type}, key{key} {}
	};

	struct KeyLong {
		enum Type : char {
			press,
			release,
		};

		const Type type;
		const input::Key key;
		const float delayAfterAction, delayInBetween;

		constexpr explicit KeyLong(Type type, input::Key key) :
			type{type}, key{key},
			delayAfterAction{}, delayInBetween{} {}
		constexpr KeyLong(Type type, input::Key key, float delayAfterAction, float delayInBetween) :
			type{type}, key{key},
			delayAfterAction{delayAfterAction}, delayInBetween{delayInBetween} {}
	};

	struct KeyPos : Key {
		const double x, y;

		constexpr explicit KeyPos(Type type, input::Key key) :
			Key{type, key},
			x{}, y{} {}
		constexpr KeyPos(Key::Type type, input::Key key, double x, double y) :
			Key{type, key},
			x{x}, y{y} {}
	};

	struct KeyPosLong : KeyLong {
		const double x, y;

		constexpr explicit KeyPosLong(KeyLong::Type type, input::Key key) :
			KeyLong{type, key},
			x{}, y{} {}
		constexpr KeyPosLong(KeyLong::Type type, input::Key key, double x, double y, float delayAfterAction, float delayInBetween) :
			KeyLong{type, key, delayAfterAction, delayInBetween},
			x{x}, y{y} {}
	};
}

namespace std {
	template<>
	struct hash<app::event::Key> { size_t operator()(const app::event::Key& k) {
		return (k.type << 8) | k.key;
	}};
	template<>
	struct hash<app::event::KeyLong> { size_t operator()(const app::event::KeyLong& k) {
		return (k.type << 8) | k.key;
	}};
	template<>
	struct hash<app::event::KeyPos> { size_t operator()(const app::event::KeyPos& k) {
		return (k.type << 8) | k.key;
	}};
	template<>
	struct hash<app::event::KeyPosLong> { size_t operator()(const app::event::KeyPosLong& k) {
		return (k.type << 8) | k.key;
	}};
}

#endif