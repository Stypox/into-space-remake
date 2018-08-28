#include "application.h"

namespace app {
	void Application::start() {
		if (!started) {

			started = true;
		}
	}
	void Application::loop() {
		if (started) {

		}
	}
	void Application::terminate() {
		if (started) {

			started = false;
		}
	}

	Application::Application(const std::vector<std::string>& arguments) :
	m_settings{arguments}, m_window{nullptr} {}
	Application::~Application() {
		terminate();
	}

	int Application::run() {
		if (m_settings.help) {
			std::cout << helpScreen;
			return 0;
		}
		if (m_settings.errorMessage != "") {
			std::cout << m_settings.errorMessage;
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