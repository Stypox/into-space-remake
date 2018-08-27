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

	std::string lines = "------";
	for (size_t i = 0; i < arguments[0].length(); ++i)
		lines += "-";
	std::cout << lines << "\nStart " << arguments[0] << "\n" << lines << "\n";

	glfwInit();
	glewInit();
	app::Application app {arguments};
	int exitValue = app.run();
	glfwTerminate();

	std::cout << lines << "\n End " << arguments[0] << " \n" << lines << "\n";
	return exitValue;
}
