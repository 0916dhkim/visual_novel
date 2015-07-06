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

fstream::pos_type get_declaration_string(string filename, fstream::pos_type original_pos, string *declaration_string){
	fstream file;
	string string_buffer = "";
	string line_buffer = "";
	char* char_buffer = NULL;
	size_t first_punctuation;
	size_t find_semi_colon = string::npos;
	size_t find_bracket_open = string::npos;
	size_t find_bracket_close = string::npos;

	file.open(filename);
	file.seekg(original_pos);

	while (find_semi_colon == string::npos && find_bracket_open == string::npos && find_bracket_close == string::npos){
		getline(file, line_buffer);
		find_semi_colon = line_buffer.find(';');
		find_bracket_open = line_buffer.find('{');
		find_bracket_close = line_buffer.find('}');
	}

	//Determine the first punctuation.
	if (find_semi_colon < find_bracket_open){
		if (find_semi_colon < find_bracket_close){
			first_punctuation = find_semi_colon;
		}
		else{
			first_punctuation = find_bracket_close;
		}
	}
	else{
		if (find_bracket_open < find_bracket_close){
			first_punctuation = find_bracket_open;
		}
		else{
			first_punctuation = find_bracket_close;
		}
	}

	file.seekg(original_pos);
	cout << first_punctuation - (unsigned int)original_pos << "\n";
	if (first_punctuation - (unsigned int)original_pos > 1000){
		return NULL;
	}
	char_buffer = new char[first_punctuation - (unsigned int)original_pos];
	file.getline(char_buffer, first_punctuation - original_pos);
	line_buffer = char_buffer;
	string_buffer += line_buffer;
	*declaration_string = string_buffer;

	return file.tellg();
};

#endif