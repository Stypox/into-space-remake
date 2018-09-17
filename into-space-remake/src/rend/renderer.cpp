#include "renderer.h"

namespace rend {
	int Renderer::m_width{};
	int Renderer::m_height{};

	void Renderer::updateScreenSize(int width, int height) {
		m_width = width;
		m_height = height;
	}
	GLfloat Renderer::screenRatio() {
		return static_cast<GLfloat>(m_width) / static_cast<GLfloat>(m_height);
	}

	glm::mat4 Renderer::projectionMatrix() {
		/*
		The returned matrix ensures the width/height of drawn things isn't changed
		The optimal screen ratio is 16/9 an there the field of view is the biggest,
		otherwise only a part of the 16/9 scene is rendered.
		If screen ratio > optimal then the bottom part of the y axis is rendered,
		otherwise the central part on the x axis.
		*/
		GLfloat ratio = screenRatio();
		if (ratio > optimalScreenRatio) {
			return glm::mat4{
				1.0f / optimalScreenRatio, 0.0f, 0.0f, 0.0f,
				0.0f, ratio / optimalScreenRatio, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, ratio / optimalScreenRatio - 1.0f, 0.0f, 1.0f,
			};
		}
		else {
			return glm::mat4{
				1.0f / ratio, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
		}
	}
	glm::mat4 Renderer::viewMatrix() {
		//TODO
		return glm::mat4{1.0f};
	}
}