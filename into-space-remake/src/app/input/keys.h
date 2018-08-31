#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_

#include <vector>
#include <utility>
#include <tuple>

#include "../event/key.h"
#include "../event/handler.h"
#include "GLFW/glfw3.h"

namespace app::input {
	constexpr bool pressed = true, notPressed = false;

	class Keys {
		struct KeyData {
			const int key;
			bool lastState;

			constexpr KeyData(int key) :
				key{key}, lastState{notPressed} {}
		};
		struct KeyDoublePressData {
			const int key;
			bool lastState;
			float lastPressed;

			constexpr KeyDoublePressData(int key, float doublePressDelay) :
				key{key}, lastState{notPressed},
				lastPressed{-3 * doublePressDelay} {}
		};
		struct KeyLongData {
			const int key;
			const float delayAfterAction, delayInBetween;
			bool lastState;
			float lastAction;

			constexpr KeyLongData(int key, float delayAfterAction, float delayInBetween) :
				key{key}, delayAfterAction{delayAfterAction},
				delayInBetween{delayInBetween}, lastState{notPressed},
				lastAction{0.0f} {}
		};

		GLFWwindow*& m_window;
		event::Handler& m_eventHandler;
		float m_doublePressDelay;

		std::vector<KeyData> m_keysPressListener;
		std::vector<KeyData> m_mouseKeysPressListener;
		std::vector<KeyDoublePressData> m_keysDoublePressListener;
		std::vector<KeyDoublePressData> m_mouseKeysDoublePressListener;
		std::vector<KeyData> m_keysReleaseListener;
		std::vector<KeyData> m_mouseKeysReleaseListener;
		std::vector<KeyLongData> m_keysLongPressListener;
		std::vector<KeyLongData> m_mouseKeysLongPressListener;
		std::vector<KeyLongData> m_keysLongReleaseListener;
		std::vector<KeyLongData> m_mouseKeysLongReleaseListener;

		float m_time;

		void updatePress();
		void updateDoublePress();
		void updateRelease();
		void updateLongPress();
		void updateLongRelease();
	public:
		Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay);
		Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay,
			std::initializer_list<std::pair<event::Key::Type, int>> listeners,
			std::initializer_list<std::tuple<event::KeyLong::Type, int, float, float>> longListeners);

		inline void setDoublePressDelay(float doublePressDelay) { m_doublePressDelay = doublePressDelay; }

		void addListener(event::Key::Type type, int key);
		void addListener(event::KeyLong::Type type, int key, float delayAfterAction, float delayInBetween);

		void update();

		inline bool isPressed(int key) { return glfwGetKey(m_window, key); }
	};
}

#endif