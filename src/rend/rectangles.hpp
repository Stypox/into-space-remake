#ifndef _INTO_SPACE_REMAKE_RENDER_RECTANGLES_HPP_
#define _INTO_SPACE_REMAKE_RENDER_RECTANGLES_HPP_

#include <memory>
#include <stypox/gl/shader.hpp>
#include <stypox/gl/texture.hpp>
#include <stypox/gl/vao.hpp>
#include <stypox/gl/vbo.hpp>
#include <stypox/gl/ebo.hpp>
#include <stypox/stock_container.hpp>
#include <glm/mat4x4.hpp>

namespace rend {
	struct RectangleRenderData {
		GLfloat x, y, w, h,
			rotation, textureOffset, textureWidth;
	};
	static_assert(sizeof(RectangleRenderData) == 7*sizeof(GLfloat), "RectangleRenderData has padding bytes");

	class RectangleRender {
	protected:
		stypox::StockContainer<RectangleRenderData>::handler m_renderData;
	public:
		RectangleRender(const RectangleRenderData& renderData);
	};

	class Rectangles {
		static std::unique_ptr<stypox::gl::Shader> m_shader;
		static std::unique_ptr<stypox::gl::Texture2D> m_texture;
		static std::unique_ptr<stypox::gl::Vao> m_vao;
		static std::unique_ptr<stypox::gl::Vbo> m_verticesVbo;
		static std::unique_ptr<stypox::gl::Ebo> m_verticesEbo;
		static std::unique_ptr<stypox::gl::Vbo> m_dataVbo;
	public:
		static stypox::StockContainer<RectangleRenderData> renderData;

		static void init();
		static void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
	};
}

#endif