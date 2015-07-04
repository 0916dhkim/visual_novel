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

bool is_whitespace(char c){
	if (c == ' ' || c == '\n' || c == '\t' || c == '\0'){
		return true;
	}
	else{
		return false;
	}
};

//Extract one declaration from a scene script.
int extract_declaration(FILE* scene_file, char* declaration_line){
	char current_char;
	int i;
	fpos_t *current_position = NULL;
	fpos_t *end_of_declaration = NULL;
	if(!fgetpos(scene_file, current_position)){
		return 1;
	};
	while (current_char = fgetc(scene_file)){
		if (current_char == ';' || current_char == '{' || current_char == '}'){
			if (!fgetpos(scene_file, end_of_declaration)){
				return 2;
			}
			break;
		}
	}
	//Go back to the beginning of reading.
	if(!fsetpos(scene_file, current_position)){
		return 3;
	}
	//Transfer the declaration into a string.
	for (i = 0; *current_position != *end_of_declaration; i++){
		declaration_line[i] = fgetc(scene_file);
		if (!fgetpos(scene_file, current_position)){
			return 4;
		}
	}
	declaration_line[i] = NULL;

	//Offset scene file by a character.
	fgetc(scene_file);
	return 0;
};

//Separate a declaration into two words.
int declaration_analysis(char* declaration_line, char** analyzed_declaration){
	int i;
	int j = -1;
	int word_count = 0;
	bool was_white = true;
	bool is_white = true;
	bool write_char = false;
	bool paranthesis_open = false;
	for (i = 0; declaration_line[i]; i++){
		//Ignore all whitespaces in ().
		if (declaration_line[i] == '('){
			paranthesis_open = true;
		}
		else if (declaration_line[i] == ')'){
			paranthesis_open = false;
		}
		if (paranthesis_open && is_whitespace(declaration_line[i])){
			continue;
		}
		else{
			is_white = is_whitespace(declaration_line[i]);
		}
		if (was_white){
			write_char = false;
			if (!is_white){
				write_char = true;
				j++;
			}
		}
		else{
			write_char = false;
			if (is_white){
				//Append NULL at the end of each word;
				analyzed_declaration[word_count][j] = NULL;
				word_count++;
				j = -1;
			}
			else{
				write_char = true;
				j++;
			}
		}
		if (write_char){
			analyzed_declaration[word_count][j] = declaration_line[i];
		}
	}
	if (analyzed_declaration[0]){
		return 1;
	}
	return 0;
};

#endif