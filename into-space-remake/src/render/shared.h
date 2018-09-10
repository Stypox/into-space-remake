#ifndef _INTO_SPACE_REMAKE_RENDER_SHARED_H_
#define _INTO_SPACE_REMAKE_RENDER_SHARED_H_

#include <cstddef>
#include <filesystem>
#include <basicTypes.h>
#include <GLFW/glfw3.h>

namespace render {
	constexpr size_t vertexSize = 4; // x, y, u, v
	const sp::Tpath shaderDir = "./into-space-remake/src/render/shader/";

	constexpr GLint itemsTexturePos = 0;
}

#endif