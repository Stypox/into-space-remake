#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_H_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_H_

#include <vector>
#include <string>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "arguments.h"

namespace app {
	constexpr const char * windowTitle = "Into Space remake";

	class Application {
		Arguments m_args;
		GLFWwindow* m_window;

		bool started;

		void start();
		void loop();
		void terminate();

	public:
		Application(const std::vector<std::string>& arguments);
		~Application();
		
		int run();
		void exit(int exitValue);
	};
}

#endif