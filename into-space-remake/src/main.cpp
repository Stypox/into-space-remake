#include <iostream>
#include <stypox/gl/texture.h>

#include "app/application.h"
#include "app/arguments.h"

int main(int argc, char const* argv[]) {
	//settings
	stypox::gl::Texture2D::setDirectory("./into-space-remake/res/");

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
