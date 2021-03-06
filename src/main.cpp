#include <iostream>

#include "app/application.hpp"
#include "app/arguments.hpp"

int main(int argc, char const* argv[]) {
	//run and catch exceptions
	int exitValue;
	try {
		app::Arguments::parse(argc, argv);
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

	return exitValue;
}
