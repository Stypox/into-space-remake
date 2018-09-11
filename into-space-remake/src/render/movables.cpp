#include "movables.h"

#include "shared.h"
#include "renderer.h"
#include "../app/arguments.h"

namespace render {
	Movables::Movables() :
	m_shader{render::shaderDir / "movables.vert", render::shaderDir / "movables.frag"}, m_texture{movablesTexturePos, "movables.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST},
	m_vao{}, m_verticesVbo{},
	m_verticesEbo{}, m_dataVbo{} {
		if (app::Arguments::verbosity > 1) {
			std::cout << m_shader.debugInfo("render::Movables::m_shader") << m_texture.debugInfo("render::Movables::m_texture");
		}

		constexpr std::array<GLfloat, 16> vertices{
			-1.0f, +1.0f, 0.0f, 0.0f, // Top-left
			+1.0f, +1.0f, 1.0f, 0.0f, // Top-right
			+1.0f, -1.0f, 1.0f, 1.0f, // Bottom-right
			-1.0f, -1.0f, 0.0f, 1.0f, // Bottom-left
		};
		constexpr std::array<GLuint, 6> indices{
			0, 1, 2,
			2, 3, 0,
		};

		m_vao.generate();
		m_vao.bind();

		m_vao.generate();
		m_vao.bind();

		m_verticesVbo.generate();
		m_verticesVbo.data(vertices, GL_STATIC_DRAW);
		m_verticesEbo.generate();
		m_verticesEbo.data(indices, GL_STATIC_DRAW);
		m_dataVbo.generate();

		m_verticesVbo.bind();
		GLint positionIndex =		 m_shader.getAttribLocation("position");
		m_vao.enableAttrib(positionIndex);
		m_vao.attribPointer(positionIndex,		  2, GL_FLOAT, 4, 0);
		m_vao.attribDivisor(positionIndex,		  0);
		GLint texturePositionIndex = m_shader.getAttribLocation("texturePosition");
		m_vao.enableAttrib(texturePositionIndex);
		m_vao.attribPointer(texturePositionIndex, 2, GL_FLOAT, 4, 2);
		m_vao.attribDivisor(texturePositionIndex, 0);

		m_dataVbo.bind();
		GLint offsetIndex =			 m_shader.getAttribLocation("offset");
		m_vao.enableAttrib(offsetIndex);
		m_vao.attribPointer(offsetIndex,		  2, GL_FLOAT, 6, 0);
		m_vao.attribDivisor(offsetIndex,		  1);
		GLint sizeIndex =			 m_shader.getAttribLocation("size");
		m_vao.enableAttrib(sizeIndex);
		m_vao.attribPointer(sizeIndex,			  2, GL_FLOAT, 6, 2);
		m_vao.attribDivisor(sizeIndex,			  1);
		GLint textureOffsetIndex =	 m_shader.getAttribLocation("textureOffset");
		m_vao.enableAttrib(textureOffsetIndex);
		m_vao.attribPointer(textureOffsetIndex,	  1, GL_FLOAT, 6, 4);
		m_vao.attribDivisor(textureOffsetIndex,	  1);
		GLint textureWidthIndex =	 m_shader.getAttribLocation("textureWidth");
		m_vao.enableAttrib(textureWidthIndex);
		m_vao.attribPointer(textureWidthIndex,	  1, GL_FLOAT, 6, 5);
		m_vao.attribDivisor(textureWidthIndex,	  1);
	}

	void Movables::draw(const std::vector<std::unique_ptr<game::entity::movable::Movable>>& movables) {
		std::vector<GLfloat> movablesData;
		movablesData.reserve(6 * movables.size());
		for (auto&& movable : movables) {
			movablesData.push_back(movable->x());
			movablesData.push_back(movable->y());
			movablesData.push_back(movable->sizeX());
			movablesData.push_back(movable->sizeY());
			movablesData.push_back(movable->textureOffset());
			movablesData.push_back(movable->textureWidth());
		}

		m_dataVbo.data(movablesData, GL_STREAM_DRAW);

		m_vao.bind();
		m_shader.bind();
		m_shader.uniform("projection", Renderer::projectionMatrix());
		m_shader.uniform("view", Renderer::viewMatrix());
		m_shader.uniform("movablesTexture", m_texture.position());

		if (GLenum e = glGetError(); e) std::cout << "Error " << e << " in game loop\n";

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, movables.size());
	}
}