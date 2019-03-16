#ifndef _INTO_SPACE_REMAKE_MISC_GET_CURRENT_MONITOR_HPP_
#define _INTO_SPACE_REMAKE_MISC_GET_CURRENT_MONITOR_HPP_

#include <GLFW/glfw3.h>

namespace misc {
	GLFWmonitor* getCurrentMonitor(GLFWwindow* window);
}

#endif