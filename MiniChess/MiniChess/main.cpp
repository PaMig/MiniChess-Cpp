#include "sgg/graphics.h"
#include "define.h"
#include <string>
#include "game.h"

void draw()
{
	Game* mygame = Game::getInstance();
	mygame->draw();
}

void update(float ms)
{
	Game* mygame = Game::getInstance();
	mygame->update();
}

int main(int argc, char** argv)
{
	//Window
	graphics::createWindow(1000, 700, "MiniChess");
	//Initialisation
	Game* game = Game::getInstance();
	
	//Canvas Properties
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	//Functions
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::startMessageLoop();
	//Release after end
	Game::releaseInstance();

	return 0;
}