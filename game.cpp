#ifndef GAME_H
#define GAME_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "scene.h"
#include "game.h"
using namespace std;

static float SCREEN_WIDTH = 800;
static float SCREEN_HEIGHT = 600;

static string filename;
static int next_scene_id = 0;
static ALLEGRO_BITMAP *scene_image[10];

int load_home(SceneFile home_scene_file){
	int i;
	for (i = 0; i < 10; i++){
		if (home_scene_file.scene_image_data[i].image_file_name != ""){
			scene_image[i] = al_load_bitmap(home_scene_file.scene_image_data[i].image_file_name.c_str());
		}
	}
	return 0;
}

int play_home(ALLEGRO_EVENT_TYPE home_ev, SceneFile home_scene_file){
	int i;
	for (i = 0; i < 10; i++){
		if (home_scene_file.scene_image_data[i].image_type.compare("background") == 0){
			al_draw_scaled_bitmap(scene_image[i], 0, 0, al_get_bitmap_width(scene_image[i]), al_get_bitmap_height(scene_image[i]), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		}
	}
	return 0;
}

int play_game(ALLEGRO_EVENT_TYPE ev){
	static SceneFile scene_file;
	static bool end_of_scene = true;
	string scene_type;
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
		play_home(ev, scene_file);
	}
	return 0;
};

#endif