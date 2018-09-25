#ifndef _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_
#define _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_

#include <vector>
#include <string>
#include <map>
#include <basicTypes.h>

#include "debug.h"

namespace app {
	enum class BoolArg {
		help,
		wasd,
	};
	enum class ValueArg {
		verbosity,
		width,
		height,
		zoom,
		doubleClickDelay,
		entitiesPerChunk,
		percItems,
	};

	extern const std::map<BoolArg, std::vector<std::string>> boolArgs;
	extern const std::map<ValueArg, std::vector<std::string>> valueArgs;

	constexpr const char * helpScreen { "\n"
		"Into Space remake by Stypox: Help screen\n"
		"\n"
		"Boolean settings:\n"
		"   -h, --help         shows this screen\n"
		"       --wasd         use WASD instead of arrow keys"
		"\n"
		"Value settings: (I = integer, D = decimal)\n"
		"   -v=I --verbosity=I verbosity (0-3); default: 0\n"
		"   -w=I --width=I     window starting width; default: 480\n"
		"   -h=I --height=I    window starting height; default: 480\n"
		"   -z=D --zoom=D      game starting zoom (0.5-2.0); default: 1.0\n"
		"        --dc-delay=D  double click/press delay in seconds; default: 0.5\n"
		"   -e=I --entities=I  entities per chunk; default: 20\n"
		"        --%items=I    item generation probability (0-255); default: 50\n"
	};

	struct Arguments {
		static sp::Tstr errorMessage;

		static bool help;
		static bool wasd;

		static Gravity verbosity;
		static uint16_t width;
		static uint16_t height;
		static float zoom;
		static float doubleClickDelay;
		static uint16_t entitiesPerChunk;
		static uint8_t percItems;

		static void parse(std::vector<std::string> arguments);
	};
}

#endif