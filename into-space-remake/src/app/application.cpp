#include "application.h"

namespace app {
	void Application::start() {
		if (!started) {
			m_window = glfwCreateWindow(m_args.width, m_args.height, windowTitle, nullptr, nullptr);
			glfwMakeContextCurrent(m_window);
			started = true;
		}
	}
	void Application::loop() {
		if (started) {
			while (!glfwWindowShouldClose(m_window)) {
				if (GLenum e = glGetError(); e) std::cout << "Error " << e << " in game loop: " << gluErrorString(e) << std::flush;
				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}
		}
	}
	void Application::terminate() {
		if (started) {
			glfwDestroyWindow(m_window);
			started = false;
		}
	}

	Application::Application(const std::vector<std::string>& arguments) :
	m_args{arguments}, m_window{nullptr} {}
	Application::~Application() {
		terminate();
	}

	int Application::run() {
		if (m_args.help) {
			std::cout << helpScreen;
			return 0;
		}
		if (m_args.errorMessage != "") {
			std::cout << m_args.errorMessage;
			return 0;
		}
		start();
		loop();
		terminate();
		return 0;
	}
	void Application::exit(int exitValue) {
		terminate();
		::exit(exitValue);
	}
}