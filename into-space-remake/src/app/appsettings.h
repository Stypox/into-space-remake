#ifndef _INTO_SPACE_REMAKE_APP_APPSETTINGS_H_
#define _INTO_SPACE_REMAKE_APP_APPSETTINGS_H_

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <stypox/range.h>
#include <stypox/basicTypes.h>

namespace app {
	enum class BoolArg {
		help,
	};
	enum class ValueArg {
		verbosity,
		width,
		height,
	};

	extern const std::map<BoolArg, std::vector<std::string>> boolArgs;
	extern const std::map<ValueArg, std::vector<std::string>> valueArgs;
	constexpr const char * helpScreen {
		"Into Space remake by Stypox: Help screen\n"
		"\n"
		"Boolean settings:\n"
		"   -h, --help         shows this screen\n"
		"\n"
		"Value settings:\n"
		"   -v=V --verbosity=V sets verbosity to V (range 0-3); Defaults to 0\n"
		"   -w=V --width=V     sets the window starting width to V; Defaults to 480\n"
		"   -h=V --height=V    sets the window starting height to V; Defaults to 480\n"
	};

	struct Settings {
		sp::Tstr errorMessage;

		bool help = false;

		sp::Tuint8 verbosity = 0;
		sp::Tuint16 width = 480;
		sp::Tuint16 height = 480;

		Settings(std::vector<std::string> arguments);
	};
}

#endif