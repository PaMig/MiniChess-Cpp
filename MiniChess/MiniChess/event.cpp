#include "event.h"
#include"sgg/graphics.h"
#include "define.h"
void Event::update()
{
	if (!m_active)
	{
		return;

	}
	if (waiting())
	{
		m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
		return;
	}

	m_elapsed_time += graphics::getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration)
	{
		m_active = false;
	}
}

Event::Event(float x, float y, float dur, float del)
	:m_pos_x(x),m_pos_y(y),m_duration(dur),m_delay(del)
{
}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}

void FireEvent::draw()
{
	graphics::Brush br;

	float s = m_elapsed_time / m_duration;
	br.fill_opacity = 1.0f - s;
	br.texture = ASSET_PATH + std::string("fire.png");
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.3f * (1.0f - s);
	graphics::setScale(m_scale + s, m_scale + s);
	graphics::setOrientation(m_orientation + s*20.0f);

	graphics::drawRect(m_pos_x, m_pos_y, PLAYER_SIZE / 5, PLAYER_SIZE / 5, br);

	graphics::resetPose();
}

FireEvent::FireEvent(float x, float y)
	:Event(x, y, 1.0f, 0.0f)
{
	m_orientation = RAND0TO1() * 180.0f - 90.0f;
	m_scale = 0.8f + RAND0TO1() * 0.4f; //size
}

void EndGame::draw()
{
	graphics::Brush br;

	float s = m_elapsed_time / m_duration;
	br.fill_opacity = 1.0f - s;
	br.texture = ASSET_PATH + std::string("gold.png");
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.3f * (1.0f - s);
	graphics::drawRect(CANVAS_WIDTH /2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::resetPose();
}

EndGame::EndGame(float x, float y)
	:Event(CANVAS_WIDTH, CANVAS_HEIGHT, 5.0f, 1.0f)
{
}
