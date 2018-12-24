#include "items.h"

#include <vector>

#include "shared.h"
#include "renderer.h"
#include "../app/arguments.h"

namespace rend {
	using namespace stypox::gl;

	std::unique_ptr<Shader> Items::m_shader = nullptr;
	std::unique_ptr<Texture2D> Items::m_texture = nullptr;
	std::unique_ptr<Vao> Items::m_vao = nullptr;
	std::unique_ptr<Vbo> Items::m_verticesVbo = nullptr;
	std::unique_ptr<Ebo> Items::m_verticesEbo = nullptr;
	std::unique_ptr<Vbo> Items::m_dataVbo = nullptr;
	stypox::StockContainer<game::ent::Item::RenderData> Items::renderData{};

	void Items::init() {
		// acquire resources
		m_shader.reset(new Shader{rend::shaderDir / "items.vert", rend::shaderDir / "items.frag"});
		m_texture.reset(new Texture2D{itemsTexturePos, "items.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST});
		m_vao.reset(new Vao{});
		m_verticesVbo.reset(new Vbo{});
		m_verticesEbo.reset(new Ebo{});
		m_dataVbo.reset(new Vbo{});

		// error logging
		if (app::Gravity::info >= app::Arguments::verbosity) {
			if (m_shader->errors())
				app::debug(app::Gravity::error, "Items", m_shader->debugInfo("rend::Items::m_shader"));
			else
				app::debug(app::Gravity::info, "Items", m_shader->debugInfo("rend::Items::m_shader"));
			if (m_texture->fileOk())
				app::debug(app::Gravity::info, "Items", m_texture->debugInfo("rend::Items::m_texture"));
			else
				app::debug(app::Gravity::error, "Items", m_texture->debugInfo("rend::Items::m_texture"));
		}

		constexpr std::array<GLfloat, 16> vertices{
			-0.1f, +0.1f, 0.0f, 0.0f, // Top-left
			+0.1f, +0.1f, 1.0f, 0.0f, // Top-right
			+0.1f, -0.1f, 1.0f, 1.0f, // Bottom-right
			-0.1f, -0.1f, 0.0f, 1.0f, // Bottom-left
		};
		constexpr std::array<GLuint, 6> indices{
			0, 1, 2,
			2, 3, 0,
		};

		m_vao->generate();
		m_vao->bind();

		m_verticesVbo->generate();
		m_verticesVbo->data(vertices.data(), vertices.size(), GL_STATIC_DRAW);
		m_verticesEbo->generate();
		m_verticesEbo->data(indices.data(), indices.size(), GL_STATIC_DRAW);
		m_dataVbo->generate();

		m_verticesVbo->bind();
		GLint positionIndex =        m_shader->getAttribLocation("position");
		m_vao->enableAttrib(positionIndex);
		m_vao->attribPointer(positionIndex,        2, GL_FLOAT, 4, 0);
		m_vao->attribDivisor(positionIndex,        0);
		GLint texturePositionIndex = m_shader->getAttribLocation("texturePosition");
		m_vao->enableAttrib(texturePositionIndex);
		m_vao->attribPointer(texturePositionIndex, 2, GL_FLOAT, 4, 2);
		m_vao->attribDivisor(texturePositionIndex, 0);

		m_dataVbo->bind();
		GLint offsetIndex =       m_shader->getAttribLocation("offset");
		m_vao->enableAttrib(offsetIndex);
		m_vao->attribPointer(offsetIndex,          2, GL_FLOAT, m_itemSize, 0);
		m_vao->attribDivisor(offsetIndex,          1);
		GLint textureIndexIndex = m_shader->getAttribLocation("textureIndex");
		m_vao->enableAttrib(textureIndexIndex);
		m_vao->attribPointer(textureIndexIndex,	   1, GL_FLOAT, m_itemSize, 2);
		m_vao->attribDivisor(textureIndexIndex,	   1);
	}

	void Items::draw() {
		m_dataVbo->data(renderData.data(), renderData.size(), GL_STREAM_DRAW);

		m_vao->bind();
		m_shader->bind();
		m_shader->uniform("projection", Renderer::projectionMatrix());
		m_shader->uniform("view", Renderer::viewMatrix());
		m_shader->uniform("itemsTexture", m_texture->position());
		m_shader->uniform("nrPackedTextures", static_cast<GLint>(game::ent::Item::max) + 1);

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, renderData.size());
	}
}