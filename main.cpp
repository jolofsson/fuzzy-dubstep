#include <allegro.h>
#include <ctime>
#include "initializeAllegro.h"
#include "Character.h"
#include "Treasure.h"
#include "Game.h"

#define MAX_DIAMONDS 7 //Max antal diamanter som finns i spelet

//Slumpar ut diamanternas position
void newDiamondPos(Treasure tr[], int diamonds) {
	for(int l = 0; l < diamonds; ++l) {
		tr[l].randomiseNewPosition();
	}
}

 
int main(void)
{
	//Startar upp allegro
	initResources();

	BITMAP *buffer = create_bitmap(1024, 768);
	BITMAP *diamond = load_bmp("gem.bmp", NULL); //Laddar in alla bilder
	BITMAP *grass = load_bmp("grass.bmp", NULL);
	BITMAP *hero = load_bmp("john-ovr.bmp", NULL);
	BITMAP *menu = load_bmp("background.bmp", NULL);
	BITMAP *about = load_bmp("about.bmp", NULL);

	Game game;
	Character c1;
	Treasure tr[MAX_DIAMONDS];
	//Anropar funktion f�r start av timer
	countdownHandler();
 
	while(game.State() != gExit) {
		
		//counter som balanserar spelets hastighet
		while(counter > 0) {
			//Meny
			if(game.State() == gMenu)
			{
				if(key[KEY_1]) { //Spelet s�tts ig�ng fr�n b�rjan
					for(int n = 0; n < tr[0].getTotal_treasure(); ++n) { //Tar bort alla diamnter i spelet
						tr[n].remove_treasure();
					}
					c1.setSpeed(1); //�terst�ller spelkarakt�rens hastighet
					tr[0].setTotal_treasure(2); //�terst�ller antalet diamanter
					newDiamondPos(tr, tr[0].getTotal_treasure()); //Slumpar fram ny positionering
					tr[0].resetPicked_treasure(); //Nollst�ller r�knaren
					c1.resetScore(); //Nollst�ller po�ngen
					game.resetLevel(); //Nollst�ller niv�-r�knaren
					game.State(gInGame); //�ndrar l�get i spelet
					gem_counter = 10; //S�tter timern till 10
				}
				else if(key[KEY_2]) { game.State(gInfo); } //G�r till "Om spelet"
				else if(key[KEY_3]) { game.State(gExit); } // Spelet avslutas
			}
			//Sj�lva spelet
			else if(game.State() == gInGame || game.State() == gNextLevel)
			{
				if(keypressed()) { //N�r man inte styr spelaren st�r karakt�ren stilla
					c1.standStill();
				}
				//Styr spelaren med piltangenterna
				if(key[KEY_UP]) {
					c1.move(8);
					c1.movement();
				}
				else if(key[KEY_DOWN]) {
					c1.move(2);
					c1.movement();
				}
				if(key[KEY_LEFT]) {
					c1.move(4);
					c1.movement();
				}
				else if(key[KEY_RIGHT]) {
					c1.move(6);
					c1.movement();
				}

				//Loop som kontrollerar om spelaren befinner sig p� en diamant
				for(int k = 0; k < tr[0].getTotal_treasure(); ++k) {
					if(tr[k].pickedUp(c1)) {
						//Om spelaren befinner sig p� samma position som en diamant
						//f�rsvinner den
						
						tr[0].updatePicked_treasure(); //Uppdaterar hur m�nga diamanter som spelaren plockat upp under en niv�
						//Uppdaterar spelarens po�ng
						c1.updateScore();
					}
				}

				if(tr[0].getTotal_treasure() == tr[0].getPicked_treasure()) { //Alla diamanter upplockade innan tiden l�pt ut
					game.State(gNextLevel); //Ny niv�
					game.changeLevel(); //Uppdaterar niv�n

					if(game.getLevel() == 10) { //N�r man befinner sig p� niv� 10 �kas hastigheten p� spelkarakt�ren
						c1.increaseSpeed();
					}
					tr[0].resetPicked_treasure(); //Nollst�ller r�knaren


				}


				if(gameTime() < 0) {
					for(int m = 0; m < tr[0].getTotal_treasure(); ++m) {
						//Om inte alla diamanter �r upplockade innan tiden l�per ut
						if(!tr[m].getPickedUp()) {
							game.State(gGameOver); //�ndrar l�ge till Game Over
							if(game.getHighScore() < c1.getScore()) { //Kontrollerar om po�ngen �r h�gre �n high score
								game.setHighScore(c1.getScore());
							}
						}
					}
					if(game.State() == gNextLevel) { //Om alla diamanter �r upplockade befinner man sig i detta l�ge
						//Efter var 5:e niv� uppdateras spelet med ytterligare en diamant p� spelplan
						if(game.getLevel() % 5 == 0) {
							tr[0].updateTotal_treasure();
						}
						game.State(gInGame); //�ndrar l�ge
						newDiamondPos(tr, tr[0].getTotal_treasure()); //Slumpar fram nya positioner
						gem_counter = 10; //�terst�ller timern
					}
				}
				//G� tillbaka till menyn
				if(key[KEY_ESC])
				{
					game.State(gMenu);
				}
			}
			//About (om)
			else if(game.State() == gInfo)
			{
				//G� tillbaka till menyn
				if(key[KEY_ESC])
				{
					game.State(gMenu);
				}
			}
			//Game over
			else if(game.State() == gGameOver)
			{
				if(key[KEY_ESC])
				{
					game.State(gMenu);
				}
			}

			counter--; //Nedr�kning av counter
		} //Slut p� while(counter > 0)
		
		//H�r skrivs all grafik ut
		acquire_screen();
		if(game.State() == gMenu) //Ritar ut menyn
		{
			draw_sprite(buffer, menu, 0, 0);
		}
		else if(game.State() == gInfo) { //Visar About (om)-menyn
			draw_sprite(buffer, menu, 0, 0);
			draw_sprite(buffer, about, 350, 450);
		}
		else if(game.State() == gInGame || game.State() == gGameOver || game.State() == gNextLevel)
		{
			//Loop som ritar ut bakgrunden i spelet
			for(int i = 0; i < SCREEN_W/32; ++i) {
				for(int j = 0; j < SCREEN_H/32; ++j) {
					draw_sprite(buffer, grass, i*32, j*32);
				}
			}
			//Ritar ut spelkarakt�ren
			c1.draw(buffer, hero);
			
			//Ritar ut diamanterna i spelet
			for(int l = 0; l < tr[0].getTotal_treasure(); ++l) {
				tr[l].draw(buffer, diamond);
			}
			
			//Skriver ut all text under spelets g�ng
			game.gameTextOutput(buffer, c1, gameTime());

		}
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(buffer);
		release_screen();
	} //Slut p� while
 
    //slut p� programmet
	destroy_bitmap(menu);
	destroy_bitmap(about);
	destroy_bitmap(hero);
	destroy_bitmap(diamond);
	destroy_bitmap(grass);
	destroy_bitmap(buffer);
    allegro_exit();
    return 0;
}
END_OF_MAIN()