#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_

#include <vector>
#include <utility>
#include <tuple>
#include <GLFW/glfw3.h>

#include "../event/key.h"
#include "../event/handler.h"

namespace app::input {
	class Keys {
		struct KeyData {
			const int key;
			bool lastState;

			constexpr KeyData(int key) :
				key{key}, lastState{false} {}
		};
		struct KeyDoublePressData {
			const int key;
			bool lastState;
			float lastPressed;

			constexpr KeyDoublePressData(int key, float doublePressDelay) :
				key{key}, lastState{false},
				lastPressed{-3 * doublePressDelay} {}
		};
		struct KeyLongData {
			const int key;
			const float delayAfterAction, delayInBetween;
			bool lastState;
			float lastAction;

			constexpr KeyLongData(int key, float delayAfterAction, float delayInBetween) :
				key{key}, delayAfterAction{delayAfterAction},
				delayInBetween{delayInBetween}, lastState{false},
				lastAction{0.0f} {}
		};

		GLFWwindow*& m_window;
		event::Handler& m_eventHandler;
		float m_doublePressDelay;

		//listeners data
		std::vector<KeyData> m_pressData;
		std::vector<KeyData> m_mousePressData;
		std::vector<KeyDoublePressData> m_doublePressData;
		std::vector<KeyDoublePressData> m_mouseDoublePressData;
		std::vector<KeyData> m_releaseData;
		std::vector<KeyData> m_mouseReleaseData;
		std::vector<KeyLongData> m_longPressData;
		std::vector<KeyLongData> m_mouseLongPressData;
		std::vector<KeyLongData> m_longReleaseData;
		std::vector<KeyLongData> m_mouseLongReleaseData;
		
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