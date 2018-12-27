#ifndef _INTO_SPACE_REMAKE_RENDER_RENDERER_H_
#define _INTO_SPACE_REMAKE_RENDER_RENDERER_H_

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#include "../game/ent/mov/rocket.h"

namespace rend {
	class Renderer {
	public:
		static constexpr GLfloat optimalScreenRatio = 16.0/9.0;
	private:
		static int m_width, m_height;
		static GLfloat m_x, m_y;
	public:
		static void updateScreenSize(int width, int height);
		static void moveCameraToRocket(float x, float y);

		static GLfloat screenRatio();

		static glm::mat4 projectionMatrix();
		static glm::mat4 viewMatrix();
	};
}

#endif