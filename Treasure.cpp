#include "Treasure.h"

/// <summary> Default constructor. </summary>
Treasure::Treasure(void)
{
	this->x_pos = (rand() %30 + 1)*32; //Slumpar fram var diamanten (skatten) hamnar på spelplan
	this->y_pos = (rand() %22 + 1)*32;
	this->total_treasure = 2; //Antal diamanter när spelet startar
	this->picked_up = false; //bool som kontrollerar om diamanten är upplockad (false = ej upplockad)
	this->picked_treasure = 0; //Variabel för att kontrollera hur många diamanter spelaren plockat upp
}
/// <summary> Slumpar fram ny position f&ouml;r diamanten. </summary>
void Treasure::randomiseNewPosition() {
	this->x_pos = (rand() %30 + 1)*32;
	this->y_pos = (rand() %22 + 1)*32;
	this->picked_up = false;
}

/// <summary> Skriver ut grafiken f&ouml;r diamanterna. </summary>
/// <param name="diamond"> F&ouml;r att f&aring; tillg&aring;ng till att rita ut bilden p&aring; sk&auml;rmen. </param>
void Treasure::draw(BITMAP *buffer,	BITMAP *diamond) { 
	if(this->picked_up == false) {
		draw_sprite(buffer, diamond, this->x_pos, this->y_pos);
	}
}

/// <summary> Funktion som kontrollerar om spelaren befinner sig p&aring; en diamant. </summary>
/// <param name="c1"> Anv&auml;nds f&ouml;r att kontrollera spelarens position mot diamantens. </param>
/// <returns> Sant om spelaren befinner sig p&aring; samma position som en diamanten annars falskt.</returns>
bool Treasure::pickedUp(Character c1) {
	if((c1.getX_pos()+25 > this->x_pos) && (c1.getX_pos()+10 < this->x_pos+32) 
		&& (c1.getY_pos()+53 > this->y_pos) && (c1.getY_pos()+10 < this->y_pos+32)) {
			Treasure::remove_treasure(); //Tar bort diamanten
			return true;
	}
	else
		return false;
}

/// <summary> Uppdaterar antalet diamanter i spelet (max 7). </summary>
void Treasure::updateTotal_treasure() {

	this->total_treasure = this->total_treasure + 1;

	if(this->total_treasure >= max_treasure) {
		this->total_treasure = max_treasure;
	}
}

/// <summary> Tar bort diamant fr&aring;n spelplan. </summary>
void Treasure::remove_treasure() {
	this->x_pos = -100;
	this->y_pos = -100;
	this->picked_up = true;
}

void Treasure::restart() {
	this->x_pos = (rand() %30 + 1)*32;
	this->y_pos = (rand() %22 + 1)*32;
	this->total_treasure = 2;
	this->picked_up = false;
}

Treasure::~Treasure(void)
{
}
