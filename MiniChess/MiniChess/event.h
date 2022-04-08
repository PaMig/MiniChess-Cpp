#pragma once

class Event
{
protected:

	float m_pos_x, m_pos_y;

	float m_duration = 1.0f;
	float m_delay = 0.0f;
	float m_elapsed_time = 0.0f;
	float m_elapsed_delay = 0.0f;
	bool m_active = true;

public: 
	virtual void draw() {};
	virtual void update();
	Event(float x = 0.0f, float y = 0.0f, float dur = 1.0f, float del = 0.0f); 
	virtual ~Event() {};
	bool active() { return m_active; }
	void disable() { m_active = false; }
	bool waiting();

};

class FireEvent : public Event
{
	float m_orientation;
	float m_scale;
public:
	void draw() override;
	FireEvent(float x, float y);
};

class EndGame : public Event
{
public:
	void draw() override;
	EndGame(float x, float y);
};