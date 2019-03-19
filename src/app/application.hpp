#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_HPP_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stypox/frequency.hpp>
#include <stypox/key_input.hpp>
#include <stypox/mousemove_input.hpp>
#include <stypox/scroll_input.hpp>

#include "../game/game.hpp"

namespace app {
	constexpr const char * windowTitle = "Into Space! remake";

	class Application {
	public:
		static stypox::EventNotifier eventNotifier;

	private:
		static GLFWwindow* m_window;

		static stypox::FrequencyCount m_framerate;

		static stypox::KeyInput m_keyInput;
		static stypox::MouseMoveInput m_mouseMoveInput;
		static stypox::ScrollInput m_scrollInput;

		static std::unique_ptr<game::Game> m_game;

		static bool m_initialized;
		static bool m_fullscreen;

		static void init();
		static void initInput();

		static void loop();
		static void updateInput();

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