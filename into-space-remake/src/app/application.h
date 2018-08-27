#ifndef _INTO_SPACE_REMAKE_APP_APPLICATION_H_
#define _INTO_SPACE_REMAKE_APP_APPLICATION_H_

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "appsettings.h"

namespace app {
	class Application {
		Settings m_settings;
		GLFWwindow* m_window;

		void loop();

	public:
		Application(const std::vector<std::string>& arguments);
		~Application();
		
		int run();
	};
}

#endif