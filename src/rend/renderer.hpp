#ifndef _INTO_SPACE_REMAKE_RENDER_RENDERER_HPP_
#define _INTO_SPACE_REMAKE_RENDER_RENDERER_HPP_

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace rend {
	class Renderer {
	public:
		static constexpr GLfloat optimalScreenRatio = 16.0f/9.0f;
	private:
		static glm::mat4 m_projectionMatrix, m_viewMatrix;
	public:
		static void updateScreenSize(int width, int height);
		static void moveCameraToRocket(float x, float y);

		static void init();
		static void render();
	};
}

#endif