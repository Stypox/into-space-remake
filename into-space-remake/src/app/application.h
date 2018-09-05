#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_H_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_H_

#include <vector>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "arguments.h"
#include "event/handler.h"
#include "input/keys.h"
#include "input/mousemove.h"
#include "input/scroll.h"

namespace app {
	constexpr const char * windowTitle = "Into Space remake";

	class Application {
		static GLFWwindow* m_window;

		static event::Handler m_eventHandler;
		static input::Keys m_keysInput;
		static input::MouseMove m_mouseMoveInput;
		static input::Scroll m_scrollInput;

		static bool started;

		static void start();
		static void loop();
		static void terminate();

	public:
		static int run();
		static void exit(int exitValue);
	};
}

#endif