#ifndef _INTO_SPACE_REMAKE_RENDER_ITEMS_H_
#define _INTO_SPACE_REMAKE_RENDER_ITEMS_H_

#include <memory>
#include <stypox/gl/shader.h>
#include <stypox/gl/texture.h>
#include <stypox/gl/vao.h>
#include <stypox/gl/vbo.h>
#include <stypox/gl/ebo.h>
#include <stypox/stock_container.h>

#include "../game/ent/item.h"

namespace rend {
	class Items {
		static constexpr size_t m_itemSize = 3;

		static std::unique_ptr<stypox::gl::Shader> m_shader;
		static std::unique_ptr<stypox::gl::Texture2D> m_texture;
		static std::unique_ptr<stypox::gl::Vao> m_vao;
		static std::unique_ptr<stypox::gl::Vbo> m_verticesVbo;
		static std::unique_ptr<stypox::gl::Ebo> m_verticesEbo;
		static std::unique_ptr<stypox::gl::Vbo> m_dataVbo;
	public:
		static stypox::StockContainer<game::ent::Item::RenderData> renderData;

		static void init();
		static void draw();
	};
}

#endif