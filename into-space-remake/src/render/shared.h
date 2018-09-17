#ifndef _INTO_SPACE_REMAKE_RENDER_SHARED_H_
#define _INTO_SPACE_REMAKE_RENDER_SHARED_H_

#include <cstddef>
#include <filesystem>
#include <basicTypes.h>
#include <GLFW/glfw3.h>

namespace render {
	const sp::Tpath shaderDir = "./into-space-remake/src/render/shader/";

	constexpr GLint itemsTexturePos = 0;
	constexpr GLint movablesTexturePos = 1;
}

#endif