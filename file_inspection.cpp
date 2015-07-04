#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifndef FILE_INSPECTION
#define FILE_INSPECTION

#include <stdio.h>
#include <stdlib.h>
#include "file_inspection.h"

struct SceneImageData{
	char image_file_name[256];
	char image_type[256];
	char animation_type[256];
};

struct ChangeAttribute{
	char character_name[256];
	char attribute_name[256];
	float change_value;
};

struct SceneChoice{
	int choice_order;
	char choice_content[256];
	ChangeAttribute change_attribute[256];
};

struct SceneFile{
	int scene_id;
	int scene_type;
	SceneImageData scene_image_data[10];
	SceneChoice scene_choice[10];
};

int parse_command(char* filename, char **parsed_script){
	FILE *scene_file = fopen(filename, "r");
	if (!scene_file){
		return 0;
	}
};

#endif