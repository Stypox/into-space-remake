#ifndef _INTO_SPACE_REMAKE_APP_APPSETTINGS_H_
#define _INTO_SPACE_REMAKE_APP_APPSETTINGS_H_

#include <vector>
#include <string>

namespace app {
	struct Settings {
		Settings(const std::vector<std::string>& arguments);
	};
}

#endif