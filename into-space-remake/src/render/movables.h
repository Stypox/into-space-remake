#ifndef _INTO_SPACE_REMAKE_RENDER_MOVABLES_H_
#define _INTO_SPACE_REMAKE_RENDER_MOVABLES_H_

#include <vector>
#include <memory>
#include <gl-abstractions/shader.h>
#include <gl-abstractions/texture.h>
#include <gl-abstractions/vao.h>
#include <gl-abstractions/vbo.h>
#include <gl-abstractions/ebo.h>

#include "shared.h"
#include "renderer.h"
#include "../game/entity/movable/movable.h"
#include "../app/arguments.h"

namespace render {
	class Movables {
		sp::gl::Shader m_shader;
		sp::gl::Texture2D m_texture;
		sp::gl::Vao m_vao;
		sp::gl::Vbo m_verticesVbo;
		sp::gl::Ebo m_verticesEbo;
		sp::gl::Vbo m_dataVbo;
	public:
		Movables();

		void draw(const std::vector<std::unique_ptr<game::entity::movable::Movable>>& movables);
	};
}

#endif