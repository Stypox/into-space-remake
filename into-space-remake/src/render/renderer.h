#ifndef _INTO_SPACE_REMAKE_RENDER_RENDERER_H_
#define _INTO_SPACE_REMAKE_RENDER_RENDERER_H_

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

namespace render {
	class Renderer {
	public:
		static constexpr GLfloat optimalScreenRatio = 16.0/9.0;
	private:
		static int m_width, m_height;
	public:
		static void updateScreenSize(int width, int height);
		static GLfloat screenRatio();

		static glm::mat4 projectionMatrix();
		static glm::mat4 viewMatrix();
	};
}

#endif