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
	//Anropar funktion för start av timer
	countdownHandler();
 
	while(game.State() != gExit) {
		
		//counter som balanserar spelets hastighet
		while(counter > 0) {
			//Meny
			if(game.State() == gMenu)
			{
				if(key[KEY_1]) { //Spelet sätts igång från början
					for(int n = 0; n < tr[0].getTotal_treasure(); ++n) { //Tar bort alla diamnter i spelet
						tr[n].remove_treasure();
					}
					c1.setSpeed(1); //Återställer spelkaraktärens hastighet
					tr[0].setTotal_treasure(2); //Återställer antalet diamanter
					newDiamondPos(tr, tr[0].getTotal_treasure()); //Slumpar fram ny positionering
					tr[0].resetPicked_treasure(); //Nollställer räknaren
					c1.resetScore(); //Nollställer poängen
					game.resetLevel(); //Nollställer nivå-räknaren
					game.State(gInGame); //Ändrar läget i spelet
					gem_counter = 10; //Sätter timern till 10
				}
				else if(key[KEY_2]) { game.State(gInfo); } //Går till "Om spelet"
				else if(key[KEY_3]) { game.State(gExit); } // Spelet avslutas
			}
			//Själva spelet
			else if(game.State() == gInGame || game.State() == gNextLevel)
			{
				if(keypressed()) { //När man inte styr spelaren står karaktären stilla
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

				//Loop som kontrollerar om spelaren befinner sig på en diamant
				for(int k = 0; k < tr[0].getTotal_treasure(); ++k) {
					if(tr[k].pickedUp(c1)) {
						//Om spelaren befinner sig på samma position som en diamant
						//försvinner den
						
						tr[0].updatePicked_treasure(); //Uppdaterar hur många diamanter som spelaren plockat upp under en nivå
						//Uppdaterar spelarens poäng
						c1.updateScore();
					}
				}

				if(tr[0].getTotal_treasure() == tr[0].getPicked_treasure()) { //Alla diamanter upplockade innan tiden löpt ut
					game.State(gNextLevel); //Ny nivå
					game.changeLevel(); //Uppdaterar nivån

					if(game.getLevel() == 10) { //När man befinner sig på nivå 10 ökas hastigheten på spelkaraktären
						c1.increaseSpeed();
					}
					tr[0].resetPicked_treasure(); //Nollställer räknaren


				}


				if(gameTime() < 0) {
					for(int m = 0; m < tr[0].getTotal_treasure(); ++m) {
						//Om inte alla diamanter är upplockade innan tiden löper ut
						if(!tr[m].getPickedUp()) {
							game.State(gGameOver); //Ändrar läge till Game Over
							if(game.getHighScore() < c1.getScore()) { //Kontrollerar om poängen är högre än high score
								game.setHighScore(c1.getScore());
							}
						}
					}
					if(game.State() == gNextLevel) { //Om alla diamanter är upplockade befinner man sig i detta läge
						//Efter var 5:e nivå uppdateras spelet med ytterligare en diamant på spelplan
						if(game.getLevel() % 5 == 0) {
							tr[0].updateTotal_treasure();
						}
						game.State(gInGame); //Ändrar läge
						newDiamondPos(tr, tr[0].getTotal_treasure()); //Slumpar fram nya positioner
						gem_counter = 10; //Återställer timern
					}
				}
				//Gå tillbaka till menyn
				if(key[KEY_ESC])
				{
					game.State(gMenu);
				}
			}
			//About (om)
			else if(game.State() == gInfo)
			{
				//Gå tillbaka till menyn
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

			counter--; //Nedräkning av counter
		} //Slut på while(counter > 0)
		
		//Här skrivs all grafik ut
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
			//Ritar ut spelkaraktären
			c1.draw(buffer, hero);
			
			//Ritar ut diamanterna i spelet
			for(int l = 0; l < tr[0].getTotal_treasure(); ++l) {
				tr[l].draw(buffer, diamond);
			}
			
			//Skriver ut all text under spelets gång
			game.gameTextOutput(buffer, c1, gameTime());

		}
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(buffer);
		release_screen();
	} //Slut på while
 
    //slut på programmet
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