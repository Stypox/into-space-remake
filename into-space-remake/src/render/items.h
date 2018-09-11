#ifndef _INTO_SPACE_REMAKE_RENDER_ITEMS_H_
#define _INTO_SPACE_REMAKE_RENDER_ITEMS_H_

#include <vector>
#include <gl-abstractions/shader.h>
#include <gl-abstractions/texture.h>
#include <gl-abstractions/vao.h>
#include <gl-abstractions/vbo.h>
#include <gl-abstractions/ebo.h>

#include "shared.h"
#include "renderer.h"
#include "../game/entity/item.h"
#include "../app/arguments.h"

namespace render {
	class Items {
		sp::gl::Shader m_shader;
		sp::gl::Texture2D m_texture;
		sp::gl::Vao m_vao;
		sp::gl::Vbo m_verticesVbo;
		sp::gl::Ebo m_verticesEbo;
		sp::gl::Vbo m_dataVbo;
	public:
		Items();

		void draw(const std::vector<game::entity::Item>& items);
	};
}

#endif