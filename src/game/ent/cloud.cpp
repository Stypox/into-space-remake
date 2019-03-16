#include "cloud.hpp"

#include "../../misc/random.hpp"

namespace game::ent {
	Cloud::Cloud(float x, float y) :
		RectangleRender{rend::RectangleRenderData{x, y, 0.0f, 0.0f, 0.0f, 0.2f, 0.8f}}, m_lastTimeRanInto{0.0f} {
		float size = misc::Random::range(0.3f, 0.4f);
		m_renderData->h = size;
		m_renderData->w = size * widthHeightRatio;
		m_renderData->rotation = misc::Random::range(-0.3f, 0.3f);
	}
}