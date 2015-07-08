#ifndef GAME_H
#define GAME_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "scene.h"
#include "game.h"
using namespace std;

float SCREEN_WIDTH = 800;
float SCREEN_HEIGHT = 600;

static string filename;
static int next_scene_id = 0;
static ALLEGRO_BITMAP *scene_image[10];

int play_home(ALLEGRO_EVENT_TYPE home_ev, SceneFile home_scene_file);
int play_game(ALLEGRO_EVENT_TYPE ev);

#endif