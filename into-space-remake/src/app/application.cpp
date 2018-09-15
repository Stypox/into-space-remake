#include "application.h"

#include <vector>
#include <string>
#include <iostream>

#include "arguments.h"
#include "event/scroll.h"
#include "event/mousemove.h"
#include "../render/renderer.h"
#include "../render/items.h"
#include "../render/movables.h"
#include "../game/entity/movable/rocket.h"
#include "../game/world/chunk.h"

#include "../misc/random.h"

namespace app {
	GLFWwindow* Application::m_window{nullptr};

	misc::FrequencyNr Application::m_framerate{1000};

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
			glClearColor(0.0, 0.86, 0.0, 1.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			render::Items itemsRenderer;
			std::vector<game::entity::Item> items{};
			auto entities = game::world::Chunk{0, 0}.generate();
			for (auto&& entity : entities) items.push_back(*dynamic_cast<game::entity::Item*>(entity.get()));
			entities = game::world::Chunk{-1, 0}.generate();
			for (auto&& entity : entities) items.push_back(*dynamic_cast<game::entity::Item*>(entity.get()));
			entities = game::world::Chunk{-1, -1}.generate();
			for (auto&& entity : entities) items.push_back(*dynamic_cast<game::entity::Item*>(entity.get()));
			entities = game::world::Chunk{0, -1}.generate();
			for (auto&& entity : entities) items.push_back(*dynamic_cast<game::entity::Item*>(entity.get()));

			render::Movables movablesRenderer;
			std::vector<std::unique_ptr<game::entity::movable::Movable>> movables{};
			movables.emplace_back(new game::entity::movable::Rocket{});


			int frames = 0;
			while (!glfwWindowShouldClose(m_window)) {
				glClear(GL_COLOR_BUFFER_BIT);
				glfwPollEvents();
				m_keysInput.update();
				m_mouseMoveInput.update();
				m_scrollInput.update();
				m_framerate.ping();

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
				movablesRenderer.draw(movables);

				if (Arguments::verbosity == Gravity::info && ++frames > 1000) {
					glfwSetWindowTitle(m_window, std::to_string(m_framerate.frequency()).c_str());
					frames = 0;
				}

				if (Arguments::verbosity >= Gravity::error)
					if (GLenum e = glGetError(); e) debug(Gravity::error, "MainLoop", "OpenGL" + std::to_string(e));
					
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