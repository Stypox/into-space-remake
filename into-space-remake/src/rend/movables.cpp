#include "movables.h"

#include "shared.h"
#include "renderer.h"
#include "../app/arguments.h"

namespace rend {
	using namespace stypox::gl;

	std::unique_ptr<Shader> Movables::m_shader = nullptr;
	std::unique_ptr<Texture2D> Movables::m_texture = nullptr;
	std::unique_ptr<Vao> Movables::m_vao = nullptr;
	std::unique_ptr<Vbo> Movables::m_verticesVbo = nullptr;
	std::unique_ptr<Ebo> Movables::m_verticesEbo = nullptr;
	std::unique_ptr<Vbo> Movables::m_dataVbo = nullptr;

	stypox::StockContainer<game::ent::mov::Movable::RenderData> Movables::renderData{};

	void Movables::init() {
		// acquire resources
		m_shader.reset(new Shader{rend::shaderDir / "movables.vert", rend::shaderDir / "movables.frag"});
		m_texture.reset(new Texture2D{movablesTexturePos, "movables.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST});
		m_vao.reset(new Vao{});
		m_verticesVbo.reset(new Vbo{});
		m_verticesEbo.reset(new Ebo{});
		m_dataVbo.reset(new Vbo{});
		
		// error logging
		if (app::Gravity::info >= app::Arguments::verbosity) {
			if (m_shader->errors())
				app::debug(app::Gravity::error, "Movables", m_shader->debugInfo("rend::Movables::m_shader"));
			else
				app::debug(app::Gravity::info, "Movables", m_shader->debugInfo("rend::Movables::m_shader"));
			if (m_texture->fileOk())
				app::debug(app::Gravity::info, "Movables", m_texture->debugInfo("rend::Movables::m_texture"));
			else
				app::debug(app::Gravity::error, "Movables", m_texture->debugInfo("rend::Movables::m_texture"));
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

		m_vao->generate();
		m_vao->bind();

		m_vao->generate();
		m_vao->bind();

		m_verticesVbo->generate();
		m_verticesVbo->data(vertices.data(), vertices.size(), GL_STATIC_DRAW);
		m_verticesEbo->generate();
		m_verticesEbo->data(indices.data(), indices.size(), GL_STATIC_DRAW);
		m_dataVbo->generate();

		m_verticesVbo->bind();
		GLint positionIndex =		 m_shader->getAttribLocation("position");
		m_vao->enableAttrib(positionIndex);
		m_vao->attribPointer(positionIndex,        2, GL_FLOAT, 4, 0);
		m_vao->attribDivisor(positionIndex,        0);
		GLint texturePositionIndex = m_shader->getAttribLocation("texturePosition");
		m_vao->enableAttrib(texturePositionIndex);
		m_vao->attribPointer(texturePositionIndex, 2, GL_FLOAT, 4, 2);
		m_vao->attribDivisor(texturePositionIndex, 0);

		m_dataVbo->bind();
		GLint offsetIndex =			 m_shader->getAttribLocation("offset");
		m_vao->enableAttrib(offsetIndex);
		m_vao->attribPointer(offsetIndex,          2, GL_FLOAT, m_movableSize, 0);
		m_vao->attribDivisor(offsetIndex,          1);
		GLint sizeIndex =			 m_shader->getAttribLocation("size");
		m_vao->enableAttrib(sizeIndex);
		m_vao->attribPointer(sizeIndex,            2, GL_FLOAT, m_movableSize, 2);
		m_vao->attribDivisor(sizeIndex,            1);
		GLint rotationIndex =		 m_shader->getAttribLocation("rotation");
		m_vao->enableAttrib(rotationIndex);
		m_vao->attribPointer(rotationIndex,        1, GL_FLOAT, m_movableSize, 4);
		m_vao->attribDivisor(rotationIndex,        1);
		GLint textureOffsetIndex =	 m_shader->getAttribLocation("textureOffset");
		m_vao->enableAttrib(textureOffsetIndex);
		m_vao->attribPointer(textureOffsetIndex,  1, GL_FLOAT, m_movableSize, 5);
		m_vao->attribDivisor(textureOffsetIndex,  1);
		GLint textureWidthIndex =	 m_shader->getAttribLocation("textureWidth");
		m_vao->enableAttrib(textureWidthIndex);
		m_vao->attribPointer(textureWidthIndex,   1, GL_FLOAT, m_movableSize, 6);
		m_vao->attribDivisor(textureWidthIndex,   1);
	}

	void Movables::draw() {
		std::vector<GLfloat> movablesData;
		movablesData.reserve(m_movableSize * renderData.size());
		for (auto&& movable : renderData) {
			movablesData.push_back(movable.x);
			movablesData.push_back(movable.y);
			movablesData.push_back(movable.w);
			movablesData.push_back(movable.h);
			movablesData.push_back(movable.rotation);
			movablesData.push_back(movable.textureOffset);
			movablesData.push_back(movable.textureWidth);
		}

		m_dataVbo->data(renderData.data(), renderData.size(), GL_STREAM_DRAW);

		m_vao->bind();
		m_shader->bind();
		m_shader->uniform("projection", Renderer::projectionMatrix());
		m_shader->uniform("view", Renderer::viewMatrix());
		m_shader->uniform("movablesTexture", m_texture->position());

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, renderData.size());
	}
}