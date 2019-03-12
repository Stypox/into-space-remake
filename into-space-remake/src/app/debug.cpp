#include "debug.hpp"

#include <iostream>

#include "arguments.hpp"

namespace app {
	void debug(Gravity gravity, std::string source, std::string message) {
		if (gravity >= Arguments::verbosity) {
			switch (gravity) {
				case Gravity::info:
					std::clog << "[" << source << "] info: " << message << "\n";
					break;
				case Gravity::warning:
					std::clog << "[" << source << "] warning: " << message << "\n";
					break;
				case Gravity::error:
					std::cerr << "[" << source << "] ERROR: " << message << "\n";
					break;
				case Gravity::critical:
					std::cerr << "[" << source << "] CRITICAL: " << message << "\n";
					break;
			}
		}
	}
}