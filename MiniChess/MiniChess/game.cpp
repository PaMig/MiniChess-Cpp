#include "game.h"
#include "define.h"
#include "sgg/graphics.h"
#include <algorithm>
void Game::draw()//==================================================================================
{	//First state of the game 
	graphics::Brush b,b2,b3,b4;
	SETCOLOR(b2.fill_color, 1.0f, 0.0f, 0.0f);
	SETCOLOR(b3.fill_color, 0.4f, 0.0f, 1.0f);
	b.outline_opacity = 0.0f;
	b.texture = ASSET_PATH + std::string("wp.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, b);
	if (m_state == STATE_INIT) {
		graphics::setFont(ASSET_PATH + std::string("fontfont.ttf"));
		graphics::drawText(CANVAS_WIDTH / 35, CANVAS_HEIGHT / 6.5, 1.3f, "WELCOME TO CAPTURE THE QUEEN A MINICHESS ADAPTATION!", b);
		graphics::drawText(CANVAS_WIDTH / 7, CANVAS_HEIGHT / 2, 1.2f, "GET TO THE ENEMY QUEEN AND WIN THE GAME!!", b);
		graphics::drawText(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 1.5, 2.0f, "PRESS  ENTER  TO  BEGIN", b2);
		graphics::drawText(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 1.4, 1.0f, "PRESS  SPACE  FOR  GAMERULES", b3);
		graphics::drawText(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 1.3, 0.5f, "By: 3160268 - 3160073", b);
		
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			m_state = STATE_LOADING;
		}if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			m_state = STATE_RULES;
		}
		return;
	}
	//Showing the Rules of The game
	if (m_state == STATE_RULES) {
		b4.texture = ASSET_PATH + std::string("wp2.png");
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, b4);
		graphics::drawText(CANVAS_WIDTH / 35, CANVAS_HEIGHT / 6.5, 1.3f, "RULES OF THE GAME!", b);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 4.5, 1.2f, "THIS IS A 2 PLAYER 1V1 CHESS GAME", b);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 3.1, 2.0f, "WHITE BEGINS FIRST", b);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 2.5, 1.0f, "WHOEVER GETS ENEMY QUEEN FIRST WINS", b);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 2.0, 0.7f, "A QUEEN CAN ONLY KILL THE ENEMY QUEEN NOT KINGS!!", b);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 1.7, 0.7f, "THE QUEEN MOVES LIKE A KING BUT WITH DOUBLE THE RANGE!!", b2);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 1.6, 0.7f, "IF A PAWN IS CLICKED IT MUST BE MOVED OR THE TURN IS LOST", b2);
		graphics::drawText(CANVAS_WIDTH / 10, CANVAS_HEIGHT / 1.5, 0.6f, "--PRESS ENTER TO BEGIN!!--", b2);
		
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) 
			m_state = STATE_LOADING;
		return;
	}
	//draw background-----------------------------------------------------------------------------------

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("chess.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH  , CANVAS_HEIGHT, br);

	//Draw the Pawns
	for (Player* player : m_black) {
		if (player == QueenB) {
			player->blackQueen();
		}else
		player->black();
	}for (Player* player : m_white) {
		if (player == QueenW) {
			player->draw();
		}
		else
		player->white();
	}
	for (Event* e : m_events) {
		e->draw();
	}
}

void Game::update()//================================================================================
{

//check state and use it------------------------------------------------------------------------------
	if (m_state == STATE_INIT) { 
		graphics::playMusic(std::string(ASSET_PATH) + "intro.mp3", 0.7f, true, 60000);
		return;
	}
	if (m_state == STATE_LOADING) { 
		init();
		m_state = STATE_IDLE;
		return; 
	}
	if (m_state == STATE_DELETE) {
		graphics::playSound(std::string(ASSET_PATH) + "kill.mp3", 1.0f, false);
		m_state == STATE_MOVING;
	}
	if (m_state == STATE_ENDW) {
		graphics::Brush b2;
		SETCOLOR(b2.fill_color, 1.0f, 0.0f, 0.0f);
		graphics::drawText(CANVAS_WIDTH / 25, CANVAS_HEIGHT / 1.5, 3.0f, "PLAYER WHITE HAS WON!!!!", b2);
		graphics::playSound(std::string(ASSET_PATH) + "victory.mp3", 1.0f, false);
		return;
	}
	if (m_state == STATE_ENDB) {
		graphics::Brush b2;
		SETCOLOR(b2.fill_color, 1.0f, 0.0f, 0.0f);
		graphics::drawText(CANVAS_WIDTH / 25, CANVAS_HEIGHT / 1.5, 3.0f, "PLAYER BLACK HAS WON!!!!", b2);
		graphics::playSound(std::string(ASSET_PATH) + "victory.mp3", 1.0f, false);
		return;
	}
//For Events
	processEvents();
//dhlwsh gia to highlight----------------------------------------------------------------------------

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	Player* cur_player = nullptr;

	for (Player* player : total_players)     
	{
		bool white = (std::find(m_white.begin(), m_white.end(), player) != m_white.end());
		if (player->containts(mx, my)) {
			player->setHighlight(true);
			if (turn % 2 == 0) {	//first is for white then one each
				if (white) {
					cur_player = player;
				}
			}
			else {
				if (!white) { cur_player = player; }
			}
		}
		else {
			player->setHighlight(false);
		}
		//activate player------------------------------------------------------------------------------------
		if (ms.button_left_pressed && cur_player)
		{
			m_active_player = cur_player;
			m_active_player->setActive(true);
			for (auto player : total_players) {
				if (player != m_active_player) {
					player->setActive(false);
				}
			}
			m_init_pos_x = m_active_player->getPosX();
			m_init_pos_y = m_active_player->getPosY();

		}
		//mouse drag to move player -------------------------------------------------------------------------
		if (ms.dragging && m_active_player)
		{
			m_state = STATE_MOVING;
			float x = PLAYER_MOTION_RANGE;
			if (m_active_player == QueenB || m_active_player == QueenW) {
				x = PLAYER_QUEEN_RANGE;
			}
			if (distance(m_init_pos_x, m_init_pos_y, mx, my) < x)
			{
				//Put player in Square center(Diakrites theseis) &Player attacking------------------------------------
				bool white = (std::find(m_white.begin(), m_white.end(), m_active_player) != m_white.end());
				mx = PLAYER_SIZE * (0.5f + (int)(mx	 / PLAYER_SIZE));
				my = PLAYER_SIZE * (0.5f + (int)(my / PLAYER_SIZE));
				m_active_player->setPosX(mx);
				m_active_player->setPosY(my);
				//If a pawn is selected and not moved the turn is lost!!
				if (white) {
					turn = 1;
				}
				else{
					turn = 0;
				}
				
			}
			m_valid_action = true;
			m_target_player = nullptr; //Intersect & Attack Mode
			for (Player* p : total_players) {

				if (p == m_active_player)
					continue;
				if (p->intersect(m_active_player))
				{
					m_state = STATE_ATTACKING;
					if (RAND0TO1() < 0.5f)
						addEvent(new FireEvent(mx, my));
					m_target_player = p;
				}
			}
//	Valid moves on attack mode 
			if (m_state == STATE_ATTACKING)  
			{
				bool white = (std::find(m_white.begin(), m_white.end(), m_active_player) != m_white.end());
				bool white2 = (std::find(m_white.begin(), m_white.end(), m_target_player) != m_white.end());
				if (m_target_player != nullptr && white != white2)
				{
					m_valid_action = true;
					if ((m_active_player == QueenB && m_target_player != QueenW) || (m_active_player == QueenW && m_target_player != QueenB)) {
						m_valid_action = false;
					}
					
				}
				else
					m_valid_action = false;
			}
		}
		// Call Delete & oi pointers ksana:nullptr----------------------------------------
		if (ms.button_left_released && m_active_player)
		{
			deletep(1);//Delete the Pawn
			m_target_player = nullptr;
			m_active_player->setActive(false);
			m_active_player = nullptr;
		}
	}

	for (auto p : total_players)
	{
		p->setHighlight(p->containts(mx, my));
	}
}

void Game::init()//==================================================================================
{

	graphics::setFont(ASSET_PATH + std::string("fontfont.ttf"));

	graphics::playMusic(std::string(ASSET_PATH) + "Vikings.mp3", 0.8f, true, 60000);
	//Spawn Pawns
	spawn(1);//1 is black
	spawn(0);//0 is white 
	//Add Queens
	total_players.push_front(QueenW);
	total_players.push_front(QueenB);
	m_white.push_front(QueenW);
	m_black.push_front(QueenB);
	QueenW->setPosX(CANVAS_WIDTH - 2.0f);
	QueenW->setPosY(CANVAS_HEIGHT / 1.6f);
	QueenB->setPosX(2.0f);
	QueenB->setPosY(CANVAS_HEIGHT / 2.7f);
}

void Game::spawn(int x)
{
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 4; j++) {
			if (x == 1)
			{
				Player* p = new Player();
				m_black.push_front(p); //To have Blacks
				p->setPosX(CANVAS_WIDTH * (i + 0.421f) / 2.0f);
				p->setPosY(CANVAS_HEIGHT * (j + 0.5f) / 4.0f);
				total_players.push_front(p); 
			}
			if(x == 0)
			{
				Player* w = new Player();
				m_white.push_front(w); //To have Whites
				w->setPosX(CANVAS_WIDTH * (i + 0.521f) * 1.5f); 
				w->setPosY(CANVAS_HEIGHT * (j + 0.5f) / 4.0f);
				total_players.push_front(w);
			}
		}
	}
}

void Game::deletep(int x)
{
	if (!m_valid_action && m_target_player)				
	{
		m_active_player->setPosX(m_init_pos_x);
		m_active_player->setPosY(m_init_pos_y);
	}
	m_state = STATE_IDLE;
	if (m_valid_action && m_target_player)	//Delete Begins
	{
		Player* tgt = m_target_player;
		bool white = (std::find(m_white.begin(), m_white.end(), tgt) != m_white.end());
		x = white;
		printf("\nChecking");
		printf("\nfront %p:", total_players.front());
		printf("\nBlack Queen: %p",QueenB);
		if (tgt == QueenB) {
			total_players.pop_front();
		}
		m_state = STATE_DELETE;
		total_players.remove_if([tgt](Player* pl) { return pl == tgt; }); // to total players trwei to exeption
		if (x == 1) {
			m_white.remove_if([tgt](Player* pl) { return pl == tgt; });
		}else
		m_black.remove_if([tgt](Player* pl) { return pl == tgt; });
		if (tgt == QueenB){
			m_state = STATE_ENDW;
				addEvent(new EndGame(CANVAS_WIDTH, CANVAS_HEIGHT));
		}
		if (tgt == QueenW) {
			m_state = STATE_ENDB;
				addEvent(new EndGame(CANVAS_WIDTH, CANVAS_HEIGHT));
		}
	}
}


Game::~Game()
{
	for (auto p : total_players) { delete p; };
		total_players.clear();
		m_white.clear();
		m_black.clear();
}

Game* Game::getInstance()
{
	if (!m_instance) 
		m_instance = new Game();
		return m_instance;
	
}

void Game::processEvents()
{
	for (Event* e : m_events)
	{
		e->update();
	}

	m_events.remove_if([](Event* ev) { return !ev->active(); });

}

void Game::addEvent(Event* evt)
{
	m_events.push_front(evt);
}

Game* Game::m_instance = nullptr;