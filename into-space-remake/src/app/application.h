#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_H_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../misc/frequency.h"
#include "event/handler.h"
#include "input/keys.h"
#include "input/mousemove.h"
#include "input/scroll.h"

namespace app {
	constexpr const char * windowTitle = "Into Space remake";

	class Application {
		static GLFWwindow* m_window;

		static misc::FrequencyNr m_framerate;

		static event::Handler m_eventHandler;
		static input::Keys m_keysInput;
		static input::MouseMove m_mouseMoveInput;
		static input::Scroll m_scrollInput;

		static bool m_initialized;

		static void init();
		static void loop();
		static void terminate();

		static void framebufferSizeCallback(GLFWwindow*, int width, int height);

	public:
		static int run();
		static void exit(int exitValue);
	};
}

#endif