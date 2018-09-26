#ifndef _INTO_SPACE_REMAKE_RENDER_MOVABLES_H_
#define _INTO_SPACE_REMAKE_RENDER_MOVABLES_H_

#include <vector>
#include <memory>
#include <gl-abstractions/shader.h>
#include <gl-abstractions/texture.h>
#include <gl-abstractions/vao.h>
#include <gl-abstractions/vbo.h>
#include <gl-abstractions/ebo.h>

#include "../game/ent/mov/movable.h"

namespace rend {
	class Movables {
		static constexpr size_t m_movableSize = 7;

		sp::gl::Shader m_shader;
		sp::gl::Texture2D m_texture;
		sp::gl::Vao m_vao;
		sp::gl::Vbo m_verticesVbo;
		sp::gl::Ebo m_verticesEbo;
		sp::gl::Vbo m_dataVbo;

		std::vector<GLfloat> m_data;
	public:
		Movables();
		
		void reserve(size_t nrMovables);
		template <typename T, typename = typename std::enable_if<std::is_same<game::ent::mov::Movable, T>::value || std::is_base_of<game::ent::mov::Movable, T>::value>::type>
		void addMovable(const std::unique_ptr<T>& mov);
		template <typename T, typename = typename std::enable_if<std::is_same<game::ent::mov::Movable, T>::value || std::is_base_of<game::ent::mov::Movable, T>::value>::type>
		void addMovables(const std::vector<std::unique_ptr<T>>& movables);

		void draw();
	};

	template <typename T, typename>
	inline void Movables::addMovable(const std::unique_ptr<T>& mov) {
		m_data.push_back(mov->x());
		m_data.push_back(mov->y());
		m_data.push_back(mov->w());
		m_data.push_back(mov->h());
		m_data.push_back(mov->rotation());
		m_data.push_back(mov->textureOffset());
		m_data.push_back(mov->textureWidth());
	}
	template <typename T, typename>
	inline void Movables::addMovables(const std::vector<std::unique_ptr<T>>& movables) {
		for (auto&& mov : movables)
			addMovable(mov);
	}
}

#endif