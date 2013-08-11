#pragma once
#include "allegro.h"
#include "Character.h"

/// <summary>
/// Har hand om objekten i spelet
/// </summary>
class Treasure
{
private:
	static const int max_treasure = 7; //Max antal diamanter som får finnas på spelplan
	int x_pos;
	int y_pos;
	int total_treasure; //Antalet aktuella diamanter
	int picked_treasure; //Antalet upplockade diamanter
	bool picked_up;

public:
	int getX_pos() { return x_pos; }
	int getY_pos() { return y_pos; }
	void randomiseNewPosition();
	void draw(BITMAP *buffer, BITMAP* diamond);
	bool pickedUp(Character c1);
	int getTotal_treasure() { return total_treasure; }
	void updateTotal_treasure();
	void setTotal_treasure(int amount) { total_treasure = amount; }
	bool getPickedUp() { return picked_up; }
	void remove_treasure();
	void restart();
	/// <summary> Uppdaterar antalet upplockade diamanter. </summary>
	void updatePicked_treasure() { picked_treasure += 1; }
	/// <summary> Nollst&auml;ller r&auml;knaren f&ouml;r upplockade diamanter. </summary>
	void resetPicked_treasure() { picked_treasure = 0; }
	int getPicked_treasure() { return picked_treasure; }
	Treasure(void);
	~Treasure(void);
};
