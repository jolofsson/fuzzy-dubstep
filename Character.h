#pragma once
#include "allegro.h"

/// <summary>
/// Spelkaraktären
/// </summary>
class Character
{
private:
	int x_pos;
	int y_pos;
	int direction;
	int check_direction;
	int score;
	int speed;
	int lost_points;
	int frame;
	int frameCounter;

public:
	int getX_pos() { return x_pos; }
	int getY_pos() { return y_pos; }
	void move(int way);
	void draw(BITMAP *buffer, BITMAP *hero);
	void updateScore();
	int getScore() { return score; }
	void resetScore();
	void increaseSpeed();
	int getSpeed() { return speed; }
	void setSpeed(int _speed);
	void updateLostPoints();
	int getLostPoints() { return lost_points; }
	void movement();
	/// <summary> N&auml;r spelaren inte r&ouml;r sin karakt&auml;r. </summary>
	void standStill() { check_direction = 0; }
	Character(void);
	~Character(void);
};
