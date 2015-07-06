#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "scene.h"
#include "file_inspection.h"

using namespace std;

static int SCENE_HOME = 0;
static int SCENE_HOME_EDITOR = 1;
static int SCENE_SCENE = 2;
static int SCENE_SCENE_EDITOR = 3;
static int SCENE_CHARACTER_SELECTION = 4;
static int SCENE_CHARACTER_SELECTION_EDITOR = 5;
static int SCENE_CG = 6;
static int SCENE_CG_EDITOR = 7;

static int ANIMATION_TYPE_NONE = 0;

class SceneImage{
private:
	char image_name[256];
	float image_x;
	float image_y;
	int animation_type;
public:
};

class Scene{
	private:
		int scene_type;
		int scene_id;
		int next_scene_id;
		SceneImage scene_image_array[10];
		string filename;
};

#endif