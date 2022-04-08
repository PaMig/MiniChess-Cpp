#pragma once
#include <list>

class Player
{
	
protected:
	float m_pos[2];
	float m_color[3];
	bool m_highlighted = false;
	bool m_active = false;
	float color;
public:
	void draw();
	void update();	
	void black();
	void white();
	void blackQueen();
	Player();
	//setters getters
	virtual float getPosX() { return m_pos[0]; }
	virtual float getPosY() { return m_pos[1]; }
	virtual void setPosX(float x) { m_pos[0] = x; }
	virtual void setPosY(float y) { m_pos[1] = y; }
	//highlight
	virtual void setHighlight(bool h) { m_highlighted = h; }
	virtual void setActive(bool a) { m_active = a; }
	//movement
	virtual bool containts(float x, float y);
	bool intersect(Player * tgt);
};