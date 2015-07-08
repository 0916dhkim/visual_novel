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

struct SceneImageData{
	string image_file_name;
	string image_type;
	string animation_type;
	int image_position[10][2];
};

struct ChangeAttribute{
	string character_name;
	string attribute_name;
	char attribute_operator;
	int change_value;
};

struct SceneChoice{
	int choice_order;
	string choice_content;
	ChangeAttribute change_attribute[10];
};

struct NextSceneCondition{
	string attribute;
	int min;
	int max;
};

struct NextScene{
	int next_id;
	NextSceneCondition next_scene_condition[10];
};

struct SceneFile{
	int scene_id;
	string scene_type;
	SceneImageData scene_image_data[10];
	SceneChoice scene_choice[10];
	NextScene next_scene[10];
};

int load_position_attribute(int* position_array[2], string str);
int load_content_attribute(string* content_attribute, string str);
int load_attribute_attribute(ChangeAttribute* attribute_struct, string str);
int load_scene_file(string filename, SceneFile* scene_file_struct);

#endif