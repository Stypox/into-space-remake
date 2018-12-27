#ifndef _INTO_SPACE_REMAKE_RENDER_ITEMS_H_
#define _INTO_SPACE_REMAKE_RENDER_ITEMS_H_

#include <memory>
#include <stypox/gl/shader.h>
#include <stypox/gl/texture.h>
#include <stypox/gl/vao.h>
#include <stypox/gl/vbo.h>
#include <stypox/gl/ebo.h>
#include <stypox/stock_container.h>
#include <glm/mat4x4.hpp>

namespace rend {
	struct ItemRenderData {
		GLfloat x, y, textureIndex;
	};
	static_assert(sizeof(ItemRenderData) == 3*sizeof(GLfloat), "ItemRenderData has padding bytes");

	class ItemRender {
	protected:
		stypox::StockContainer<ItemRenderData>::handler m_renderData;
	public:
		ItemRender(const ItemRenderData& renderData);
	};

	class Items {
		static std::unique_ptr<stypox::gl::Shader> m_shader;
		static std::unique_ptr<stypox::gl::Texture2D> m_texture;
		static std::unique_ptr<stypox::gl::Vao> m_vao;
		static std::unique_ptr<stypox::gl::Vbo> m_verticesVbo;
		static std::unique_ptr<stypox::gl::Ebo> m_verticesEbo;
		static std::unique_ptr<stypox::gl::Vbo> m_dataVbo;
	public:
		static stypox::StockContainer<ItemRenderData> renderData;

		static void init();
		static void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
	};
}

#endif