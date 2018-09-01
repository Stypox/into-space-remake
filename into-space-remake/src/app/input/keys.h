#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_

#include <vector>
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

		//data of listeners (P -> track position, M -> mouse key)

		//press
		std::vector<KeyData> m_dataPress,						// press type, no position tracking, keyboard key
							 m_dataPressM,						// press type, no position tracking, keyboard key
							 m_dataPressP,						// press type, position tracking, keyboard key
							 m_dataPressPM;						// press type, position tracking, mouse key
		//doublePress
		std::vector<KeyDoublePressData> m_dataDoublePress,		// doublePress type, no position tracking, keyboard key
										m_dataDoublePressM,		// doublePress type, no position tracking, mouse key
										m_dataDoublePressP,		// doublePress type, position tracking, keyboard key
										m_dataDoublePressPM;	// doublePress type, position tracking, mouse key
		//release
		std::vector<KeyData> m_dataRelease,						// release type, no position tracking, keyboard key
							 m_dataReleaseM,					// release type, no position tracking, mouse key
							 m_dataReleaseP,					// release type, position tracking, keyboard key
							 m_dataReleasePM;					// release type, position tracking, mouse key
		//longPress
		std::vector<KeyLongData> m_dataLongPress,				// longPress type, no position tracking, keyboard key
								 m_dataLongPressM,				// longPress type, no position tracking, mouse key
								 m_dataLongPressP,				// longPress type, position tracking, keyboard key
								 m_dataLongPressPM;				// longPress type, position tracking, mouse key
		//longRelease
		std::vector<KeyLongData> m_dataLongRelease,				// longRelease type, no position tracking, keyboard key
								 m_dataLongReleaseM,			// longRelease type, no position tracking, mouse key
								 m_dataLongReleaseP,			// longRelease type, position tracking, keyboard key
								 m_dataLongReleasePM;			// longRelease type, position tracking, mouse key

		float m_time;
		double m_xCursor, m_yCursor;

		void updatePress();
		void updateDoublePress();
		void updateRelease();
		void updateLongPress();
		void updateLongRelease();
	public:
		Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay);
		Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay,
			std::initializer_list<std::tuple<event::Key::Type, int, bool>> listeners,
			std::initializer_list<std::tuple<event::KeyLong::Type, int, bool, float, float>> longListeners);

		inline void setDoublePressDelay(float doublePressDelay) { m_doublePressDelay = doublePressDelay; }

		void addListener(event::Key::Type type, int key, bool trackPosition);
		void addListener(event::KeyLong::Type type, int key, bool trackPosition, float delayAfterAction, float delayInBetween);

		void update();

		inline bool isPressed(int key) { return glfwGetKey(m_window, key); }
	};

}

#endif