#include "renderer.hpp"

#include "items.hpp"
#include "rectangles.hpp"

namespace rend {
	glm::mat4 Renderer::m_projectionMatrix{1.0f};
	glm::mat4 Renderer::m_viewMatrix{1.0f};

	void Renderer::updateScreenSize(int width, int height) {
		/*
		The returned matrix ensures the width/height of drawn things isn't changed
		The optimal screen ratio is 16/9 an there the field of view is the biggest,
		otherwise only a part of the 16/9 scene is rendered.
		If screen ratio > optimal then the bottom part of the y axis is rendered,
		otherwise the central part on the x axis.
		*/
		GLfloat ratio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
		if (ratio > optimalScreenRatio) {
			m_projectionMatrix[0][0] = 1.0f / optimalScreenRatio;
			m_projectionMatrix[1][1] = ratio / optimalScreenRatio;
			m_projectionMatrix[3][1] = ratio / optimalScreenRatio - 1.0f; // the rocket should always be a little bit above the bottom margin
		}
		else {
			m_projectionMatrix[0][0] = 1.0f / ratio;
			m_projectionMatrix[1][1] = 1.0f;
			m_projectionMatrix[3][1] = 0.0f;
		}
	}
	void Renderer::moveCameraToRocket(float x, float y) {
		m_viewMatrix[3][0] = -x;
		m_viewMatrix[3][1] = -y - 0.5f; // the rocket should be a little bit above the bottom margin
	}

	void Renderer::init() {
		Items::init();
		Rectangles::init();
	}
	void Renderer::render() {
		Items::draw(m_projectionMatrix, m_viewMatrix);
		Rectangles::draw(m_projectionMatrix, m_viewMatrix);
	}
}