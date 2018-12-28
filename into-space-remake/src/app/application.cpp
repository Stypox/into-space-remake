#include "application.h"

#include <string>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "arguments.h"
#include "debug.h"
#include "../rend/renderer.h"
#include "../misc/get_current_monitor.h"

namespace app {
	GLFWwindow* Application::m_window{nullptr};

	misc::FrequencyNr Application::m_framerate{1000};

	event::Handler Application::m_eventHandler{};
	input::Keys Application::m_keysInput{m_window, m_eventHandler, Arguments::doubleClickDelay, {
		{event::Key::press, GLFW_KEY_F11, false},
		{event::Key::press, GLFW_KEY_ESCAPE, false}
	}, {

	}};
	input::MouseMove Application::m_mouseMoveInput{m_window, m_eventHandler, 0, 0};
	input::Scroll Application::m_scrollInput{m_window, m_eventHandler, 0, 0};

	std::unique_ptr<game::Game> Application::m_game{nullptr};

	bool Application::m_initialized{false};
	bool Application::m_fullscreen{false};
	


	void Application::init() {
		if (!m_initialized) {
			// GLFW initialization
			if (int errorCode = glfwInit(); !errorCode)
				throw std::runtime_error{"Unable to initialize glfw, error " + std::to_string(errorCode)};
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			// window creation with GLFW
			m_window = glfwCreateWindow(Arguments::width, Arguments::height, windowTitle, nullptr, nullptr);
			if (m_window == nullptr) {
				glfwTerminate();
				throw std::runtime_error{"Unable to create glfw window."};
			}

			// context settings
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
			glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
			glfwMakeContextCurrent(m_window);
			glfwSwapInterval(0);
			
			glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
			m_scrollInput.activateWindowCallback();

			// GLAD initialization
			if (int errorCode = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); !errorCode) {
				glfwDestroyWindow(m_window);
				glfwTerminate();
				throw std::runtime_error{"Unable to initialize glad, error " + std::to_string(errorCode)};
			}

			// ImGui initialization
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui_ImplGlfw_InitForOpenGL(m_window, true);
			ImGui_ImplOpenGL3_Init("#version 330 core");
			ImGui::StyleColorsClassic();

			// render engine initialization
			rend::Renderer::init();
			rend::Renderer::updateScreenSize(Arguments::width, Arguments::height);

			m_game.reset(new game::Game{});

			initInput();

			m_initialized = true;
		}
	}
	void Application::initInput() {
		if (Arguments::wasd) {
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_W,		false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_W,		false);
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_A,		false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_A,		false);
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_S,		false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_S,		false);
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_D,		false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_D,		false);
		}
		else {
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_UP,	false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_UP,	false);
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_LEFT,	false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_LEFT,	false);
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_DOWN,	false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_DOWN,	false);
			m_keysInput.addListener(event::Key::Type::press,	GLFW_KEY_RIGHT,	false);
			m_keysInput.addListener(event::Key::Type::release,	GLFW_KEY_RIGHT,	false);
		}
	}

	void Application::loop() {
		if (m_initialized) {
			glClearColor(0.0625, 0.0625, 0.0625, 1.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			int frames = 0;
			while (!glfwWindowShouldClose(m_window)) {
				glClear(GL_COLOR_BUFFER_BIT);
				m_framerate.ping();

				updateInput();

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				delegateEvents();

				m_game->update();
				rend::Renderer::moveCameraToRocket(m_game->rocketX(), m_game->rocketY());
				
				rend::Renderer::render();
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
	void Application::updateInput() {
		glfwPollEvents();
		m_keysInput.update();
		m_mouseMoveInput.update();
		m_scrollInput.update();
	}
	bool Application::process(const std::shared_ptr<event::Event>& event) {
		if (event->type == event::Event::key) {
			switch (event::Key* keyEvent = dynamic_cast<event::Key*>(event.get()); keyEvent->key) {
			case GLFW_KEY_F11: {
				m_fullscreen = !m_fullscreen;
				debug(Gravity::info, "Application", "Fullscreen is now " + std::string{m_fullscreen ? "active" : "inactive"});

				updateFullscreen();
				m_game->pause();
				return true;
			}
			}
		}
		return false;
	}
	void Application::delegateEvents() {
		while (1) {
			auto event = m_eventHandler.getKeep();
			if (*event) {
				process(event) ||
				m_game->process(event);

				m_eventHandler.get();
			}
			else break;
		}
	}
	void Application::updateFullscreen() {
		GLFWmonitor* currentMonitor = misc::getCurrentMonitor(m_window);
		if (m_fullscreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);
			glfwSetWindowMonitor(m_window, currentMonitor, 0, 0, mode->width, mode->height, 0);
		}
		else {
			int xMonitor, yMonitor;
			glfwGetMonitorPos(currentMonitor, &xMonitor, &yMonitor);
			glfwSetWindowMonitor(m_window, nullptr, xMonitor, yMonitor, Arguments::width, Arguments::height, 0);
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
			rend::Renderer::updateScreenSize(width, height);
		}
	}

	int Application::run() {
		if (Arguments::help) {
			std::cout << Arguments::helpScreen();
			return 0;
		}
		if (!Arguments::errorMessage.empty()) {
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