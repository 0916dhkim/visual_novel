#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "scene.h"
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

struct SceneAudio{
	string audio_type;
	string audio_name;
	string play_option;
};

struct SceneFile{
	int scene_id;
	string scene_type;
	SceneImageData scene_image_data[10];
	SceneChoice scene_choice[10];
	SceneAudio scene_audio[5];
	NextScene next_scene[10];
};

int load_position_attribute(int* position_x, string str){
	string string_buffer[2];
	int i = 0;
	int j = 0;
	while (1){
		if (str.at(i) == '('){
			string_buffer[j] = "";
			continue;
		}
		else if (str.at(i) == ')'){
			break;
		}
		else if (str.at(i) == ','){
			j++;
			string_buffer[j] = "";
		}
		else{
			string_buffer[j] += str.at(i);
		}
		i++;
		if (i > 100){
			return 1;
		}
	}
	*position_x = atoi(string_buffer[0].c_str());
	*(position_x + 1) = atoi(string_buffer[1].c_str());
	return 0;
};

int load_content_attribute(ALLEGRO_USTR* content_attribute, ALLEGRO_USTR* ustr){
	al_ustr_remove_chr(ustr, 0);
	al_ustr_remove_chr(ustr, -1);
	al_ustr_assign(content_attribute, ustr);
	return 0;
}

int load_attribute_attribute(ChangeAttribute* attribute_struct, string str){
	int i = 0;
	int j = 0;
	string change_value_buffer;
	while (1){
		if (str.at(i) == '('){
			i++;
			continue;
		}
		else if (str.at(i) == ')'){
			break;
		}
		else if (str.at(i) == ','){
			j++;
		}
		else{
			if (j == 0){
				(*attribute_struct).character_name += str.at(i);
			}
			else if (j == 1){
				(*attribute_struct).attribute_name += str.at(i);
			}
			else if (j == 2){
				(*attribute_struct).attribute_operator = str.at(i);
			}
			else if (j == 3){
				change_value_buffer += str.at(i);
			}
			else{
				return 1;
			}
		}
		i++;
	}
	(*attribute_struct).change_value = atoi(change_value_buffer.c_str());
	return 0;
};

int load_condition_attribute(NextSceneCondition* next_scene_condition, string str){
	int i = 0;
	int j = 0;
	string min_buffer;
	string max_buffer;
	while (1){
		if (str.at(i) == '('){
			i++;
			continue;
		}
		else if (str.at(i) == ')'){
			break;
		}
		else if (str.at(i) == ','){
			j++;
		}
		else{
			if (j == 0){
				(*next_scene_condition).character += str.at(i);
			}
			else if (j == 1){
				(*next_scene_condition).attribute += str.at(i);
			}
			else if (j == 2){
				min_buffer += str.at(i);
			}
			else if (j == 3){
				max_buffer += str.at(i);
			}
			else{
				return 1;
			}
		}
		i++;
	}
	(*next_scene_condition).min = atoi(min_buffer.c_str());
	(*next_scene_condition).max = atoi(max_buffer.c_str());
	return 0;
};

int load_scene_file(string filename, SceneFile* scene_file_struct){
	ALLEGRO_FILE* punct_file;
	ALLEGRO_USTR* declaration_ustr = al_ustr_new("");
	string type_buffer;
	string content_buffer;
	ALLEGRO_USTR* content_ustr = al_ustr_new("");
	string current_type = "";
	char punctuation_buffer;
	int file_position = 0;
	int declaration_level = 0;
	int image_number = 0;
	int choice_number = 0;
	int audio_number = 0;
	int next_scene_number = 0;
	int position_number = 0;
	int attribute_number = 0;
	int next_condition_number = 0;

	while (1){
		file_position = get_declaration_string(filename, file_position, declaration_ustr);
		if (file_position == -1){
			break;
		}
		type_buffer = get_declaration_type(declaration_ustr);
		content_buffer = get_declaration_content(declaration_ustr);
		content_ustr = get_declaration_ustr_content(declaration_ustr);
		//Get punctuation
		punct_file = al_fopen(filename.c_str(), "r");
		al_fseek(punct_file, file_position, ALLEGRO_SEEK_SET);
		punctuation_buffer = al_fgetc(punct_file);
		file_position = al_ftell(punct_file);
		al_fclose(punct_file);

		//Determine declaration level.
		if (punctuation_buffer == '{'){
			declaration_level = 1;
		}
		else if (punctuation_buffer == '}'){
			declaration_level = 2;
			//If scenefile has multiple elements of one kind, count them.
			if (current_type.compare("image") == 0){
				image_number++;
				position_number = 0;
			}
			else if (current_type.compare("choice") == 0){
				choice_number++;
				attribute_number = 0;
			}
			else if (current_type.compare("audio") == 0){
				audio_number++;
			}
			else if (current_type.compare("next") == 0){
				next_scene_number++;
				next_condition_number = 0;
			}
			continue;
		}
		else if (punctuation_buffer == ';'){
			declaration_level = 2;
		}

		//Load types
		if (declaration_level == 1){
			if (type_buffer.compare("id") == 0){
				cout << "id:";
				current_type = "id";
				(*scene_file_struct).scene_id = atoi(content_buffer.c_str());
			}
			else if (type_buffer.compare("image") == 0){
				cout << "image:";
				current_type = "image";
				(*scene_file_struct).scene_image_data[image_number].image_type = content_buffer;
			}
			else if (type_buffer.compare("choice") == 0){
				cout << "choice:";
				current_type = "choice";
				(*scene_file_struct).scene_choice[choice_number].choice_order = atoi(content_buffer.c_str());
			}
			else if (type_buffer.compare("next") == 0){
				cout << "next:";
				current_type = "next";
				(*scene_file_struct).next_scene[next_scene_number].next_id = atoi(content_buffer.c_str());
			}
			else if (type_buffer.compare("audio") == 0){
				cout << "audio:";
				current_type = "audio";
				(*scene_file_struct).scene_audio[audio_number].audio_type = content_buffer;
			}
			else{
				//syntax error
				return 2;
			}
			cout << content_buffer + "\n";
		}

		//Load attributes.
		else if (declaration_level == 2){
			if (current_type.compare("id") == 0){
				if (type_buffer.compare("type") == 0){
					(*scene_file_struct).scene_type = content_buffer;
				}
				else{
					//type - attribute mismatch
					return 3;
				}
			}
			else if (current_type.compare("image") == 0){
				if (type_buffer.compare("name") == 0){
					(*scene_file_struct).scene_image_data[image_number].image_file_name = content_buffer;
				}
				else if (type_buffer.compare("animation") == 0){
					(*scene_file_struct).scene_image_data[image_number].animation_type = content_buffer;
				}
				else if (type_buffer.compare("position") == 0){
					load_position_attribute(&(*scene_file_struct).scene_image_data[image_number].image_position[position_number][0],content_buffer);
					position_number++;
				}
				else{
					return 3;
				}
			}
			else if (current_type.compare("choice") == 0){
				if (type_buffer.compare("content") == 0){
					load_content_attribute((*scene_file_struct).scene_choice[choice_number].choice_content, content_ustr);
				}
				else if (type_buffer.compare("attribute") == 0){
					load_attribute_attribute(&(*scene_file_struct).scene_choice[choice_number].change_attribute[attribute_number], content_buffer);
					attribute_number++;
				}
				else{
					return 3;
				}
			}
			else if (current_type.compare("audio") == 0){
				if (type_buffer.compare("name") == 0){
					(*scene_file_struct).scene_audio[audio_number].audio_name = content_buffer;
				}
				else if (type_buffer.compare("option") == 0){
					(*scene_file_struct).scene_audio[audio_number].play_option = content_buffer;
				}
				else{
					return 3;
				}
			}
			else if (current_type.compare("next") == 0){
				if (type_buffer.compare("condition") == 0){
					load_condition_attribute(&(*scene_file_struct).next_scene[next_scene_number].next_scene_condition[next_condition_number], content_buffer);
					next_condition_number++;
				}
				else{
					return 3;
				}
			}
		}
	}
	al_ustr_free(declaration_ustr);
	al_ustr_free(content_ustr);
	return 0;
};

#endif