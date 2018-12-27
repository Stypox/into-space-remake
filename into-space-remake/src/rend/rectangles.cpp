#include "rectangles.h"

#include "shared.h"
#include "renderer.h"
#include "../app/arguments.h"

namespace rend {
	using namespace stypox::gl;

	RectangleRender::RectangleRender(const RectangleRenderData& renderData) :
		m_renderData{Rectangles::renderData.emplace(renderData)} {}

	std::unique_ptr<Shader> Rectangles::m_shader = nullptr;
	std::unique_ptr<Texture2D> Rectangles::m_texture = nullptr;
	std::unique_ptr<Vao> Rectangles::m_vao = nullptr;
	std::unique_ptr<Vbo> Rectangles::m_verticesVbo = nullptr;
	std::unique_ptr<Ebo> Rectangles::m_verticesEbo = nullptr;
	std::unique_ptr<Vbo> Rectangles::m_dataVbo = nullptr;

	stypox::StockContainer<RectangleRenderData> Rectangles::renderData{};

	void Rectangles::init() {
		// acquire resources
		m_shader.reset(new Shader{rend::shaderDir / "rectangles.vert", rend::shaderDir / "rectangles.frag"});
		m_texture.reset(new Texture2D{rectanglesTexturePos, "rectangles.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST});
		m_vao.reset(new Vao{});
		m_verticesVbo.reset(new Vbo{});
		m_verticesEbo.reset(new Ebo{});
		m_dataVbo.reset(new Vbo{});
		
		// error logging
		if (app::Gravity::info >= app::Arguments::verbosity) {
			if (m_shader->errors())
				app::debug(app::Gravity::error, "Rectangles", m_shader->debugInfo("rend::Rectangles::m_shader"));
			else
				app::debug(app::Gravity::info, "Rectangles", m_shader->debugInfo("rend::Rectangles::m_shader"));
			if (m_texture->fileOk())
				app::debug(app::Gravity::info, "Rectangles", m_texture->debugInfo("rend::Rectangles::m_texture"));
			else
				app::debug(app::Gravity::error, "Rectangles", m_texture->debugInfo("rend::Rectangles::m_texture"));
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

		constexpr size_t nrOfFloats = sizeof(RectangleRenderData) / sizeof(GLfloat);
		m_dataVbo->bind();
		GLint offsetIndex =			 m_shader->getAttribLocation("offset");
		m_vao->enableAttrib(offsetIndex);
		m_vao->attribPointer(offsetIndex,          2, GL_FLOAT, nrOfFloats, 0);
		m_vao->attribDivisor(offsetIndex,          1);
		GLint sizeIndex =			 m_shader->getAttribLocation("size");
		m_vao->enableAttrib(sizeIndex);
		m_vao->attribPointer(sizeIndex,            2, GL_FLOAT, nrOfFloats, 2);
		m_vao->attribDivisor(sizeIndex,            1);
		GLint rotationIndex =		 m_shader->getAttribLocation("rotation");
		m_vao->enableAttrib(rotationIndex);
		m_vao->attribPointer(rotationIndex,        1, GL_FLOAT, nrOfFloats, 4);
		m_vao->attribDivisor(rotationIndex,        1);
		GLint textureOffsetIndex =	 m_shader->getAttribLocation("textureOffset");
		m_vao->enableAttrib(textureOffsetIndex);
		m_vao->attribPointer(textureOffsetIndex,   1, GL_FLOAT, nrOfFloats, 5);
		m_vao->attribDivisor(textureOffsetIndex,   1);
		GLint textureWidthIndex =	 m_shader->getAttribLocation("textureWidth");
		m_vao->enableAttrib(textureWidthIndex);
		m_vao->attribPointer(textureWidthIndex,    1, GL_FLOAT, nrOfFloats, 6);
		m_vao->attribDivisor(textureWidthIndex,    1);
	}

	void Rectangles::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
		m_dataVbo->data(renderData.data(), renderData.size(), GL_STREAM_DRAW);

		m_vao->bind();
		m_shader->bind();
		m_shader->uniform("projection", projectionMatrix);
		m_shader->uniform("view", viewMatrix);
		m_shader->uniform("rectanglesTexture", m_texture->position());

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, renderData.size());
	}
}