#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_HPP_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stypox/event_notifier.hpp>

#include "stypox/frequency.hpp"
#include "input/keys.hpp"
#include "input/mousemove.hpp"
#include "input/scroll.hpp"
#include "../game/game.hpp"

namespace app {
	constexpr const char * windowTitle = "Into Space! remake";

	class Application {
	public:
		static stypox::EventNotifier eventNotifier;

	private:
		static GLFWwindow* m_window;

		static stypox::FrequencyCount m_framerate;

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