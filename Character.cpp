#include "Character.h"

/// <summary> Default constructor. </summary>
Character::Character(void)
{
	this->x_pos = (rand() %30 + 1)*32; //Slumpar fram position var karaktären hamnar på spleplanen
	this->y_pos = (rand() %22 + 1)*32;
	this->direction = 2; //Spelaren startar i riktning nedåt
	this->check_direction = 0; //Kontrollvariabel för spelaren riktning
	this->score = 0;
	this->speed = 1;
	this->lost_points = 0;
	this->frame = 1;
	this->frameCounter = 0;
}
/// <summary> Flyttar spelkarakt&auml;ren &ouml;ver spelplan </summary>
/// <param name="way"> Vilken riktning karakt&auml;ren skall f&ouml;rflyttas </param>
void Character::move(int way) {

	this->direction = way; //Variabel som kontrollerar åt vilket håll karaktären förflyttas
	this->check_direction = way; //Kontroll-variabel för att hålla koll på om karaktären rör sig åt det hållet eller står still

	if(way == 2) { //2 = förflyttas nedåt
		if(this->y_pos < 736) {
			this->y_pos += this->speed;
		}
	}
	else if(way == 8) { //8 = Förflyttas uppåt
		if(this->y_pos > 10) {
			this->y_pos -= this->speed;
		}
	}
	else if(way == 4) { //4 = Förflyttas vänster
		if(this->x_pos > 0) {
			this->x_pos -= this->speed;
		}
	}
	else if(way == 6) { //6 = Förflyttas höger
		if(this->x_pos < 992) {
			this->x_pos += this->speed;
		}
	}

}
/// <summary> Funktion som kontrollerar n&auml;r en ny "frame"/sprite skall &auml;ndras n&auml;r spelkarakt&auml;ren r&ouml;r sig &ouml;ver banan. </summary>
void Character::movement() {

	this->frameCounter = this->frameCounter + this->speed; //En räknare som håller koll hur många punkter spelkaraktären gått

	if(this->frameCounter > 64*this->frame) { //En sprit-bild är kvadratisk 64 pixlar. När spelaren rört sig 64 punkter ändras bilden

		this->frame = this->frame + 1; //Det finns 4 olika sprite-bilder på karaktären i rörelse

		if(this->frame > 4) { //När man gått igenom hela fjärde bildrutan återställs den till den första igen (1)
			this->frame = 1;
			this->frameCounter = 0; //Räknaren nollställs likaså
		}
	}


}
/// <summary> Ritar ut spelkarakt&auml;ren p&aring; sk&auml;rmen. </summary>
/// <param name="hero"> F&ouml;r att kunna rita ut spelkarakt&auml;ren p&aring; sk&auml;rmen </param>
void Character::draw(BITMAP *buffer, BITMAP *hero) {
	if(this->check_direction == 0) { //Spelkaraktären står stilla
		if(this->direction == 2) { //Karaktären kollar nedåt
			masked_blit(hero, buffer, 0, 64,this->x_pos, this->y_pos,64, 64);
		}
		else if(this->direction == 8) { //Kollar uppåt
			masked_blit(hero, buffer, 0, 128,this->x_pos, this->y_pos,64, 64);
		}
		else if(this->direction == 4) { //Kollar vänster
			masked_blit(hero, buffer, 0, 0, this->x_pos, this->y_pos, 64, 64);
		}
		else if(this->direction == 6) { //Kollar höger
			masked_blit(hero, buffer, 0, 192, this->x_pos, this->y_pos, 64, 64);
		}
	}
	else { //Annars rör sig spelkaraktären
		if(this->direction == 2) { //Rör sig nedåt

			masked_blit(hero, buffer, 64*this->frame, 64,this->x_pos, this->y_pos,64, 64);

		}
		else if(this->direction == 8) { //Rör sig uppåt

			masked_blit(hero, buffer, 64*this->frame, 128,this->x_pos, this->y_pos,64, 64);

		}
		else if(this->direction == 4) { //Rör sig åt vänster

			masked_blit(hero, buffer, 64*this->frame, 0,this->x_pos, this->y_pos,64, 64);

		}
		else if(this->direction == 6) { //Rör sig åt höger

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
// Minuspoäng (används dock inte i denna version av spelet).
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
