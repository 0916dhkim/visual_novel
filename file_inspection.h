#ifndef FILE_INSPECTION
#define FILE_INSPECTION

#include <iostream>
#include <fstream>
#include <string>
#include "file_inspection.h"
using namespace std;

struct SceneImageData{
	string image_file_name;
	string image_type;
	string animation_type;
};

struct ChangeAttribute{
	string character_name;
	string attribute_name;
	float change_value;
};

struct SceneChoice{
	int choice_order;
	string choice_content;
	ChangeAttribute change_attribute[256];
};

struct SceneFile{
	int scene_id;
	int scene_type;
	SceneImageData scene_image_data[10];
	SceneChoice scene_choice[10];
};

fstream::pos_type get_declaration_string(string filename, fstream::pos_type original_pos, string* declaration_string);

#endif