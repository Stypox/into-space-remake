#include "application.h"

namespace app {
	Application::Application(const std::vector<std::string>& arguments) :
	m_settings{arguments}, m_window{nullptr} {}
	Application::~Application() {}

	void Application::loop() {
		
	}
	int Application::run() {
		//create window
		//generate starting point
		loop();
		//closing tasks
		//close window
		return 0;
	}
}