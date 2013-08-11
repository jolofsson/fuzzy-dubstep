#pragma once
#include <iostream>
#include "allegro.h"
#include "Character.h"

using namespace std;

/// <summary>
/// Enum som g&ouml;r det l&auml;ttare att se i vilket skede spelet befinner sig i
/// </summary>
enum GameScreen { gMenu = 0, gInfo = 1, gInGame = 2, gNextLevel = 3, gGameOver = 4, gExit = 5 };

/// <summary>
/// Klass som hanterar all textutmatning n&auml;r du &auml;r i spelet, ger ocks&aring; information om vilken niv&aring; du &auml;r p&aring; och den h&ouml;gsta po&auml;ngen.
/// </summary>
class Game
{
private:
	int highscore;
	int level;
	GameScreen state;

public:
	/// <summary> Default constructor. </summary>
	Game(void);
	~Game(void);
	/// <summary> Liknande get-metod f&ouml;r enum. </summary>
	/// <returns> Vilket l&auml;ge man befinner sig p&aring; i spelet </returns>
	GameScreen State() { return state; }

	/// <summary> Liknande set-metod f&ouml;r enum. </summary>
	void State(GameScreen change) { state = change; }

	/// <summary> Get-metod f&ouml;r variabeln highscore </summary>
	/// <returns> Returnerar h&ouml;gsta poängen </returns>
	int getHighScore() { return highscore; }

	/// <summary> Update highscore. </summary>
	/// <param name="points"> Gives the variable 'highscore' a new value. </param>
	void setHighScore(int points);

	void gameTextOutput(BITMAP *buffer, Character c1, int time);

	/// <summary> Uppdaterar niv&aring;n i spelet </summary>
	void changeLevel() { level += 1; }

	/// <summary> Återst&auml;ller niv&aring;n till 1. </summary>
	void resetLevel() { level = 1; }

	/// <summary> Get-metod f&ouml;r variabeln level. </summary>
	/// <returns> Returnerar den aktuella niv&aring;n i spelet </returns>
	int getLevel() { return level; }
};
