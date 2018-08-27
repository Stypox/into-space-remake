#ifndef _INTO_SPACE_REMAKE_APP_H_
#define _INTO_SPACE_REMAKE_APP_H_

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

namespace app {
	class Application {
		GLFWwindow* window;

		void loop();

	public:
		Application(const std::vector<std::string>& arguments);
		~Application();
		
		int run();
	};
}

#endif