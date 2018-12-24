#ifndef _INTO_SPACE_REMAKE_RENDER_SHARED_H_
#define _INTO_SPACE_REMAKE_RENDER_SHARED_H_

#include <cstddef>
#include <filesystem>
#include <GLFW/glfw3.h>

namespace rend {
	const std::filesystem::path shaderDir = "./into-space-remake/src/rend/shader/";

	constexpr GLint itemsTexturePos = 0;
	constexpr GLint movablesTexturePos = 1;
}

#endif