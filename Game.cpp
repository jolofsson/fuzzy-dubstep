#include "Game.h"

Game::Game(void)
{
	state = gMenu; //Startar i meny-läge
	highscore = 0;
	level = 1; //Nivå 1
}

//Uppdaterar högsta poängen
void Game::setHighScore(int points) {
	this->highscore = points;
}

/// <summary> All textutmatning till spelet. </summary>
/// <param name="buffer"> Bitmap buffer f&ouml;r implementering av double buffering. </param>
/// <param name="c1"> F&ouml;r att f&aring; tillg&aring;ng till spelaren po&auml;ng. </param>
/// <param name="time"> F&ouml;r m&ouml;jlighet att skriva ut timern i spelet. </param>
void Game::gameTextOutput(BITMAP *buffer, Character c1, int time) {

	textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "SCORE: %d", c1.getScore());
	textprintf_ex(buffer, font, 300, 10, makecol(0, 0, 0), -1, "LEVEL: %d", this->level);
	textprintf_ex(buffer, font, SCREEN_W-150, 10, makecol(0, 0, 0), -1, "HIGH SCORE: %d", this->highscore);
	//När man befinner sig i spelet
	if(this->state == gInGame) {
		textprintf_ex(buffer, font, SCREEN_W/2, 20, makecol(255, 255, 255), -1, "%d", time);
	}
	//När man klarat nivån
	if(this->state == gNextLevel) {
		textout_centre_ex(buffer, font, "LEVEL COMPLETE", SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1);
		textprintf_ex(buffer, font, (SCREEN_W/2)-90, (SCREEN_H/2)+20, makecol(0, 0, 0), -1, "Next Level starts in: %d", time);
	}

	//Om det blir game over skrivs detta ut på skärmen
	if(this->state == gGameOver) {
		textout_centre_ex(buffer, font, "GAME OVER", SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1);
		textout_centre_ex(buffer, font, "Press ESC", SCREEN_W/2, (SCREEN_H/2)+20, makecol(0, 0, 0), -1);
	}
}

Game::~Game(void)
{
}
