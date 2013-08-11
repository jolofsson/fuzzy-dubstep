#include "Character.h"

/// <summary> Default constructor. </summary>
Character::Character(void)
{
	this->x_pos = (rand() %30 + 1)*32; //Slumpar fram position var karakt�ren hamnar p� spleplanen
	this->y_pos = (rand() %22 + 1)*32;
	this->direction = 2; //Spelaren startar i riktning ned�t
	this->check_direction = 0; //Kontrollvariabel f�r spelaren riktning
	this->score = 0;
	this->speed = 1;
	this->lost_points = 0;
	this->frame = 1;
	this->frameCounter = 0;
}
/// <summary> Flyttar spelkarakt&auml;ren &ouml;ver spelplan </summary>
/// <param name="way"> Vilken riktning karakt&auml;ren skall f&ouml;rflyttas </param>
void Character::move(int way) {

	this->direction = way; //Variabel som kontrollerar �t vilket h�ll karakt�ren f�rflyttas
	this->check_direction = way; //Kontroll-variabel f�r att h�lla koll p� om karakt�ren r�r sig �t det h�llet eller st�r still

	if(way == 2) { //2 = f�rflyttas ned�t
		if(this->y_pos < 736) {
			this->y_pos += this->speed;
		}
	}
	else if(way == 8) { //8 = F�rflyttas upp�t
		if(this->y_pos > 10) {
			this->y_pos -= this->speed;
		}
	}
	else if(way == 4) { //4 = F�rflyttas v�nster
		if(this->x_pos > 0) {
			this->x_pos -= this->speed;
		}
	}
	else if(way == 6) { //6 = F�rflyttas h�ger
		if(this->x_pos < 992) {
			this->x_pos += this->speed;
		}
	}

}
/// <summary> Funktion som kontrollerar n&auml;r en ny "frame"/sprite skall &auml;ndras n&auml;r spelkarakt&auml;ren r&ouml;r sig &ouml;ver banan. </summary>
void Character::movement() {

	this->frameCounter = this->frameCounter + this->speed; //En r�knare som h�ller koll hur m�nga punkter spelkarakt�ren g�tt

	if(this->frameCounter > 64*this->frame) { //En sprit-bild �r kvadratisk 64 pixlar. N�r spelaren r�rt sig 64 punkter �ndras bilden

		this->frame = this->frame + 1; //Det finns 4 olika sprite-bilder p� karakt�ren i r�relse

		if(this->frame > 4) { //N�r man g�tt igenom hela fj�rde bildrutan �terst�lls den till den f�rsta igen (1)
			this->frame = 1;
			this->frameCounter = 0; //R�knaren nollst�lls likas�
		}
	}


}
/// <summary> Ritar ut spelkarakt&auml;ren p&aring; sk&auml;rmen. </summary>
/// <param name="hero"> F&ouml;r att kunna rita ut spelkarakt&auml;ren p&aring; sk&auml;rmen </param>
void Character::draw(BITMAP *buffer, BITMAP *hero) {
	if(this->check_direction == 0) { //Spelkarakt�ren st�r stilla
		if(this->direction == 2) { //Karakt�ren kollar ned�t
			masked_blit(hero, buffer, 0, 64,this->x_pos, this->y_pos,64, 64);
		}
		else if(this->direction == 8) { //Kollar upp�t
			masked_blit(hero, buffer, 0, 128,this->x_pos, this->y_pos,64, 64);
		}
		else if(this->direction == 4) { //Kollar v�nster
			masked_blit(hero, buffer, 0, 0, this->x_pos, this->y_pos, 64, 64);
		}
		else if(this->direction == 6) { //Kollar h�ger
			masked_blit(hero, buffer, 0, 192, this->x_pos, this->y_pos, 64, 64);
		}
	}
	else { //Annars r�r sig spelkarakt�ren
		if(this->direction == 2) { //R�r sig ned�t

			masked_blit(hero, buffer, 64*this->frame, 64,this->x_pos, this->y_pos,64, 64);

		}
		else if(this->direction == 8) { //R�r sig upp�t

			masked_blit(hero, buffer, 64*this->frame, 128,this->x_pos, this->y_pos,64, 64);

		}
		else if(this->direction == 4) { //R�r sig �t v�nster

			masked_blit(hero, buffer, 64*this->frame, 0,this->x_pos, this->y_pos,64, 64);

		}
		else if(this->direction == 6) { //R�r sig �t h�ger

			masked_blit(hero, buffer, 64*this->frame, 192,this->x_pos, this->y_pos,64, 64);

		}
	}
}
/// <summary>Uppdaterar po&auml;ngen f&ouml;r spelaren. </summary>
void Character::updateScore() {
	this->score = this->score + 1;
}
/// <summary> Nollst&auml;ller po&auml;ngen (vid omstart av spel). </summary>
void Character::resetScore() {
	this->score = 0;
}
/// <summary> &Ouml;kar hastigheten p&aring; hur fort karakt&auml;ren r&ouml;r sig. </summary>
void Character::increaseSpeed() {
	this->speed = this->speed + 1;
}
// Minuspo�ng (anv�nds dock inte i denna version av spelet).
void Character::updateLostPoints() {
	this->lost_points = this->lost_points + 1;
}
/// <summary> S&auml;tter en specifik hastighet f&ouml;r karakt&auml;ren (anv&auml;nds vid omstart av spel). </summary>
void Character::setSpeed(int _speed) {
	this->speed = _speed;
}

Character::~Character(void)
{
}
