#ifndef _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_
#define _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_

#include <vector>
#include <string>
#include <map>
#include <basicTypes.h>

namespace app {
	enum class BoolArg {
		help,
	};
	enum class ValueArg {
		verbosity,
		width,
		height,
		zoom,
		doubleClickDelay,
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
		"   -v=I --verbosity=I sets verbosity to I (range 0-3); defaults to 0\n"
		"   -w=I --width=I     sets the window starting width to I; defaults to 480\n"
		"   -h=I --height=I    sets the window starting height to I; defaults to 480\n"
		"   -z=D --zoom=D      sets the game starting zoom to D (range 0.5-2.0); defaults to 1.0\n"
		"        --dc-delay=D  sets the double click/press delay to D seconds; defaults to 0.5\n"
	};

	struct Arguments {
		static sp::Tstr errorMessage;

		static bool help;

		static sp::Tuint8 verbosity;
		static sp::Tuint16 width;
		static sp::Tuint16 height;
		static float zoom;
		static float doubleClickDelay;

		static void parse(std::vector<std::string> arguments);
	};
}

#endif