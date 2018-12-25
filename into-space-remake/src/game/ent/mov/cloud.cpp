#include "cloud.h"

#include "../../../misc/random.h"

namespace game::ent::mov {
	Cloud::Cloud(GLfloat x, GLfloat y) :
		Movable{RenderData{x, y, 0.0f, 0.0f, 0.0f, 0.2f, 0.8f}} {
		GLfloat size = misc::Random::range(0.3f, 0.4f);
		m_renderData->h = size;
		m_renderData->w = size * widthHeightRatio;
		m_renderData->rotation = misc::Random::range(-0.3f, 0.3f);
	}
}