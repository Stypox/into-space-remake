#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_HPP_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_HPP_

#include <vector>
#include <tuple>
#include <GLFW/glfw3.h>
#include <stypox/event_notifier.hpp>

#include "key.hpp"
#include "../event/key.hpp"

namespace app::input {
	class Keys {
		struct KeyData {
			const Key key;
			bool lastState;

			constexpr KeyData(Key key) :
				key{key}, lastState{false} {}
		};
		struct KeyDoublePressData {
			const Key key;
			bool lastState;
			float lastPressed;

			constexpr KeyDoublePressData(Key key, float doublePressDelay) :
				key{key}, lastState{false},
				lastPressed{-3 * doublePressDelay} {}
		};
		struct KeyLongData {
			const Key key;
			const float delayAfterAction, delayInBetween;
			bool lastState;
			float lastAction;

			constexpr KeyLongData(Key key, float delayAfterAction, float delayInBetween) :
				key{key}, delayAfterAction{delayAfterAction},
				delayInBetween{delayInBetween}, lastState{false},
				lastAction{0.0f} {}
		};

		GLFWwindow*& m_window;
		stypox::EventNotifier& m_eventNotifier;
		float m_doublePressDelay;

		bool m_keysStatus[Key::last + 1];

		//data of listeners (P -> track position, M -> mouse key)

		//press
		std::vector<KeyData> m_dataPress,						// press type, no position tracking
							 m_dataPressP;						// press type, position tracking
		//doublePress
		std::vector<KeyDoublePressData> m_dataDoublePress,		// doublePress type, no position tracking
										m_dataDoublePressP;		// doublePress type, position tracking
		//release
		std::vector<KeyData> m_dataRelease,						// release type, no position tracking
							 m_dataReleaseP;					// release type, position tracking
		//longPress
		std::vector<KeyLongData> m_dataLongPress,				// longPress type, no position tracking
								 m_dataLongPressP;				// longPress type, position tracking
		//longRelease
		std::vector<KeyLongData> m_dataLongRelease,				// longRelease type, no position tracking
								 m_dataLongReleaseP;			// longRelease type, position tracking

		float m_time;
		double m_xCursor, m_yCursor;

		void updateKeysStatus();

		void updatePress();
		void updateDoublePress();
		void updateRelease();
		void updateLongPress();
		void updateLongRelease();
	public:
		Keys(GLFWwindow*& window, stypox::EventNotifier& eventNotifier, float doublePressDelay);
		Keys(GLFWwindow*& window, stypox::EventNotifier& eventNotifier, float doublePressDelay,
			std::initializer_list<std::tuple<event::Key::Type, Key, bool>> listeners, // see addListener() with 3 arguments
			std::initializer_list<std::tuple<event::KeyLong::Type, Key, bool, float, float>> longListeners); // see addListener() with 5 arguments

		inline void setDoublePressDelay(float doublePressDelay) { m_doublePressDelay = doublePressDelay; }

		void addListener(event::Key::Type type, Key key, bool trackPosition);
		void addListener(event::KeyLong::Type type, Key key, bool trackPosition, float delayAfterAction, float delayInBetween);

		void update();

		inline bool isPressed(int key) { return glfwGetKey(m_window, key); }
	};

}

#endif