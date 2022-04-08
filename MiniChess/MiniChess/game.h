#pragma once
#include "player.h"
#include "event.h"
#include <list>
class Game
{
public:
	enum game_state_t{STATE_INIT,STATE_RULES,STATE_LOADING,STATE_IDLE,STATE_MOVING,STATE_ATTACKING,STATE_DELETE,STATE_ENDW,STATE_ENDB};
protected:
	static Game* m_instance;
	std::list<Player*> m_white, m_black,total_players;
	std::list<Event*> m_events;
	Player* QueenW = new Player();
	Player* QueenB = new Player();
	Player* m_active_player = nullptr;
	Player* m_target_player = nullptr;
	float m_init_pos_x;
	float m_init_pos_y;
	bool m_valid_action = false;

	int turn = 0;
	game_state_t m_state = STATE_INIT;
	Game() {}
public:
	void draw();
	void update();
	void init();
	void spawn(int x);
	void deletep(int x);

	~Game();
	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Game* getInstance();

	void processEvents();
	void addEvent(Event * evt);
};
