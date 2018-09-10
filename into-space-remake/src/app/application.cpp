#include "application.h"

namespace app {
	GLFWwindow* Application::m_window{nullptr};

	event::Handler Application::m_eventHandler{};
	input::Keys Application::m_keysInput{m_window, m_eventHandler, Arguments::doubleClickDelay, {

	}, {

	}};
	input::MouseMove Application::m_mouseMoveInput{m_window, m_eventHandler, 0, 0};
	input::Scroll Application::m_scrollInput{m_window, m_eventHandler, 0, 0};

	bool Application::m_initialized{false};
	


	void Application::init() {
		if (!m_initialized) {
			if (int errorCode = glfwInit(); !errorCode)
				throw std::runtime_error{"Unable to initialize glfw, error " + std::to_string(errorCode)};

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			m_window = glfwCreateWindow(Arguments::width, Arguments::height, windowTitle, nullptr, nullptr);
			if (m_window == nullptr) {
				glfwTerminate();
				throw std::runtime_error{"Unable to create glfw window."};
			}

			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
			glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
			glfwMakeContextCurrent(m_window);
			glfwSwapInterval(0);
			
			glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
			m_scrollInput.activateWindowCallback();

			if (int errorCode = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); !errorCode) {
				glfwDestroyWindow(m_window);
				glfwTerminate();
				throw std::runtime_error{"Unable to initialize glad, error " + std::to_string(errorCode)};
			}

			render::Renderer::updateScreenSize(Arguments::width, Arguments::height);
			m_initialized = true;
		}
	}
	void Application::loop() {
		if (m_initialized) {
			glClearColor(0.0, 1.0, 0.0, 1.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			render::Items itemsRenderer;
			std::vector<game::entity::Item> items{};
			items.emplace_back(game::entity::Item::fuel0, -0.6, -0.2);
			items.emplace_back(game::entity::Item::fuel1, -0.4, 0.0);
			items.emplace_back(game::entity::Item::fuel2, -0.2, -0.7);
			items.emplace_back(game::entity::Item::money0, 0.0, 0.9);
			items.emplace_back(game::entity::Item::money1, 0.2, -0.4);
			items.emplace_back(game::entity::Item::money2, 0.4, -0.1);
			items.emplace_back(game::entity::Item::repair, 0.6, 0.3);

			while (!glfwWindowShouldClose(m_window)) {
				glClear(GL_COLOR_BUFFER_BIT);
				glfwPollEvents();
				m_keysInput.update();
				m_mouseMoveInput.update();
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
						case event::Event::scroll: {
							auto event = std::dynamic_pointer_cast<event::Scroll>(m_eventHandler.get());
							std::cout << "Scroll: " << event->type << " - Offset:" << event->offset << "; X:" << event->xCursor << "; Y:" << event->yCursor << "\n";
							continue;
						}
						case event::Event::mouseMove: {
							auto event = std::dynamic_pointer_cast<event::MouseMove>(m_eventHandler.get());
							std::cout << "MouseMove: " << event->type << " - Offset:" << event->offset << "; Position:" << event->position << "\n";
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

				itemsRenderer.draw(items);

				if (GLenum e = glGetError(); e) std::cout << "Error " << e << " in game loop\n";
				glfwSwapBuffers(m_window);
			}
		}
	}
	void Application::terminate() {
		if (m_initialized) {
			glfwDestroyWindow(m_window);
			glfwTerminate();
			m_initialized = false;
		}
	}

	void Application::framebufferSizeCallback(GLFWwindow*, int width, int height) {
		if (m_initialized) {
			glViewport(0, 0, width, height);
			render::Renderer::updateScreenSize(width, height);
	}
	}

	int Application::run() {
		if (Arguments::help) {
			std::cout << helpScreen;
			return 0;
		}
		if (Arguments::errorMessage != "") {
			std::cout << Arguments::errorMessage;
			return 0;
		}
		init();
		loop();
		terminate();
		return 0;
	}
	void Application::exit(int exitValue) {
		terminate();
		::exit(exitValue);
	}
}