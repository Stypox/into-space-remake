#ifndef _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_
#define _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_

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
		zoom,
	};

	extern const std::map<BoolArg, std::vector<std::string>> boolArgs;
	extern const std::map<ValueArg, std::vector<std::string>> valueArgs;

	constexpr const char * helpScreen { "\n"
		"Into Space remake by Stypox: Help screen\n"
		"\n"
		"Boolean settings:\n"
		"   -h, --help         shows this screen\n"
		"\n"
		"Value settings: (I = integer, D = decimal)\n"
		"   -v=I --verbosity=I sets verbosity to I (range 0-3); Defaults to 0\n"
		"   -w=I --width=I     sets the window starting width to I; Defaults to 480\n"
		"   -h=I --height=I    sets the window starting height to I; Defaults to 480\n"
		"   -z=D --zoom=D      sets the game starting zoom to D (range 0.5-2.0); Defaults to 1.0\n"
	};

	struct Arguments {
		sp::Tstr errorMessage;

		bool help = false;

		sp::Tuint8 verbosity = 0;
		sp::Tuint16 width = 480;
		sp::Tuint16 height = 480;
		float zoom = 1.0f;

		Arguments(std::vector<std::string> arguments);
	};
}

#endif