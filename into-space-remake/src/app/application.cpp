#include "application.h"

namespace app {
	void Application::start() {
		if (!started) {
			m_window = glfwCreateWindow(m_args.width, m_args.height, windowTitle, nullptr, nullptr);
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
			glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
			glfwMakeContextCurrent(m_window);
			glfwSwapInterval(0);
			m_scrollInput.activateWindowCallback();
			started = true;
		}
	}
	void Application::loop() {
		if (started) {
			while (!glfwWindowShouldClose(m_window)) {
				glfwPollEvents();
				m_keysInput.update();
				m_scrollInput.update();
				while (1) {
					switch (m_eventHandler.getKeep()->eventType()) {
						case event::Event::key: {
							std::cout << "Key: " << std::dynamic_pointer_cast<event::Key>(m_eventHandler.get())->type << "\n";
							continue;
						}
						case event::Event::keyLong: {
							std::cout << "KeyLong: " << std::dynamic_pointer_cast<event::KeyLong>(m_eventHandler.get())->type << "\n";
							continue;
						}
						case event::Event::keyPos: {
							auto event = std::dynamic_pointer_cast<event::KeyPos>(m_eventHandler.get());
							std::cout << "KeyPos: " << event->type << " - X:" << event->x << "; Y:" << event->y << "\n";
							continue;
						}
						case event::Event::keyPosLong: {
							auto event = std::dynamic_pointer_cast<event::KeyPosLong>(m_eventHandler.get());
							std::cout << "KeyPosLong: " << event->type << " - X:" << event->x << "; Y:" << event->y << "\n";
							continue;
						}
						case event::Event::empty: {
							m_eventHandler.get();
							break;
						}
						default: {
							std::cout << "Unknown event\n";
							m_eventHandler.get();
							break;
						}
					}
					break;
				}

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

		}, {
			
		}}, m_scrollInput{m_window, m_eventHandler, 1, 1} {}
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