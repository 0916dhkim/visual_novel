#ifndef GAME_H
#define GAME_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "scene.h"
#include "game.h"
using namespace std;

float SCREEN_WIDTH = 1200;
float SCREEN_HEIGHT = 900;

static string filename;
static int next_scene_id = 0;
static ALLEGRO_BITMAP *scene_image[10];

int load_home(SceneFile home_scene_file);
int play_home(ALLEGRO_EVENT_TYPE home_ev, SceneFile home_scene_file, ALLEGRO_FONT* font);
int play_game(ALLEGRO_EVENT_TYPE ev, ALLEGRO_FONT* font);

#endif