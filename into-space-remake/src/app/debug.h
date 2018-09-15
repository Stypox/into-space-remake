#ifndef _INTO_SPACE_REMAKE_APP_DEBUG_H_
#define _INTO_SPACE_REMAKE_APP_DEBUG_H_

#include <string>

namespace app {
	enum class Gravity : char {
		info = 0,
		warning = 1,
		error = 2,
		critical = 3,
		max = critical,
	};

	void debug(Gravity gravity, std::string source, std::string message);
}

#endif