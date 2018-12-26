#ifndef _INTO_SPACE_REMAKE_RENDER_RECTANGLES_H_
#define _INTO_SPACE_REMAKE_RENDER_RECTANGLES_H_

#include <vector>
#include <memory>
#include <stypox/gl/shader.h>
#include <stypox/gl/texture.h>
#include <stypox/gl/vao.h>
#include <stypox/gl/vbo.h>
#include <stypox/gl/ebo.h>
#include <stypox/stock_container.h>

namespace rend {
	struct RectangleRenderData {
		GLfloat x, y, w, h,
			rotation, textureOffset, textureWidth;
	};

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
		static void draw();
	};
}

#endif