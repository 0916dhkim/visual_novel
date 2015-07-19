#ifndef GAME_H
#define GAME_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "scene.h"
#include "game.h"
using namespace std;

static float SCREEN_WIDTH = 1200;
static float SCREEN_HEIGHT = 900;

static string filename;
static int next_scene_id = 0;
static ALLEGRO_BITMAP *scene_image[10];
static ALLEGRO_SAMPLE *asample[5];

int load_home(SceneFile home_scene_file){
	int i;
	for (i = 0; i < 10; i++){
		if (home_scene_file.scene_image_data[i].image_file_name != ""){
			scene_image[i] = al_load_bitmap(home_scene_file.scene_image_data[i].image_file_name.c_str());
		}
	}
	if (home_scene_file.scene_audio[0].audio_type.compare("play") == 0){
		asample[0] = al_load_sample(home_scene_file.scene_audio[0].audio_name.c_str());
		if (asample[0] == NULL){
			cout << "No audio loaded.\n";
		}
	}
	return 0;
}

int play_home(ALLEGRO_EVENT_TYPE home_ev, SceneFile home_scene_file, ALLEGRO_FONT* font){
	int i;
	int button_x = SCREEN_WIDTH/2 - 250;
	int button_y = SCREEN_HEIGHT/2 - 40;

	for (i = 0; i < 10; i++){
		if (home_scene_file.scene_image_data[i].image_type.compare("background") == 0){
			al_draw_scaled_bitmap(scene_image[i], 0, 0, al_get_bitmap_width(scene_image[i]), al_get_bitmap_height(scene_image[i]), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		}
		else if (home_scene_file.scene_image_data[i].image_type.compare("choice") == 0){
			al_draw_bitmap(scene_image[i], button_x, button_y, 0);
		}
		if (home_scene_file.scene_audio[0].audio_type.compare("play") == 0){
			al_play_sample(asample[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		}
		if (home_scene_file.scene_choice[0].choice_order != NULL){
			al_draw_ustr(font, al_map_rgb(0,0,0), button_x + 250, button_y + 10, ALLEGRO_ALIGN_CENTER, home_scene_file.scene_choice[0].choice_content);
		}

	}
	return 0;
}

int play_game(ALLEGRO_EVENT_TYPE ev, ALLEGRO_FONT* font){
	static bool end_of_scene = true;
	static SceneFile scene_file;
	string scene_type;

	al_reserve_samples(5);

	if (end_of_scene){
		filename = "scene_" + to_string(next_scene_id) + ".txt";
		load_scene_file(filename, &scene_file);
		scene_type = scene_file.scene_type;
		//Analyze scene type.
		if (scene_type.compare("home") == 0){
			load_home(scene_file);
		}
		end_of_scene = false;
	}
	//filename = "scene_" + to_string(next_scene_id) + ".txt";
	//load_scene_file(filename, &scene_file);
	//Check for matching id.
	if (scene_file.scene_id != next_scene_id){
		return 1;
	}
	//Analyze scene type.
	scene_type = scene_file.scene_type;
	if (scene_type.compare("home") == 0){
		play_home(ev, scene_file, font);
	}

	return 0;
};

#endif