#pragma once
#ifndef INITIALIZEALLEGRO_H
#define INITIALIZEALLEGRO_H
#include <allegro.h>

volatile long counter = 0;

/// <summary> R&auml;knare f&ouml;r att f&aring; en j&auml;mn hastighet i spelet </summary>
void increment_counter() {
	counter++;
}
END_OF_FUNCTION(increment_counter);

void initResources();

/// <summary> L&auml;ser in alla n&ouml;dv&auml;ndiga allegro-resurser. </summary>
void initResources() {
	allegro_init();
	//32-bitar samt fönsterläge i upplösning 1024x768
	set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0);
    install_keyboard();
	install_timer();
	set_window_title("Diamond Hunter");

	//Låser minnet
	LOCK_VARIABLE(counter);
	LOCK_FUNCTION(increment_counter);
	//För justering av spelets hastighet (fps). Satt till 120 BPS, ticks per sekund
	install_int_ex(increment_counter, BPS_TO_TIMER(120));
	srand((unsigned)time(NULL));
}
END_OF_FUNCTION(initResources);

unsigned int gem_counter = 10; //Räkna ned från 10 (sekunder)

/// <summary> Nedr&auml;knare (r&auml;knar per sekund). </summary>
void countdownGem() {
	gem_counter--;
}
END_OF_FUNCTION(countdownGem);

void countdownHandler();

/// <summary> Funktion f&ouml;r att hantera nedr&auml;knaren i spelet. </summary>
void countdownHandler() {
	LOCK_VARIABLE(gem_counter);
	LOCK_FUNCTION(countdownGem);
	install_int_ex(countdownGem, SECS_TO_TIMER(1)); //sekund
}
END_OF_FUNCTION(countdownHandler);

int gameTime();

/// <summary> Returnerar vilket v&auml;rde timern har. </summary>
int gameTime() {

	return gem_counter;
}
END_OF_FUNCTION(gameTime);

#endif