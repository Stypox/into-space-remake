#ifndef _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_
#define _INTO_SPACE_REMAKE_APP_ARGUMENTS_H_

#include <string>
#include <filesystem>

#include "debug.h"

namespace app {
	struct Arguments {
		static std::string errorMessage;

		static bool help;
		static bool wasd;
		static bool fullscreen;

		static Gravity verbosity;
		static uint16_t width, height;
		static uint16_t entitiesPerChunk;
		static uint8_t percItems, percClouds;

		static float zoom;
		static float doubleClickDelay;

		static std::filesystem::path itemsVertexShader,
			itemsFragmentShader,
			rectanglesVertexShader,
			rectanglesFragmentShader;

		static void parse(int argc, char const* argv[]);
		static std::string helpScreen();
	};
}

#endif