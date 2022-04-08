#include "player.h"
#include "sgg/graphics.h"
#include "define.h"


void Player::draw()
{
	graphics::Brush br;
	graphics::Brush br2;

	float h = 1.0f * m_highlighted;
	SETCOLOR(br2.fill_color, 1.0f, h, h);
	br2.outline_opacity = 0.0f;
	br2.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Q_W.png");
	br2.texture = ASSET_PATH + std::string("Q_W.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE + 1.0f, PLAYER_SIZE, br2);
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE+ 0.5f, PLAYER_SIZE, br);
	graphics::resetPose();
}

void Player::update()
{
}

void Player::black()
{
	
	graphics::Brush br;
	graphics::Brush br2;
	float h = 1.0f * m_highlighted;
	SETCOLOR(br2.fill_color, h, 0.0f, 1.0f);
	br.outline_opacity = 0.0f;
	br2.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("K_B.png");
	br2.texture = ASSET_PATH + std::string("K_B.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE + 0.5f, PLAYER_SIZE, br2);
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
	graphics::resetPose();
}

void Player::white()
{
	graphics::Brush br;
	graphics::Brush br2;

	float h = 1.0f * m_highlighted;
	SETCOLOR(br2.fill_color, h, 0.0f, 1.0f);
	br2.outline_opacity =0.0f;
	br.outline_opacity = 0.0f;

	br.texture = ASSET_PATH + std::string("K_W.png");
	br2.texture = ASSET_PATH + std::string("K_W.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE + 0.5f, PLAYER_SIZE, br2);
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
	graphics::resetPose();
}

void Player::blackQueen()
{
	graphics::Brush king2;
	graphics::Brush king;
	graphics::Brush br2;
	float h = 1.0f * m_highlighted;
	SETCOLOR(br2.fill_color, 1.0f, h, h);
	SETCOLOR(king2.fill_color, 0.0f,0.0f, 0.0f);
	br2.outline_opacity = 0.0f;
	king2.outline_opacity = 0.0f;
	br2.texture = ASSET_PATH + std::string("Q_W.png");
	king2.texture = ASSET_PATH + std::string("Q_W.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE + 1.0f, PLAYER_SIZE + 0.5f, br2);
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE + 0.5f, PLAYER_SIZE + 0.5f, king2);
	graphics::resetPose();
}

Player::Player()

{
	SETCOLOR(m_color, 1.0f, 1.0f, 1.0f);
}
bool Player::containts(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < PLAYER_SIZE * 0.3f;
}

bool Player::intersect(Player* tgt)
{
	return distance(m_pos[0], m_pos[1], tgt->m_pos[0], tgt->m_pos[1]) < PLAYER_SIZE * 0.6;
}

