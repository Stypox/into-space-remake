#include "get_current_monitor.h"

#include <algorithm>

namespace misc {
	GLFWmonitor* getCurrentMonitor(GLFWwindow* window) {
		int xWindow, yWindow, wWindow, hWindow;
		glfwGetWindowPos(window, &xWindow, &yWindow);
		glfwGetWindowSize(window, &wWindow, &hWindow);

		int nMonitors;
		GLFWmonitor** monitors = glfwGetMonitors(&nMonitors);

		int bestMonitorOverlap = 0;
		GLFWmonitor* bestMonitor = nullptr;
		for (int i = 0; i < nMonitors; i++) {
			const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);

			int xMonitor, yMonitor, wMonitor, hMonitor;
			glfwGetMonitorPos(monitors[i], &xMonitor, &yMonitor);
			wMonitor = mode->width;
			hMonitor = mode->height;

			int monitorOverlap =
				std::max(0, std::min(xWindow + wWindow, xMonitor + wMonitor) - std::max(xWindow, xMonitor)) *
				std::max(0, std::min(yWindow + hWindow, yMonitor + hMonitor) - std::max(yWindow, yWindow));

			if (bestMonitorOverlap < monitorOverlap) {
				bestMonitorOverlap = monitorOverlap;
				bestMonitor = monitors[i];
			}
		}

		return bestMonitor;
	}
}