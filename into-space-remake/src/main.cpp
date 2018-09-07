#include <iostream>
#include <range.h>

#include "app/application.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> arguments;
	for (int arg : sp::range(0, argc))
		arguments.push_back(argv[arg]);

	std::string lines(6 + arguments[0].length(), '-');
	std::cout << lines << "\nStart " << arguments[0] << "\n" << lines << "\n";

	int exitValue;
	try {
		app::Arguments::parse(arguments);
		exitValue = app::Application::run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Exception: " << e.what() << "\n";
		exitValue = 1;
	}
	catch (...) {
		std::cout << "Unknown exception\n";
		exitValue = 2;
	}

	std::cout << lines << "\n End " << arguments[0] << " \n" << lines << "\n";
	return exitValue;
}
