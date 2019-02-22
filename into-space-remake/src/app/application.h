#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_H_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stypox/event_notifier.h>

#include "../misc/frequency.h"
#include "input/keys.h"
#include "input/mousemove.h"
#include "input/scroll.h"
#include "../game/game.h"

namespace app {
	constexpr const char * windowTitle = "Into Space! remake";

	class Application {
	public:
		static stypox::EventNotifier eventNotifier;

	private:
		static GLFWwindow* m_window;

		static misc::FrequencyNr m_framerate;

		static input::Keys m_keysInput;
		static input::MouseMove m_mouseMoveInput;
		static input::Scroll m_scrollInput;

		static std::unique_ptr<game::Game> m_game;

		static bool m_initialized;
		static bool m_fullscreen;

		static void init();
		static void initInput();

		static void loop();
		static void updateInput();
		static bool processKey(const event::Key key);

		static void toggleFullscreen();
		static void updateFullscreen();

		static void terminate();

		static void framebufferSizeCallback(GLFWwindow*, int width, int height);

	public:
		static int run();
		static void exit(int exitValue);
	};
}

#endif