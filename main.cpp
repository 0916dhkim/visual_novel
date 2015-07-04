#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "scene.h"

float SCREEN_WIDTH = 800;
float SCREEN_HEIGHT = 600;
int FPS = 60;

int main(){
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;
	bool mouse_click = false;

	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);

	while (true){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.type == ALLEGRO_EVENT_KEY_DOWN){
			redraw = false;
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			redraw = false;
		}

		if (redraw){
			redraw = false;
			al_flip_display();
		}
	}
	return 0;
}
