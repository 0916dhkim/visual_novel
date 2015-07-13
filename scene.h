#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "file_inspection.h"

using namespace std;

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
	ALLEGRO_USTR* choice_content;
	ChangeAttribute change_attribute[10];
};

struct NextSceneCondition{
	string character;
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

int load_position_attribute(int* position_x, string str);
int load_content_attribute(ALLEGRO_USTR* content_attribute, ALLEGRO_USTR* ustr);
int load_attribute_attribute(ChangeAttribute* attribute_struct, string str);
int load_condition_attribute(NextSceneCondition* next_scene_condition, string str);
int load_scene_file(string filename, SceneFile* scene_file_struct);

#endif