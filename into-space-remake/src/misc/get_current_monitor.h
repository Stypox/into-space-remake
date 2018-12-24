#ifndef _INTO_SPACE_REMAKE_MISC_GET_CURRENT_MONITOR_H_
#define _INTO_SPACE_REMAKE_MISC_GET_CURRENT_MONITOR_H_

#include <GLFW/glfw3.h>

namespace misc {
	GLFWmonitor* getCurrentMonitor(GLFWwindow* window);
}

#endif