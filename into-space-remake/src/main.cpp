#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "app/application.h"
#include "stypox/range.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> arguments;
	for (int arg : sp::range(0, argc))
		arguments.push_back(argv[arg]);

	std::string lines(6 + arguments[0].length(), '-');
	std::cout << lines << "\nStart " << arguments[0] << "\n" << lines << "\n";

	int exitValue;
	try {
		glfwInit();
		glewInit();
		app::Application app {arguments};
		exitValue = app.run();
		glfwTerminate();
	}
	catch (...) {
		std::cout << "exception";
		exitValue = 1;
	}

	std::cout << lines << "\n End " << arguments[0] << " \n" << lines << "\n";
	return exitValue;
}
