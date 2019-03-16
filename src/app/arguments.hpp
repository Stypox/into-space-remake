#ifndef _INTO_SPACE_REMAKE_APP_ARGUMENTS_HPP_
#define _INTO_SPACE_REMAKE_APP_ARGUMENTS_HPP_

#include <string>
#include <filesystem>

#include "debug.hpp"

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
			rectanglesFragmentShader,
			textureFolder;

		static void parse(int argc, char const* argv[]);
		static std::string helpScreen();
	};
}

#endif