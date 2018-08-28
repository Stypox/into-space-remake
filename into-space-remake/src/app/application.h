#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_H_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_H_

#include <vector>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>

#include "appsettings.h"

namespace app {
	class Application {
		Settings m_settings;
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