#include "application.h"

namespace app {
	void Application::start() {
		if (!started) {
			m_window = glfwCreateWindow(m_args.width, m_args.height, windowTitle, nullptr, nullptr);
			glfwMakeContextCurrent(m_window);
			m_keysInput.setWindow(m_window);
			started = true;
		}
	}
	void Application::loop() {
		if (started) {
			while (!glfwWindowShouldClose(m_window)) {
				glfwPollEvents();
				m_keysInput.update();
				if (*m_eventHandler.getKeep())
					std::cout << std::dynamic_pointer_cast<event::Key>(m_eventHandler.get())->type << "\n";

				if (GLenum e = glGetError(); e) std::cout << "Error " << e << " in game loop: " << gluErrorString(e) << std::flush;
				glfwSwapBuffers(m_window);
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
		m_args{arguments}, m_window{nullptr},
		m_eventHandler{}, m_keysInput{m_window, m_eventHandler, m_args.doubleClickDelay, {
			{event::Key::press, GLFW_KEY_W},
			{event::Key::release, GLFW_KEY_A},
			{event::Key::doublePress, GLFW_KEY_S},
		}} {}
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