#ifndef FILE_INSPECTION_H
#define FILE_INSPECTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
#include "file_inspection.h"
using namespace std;

bool is_whitespace(char c){
	if (c == ' ' || c == '\n' || c == '\t' || c == '\0'){
		return true;
	}
	else{
		return false;
	}
};

int get_declaration_string(string filename, int original_pos, ALLEGRO_USTR* declaration_ustr){
	ALLEGRO_FILE* file = NULL;
	ALLEGRO_USTR* ustr_buffer = al_ustr_new("");
	ALLEGRO_USTR* ustr_line_buffer = al_ustr_new("");
	int semi_colon_pos = -1;
	int bracket_open_pos = -1;
	int bracket_close_pos = -1;
	int first_punct = -1;
	int last_punct = -1;
	int final_pos = -1;

	file = al_fopen(filename.c_str(), "r");
	if (file == NULL){
		cout << "Failed to open scene file.\n";
		return -1;
	}

	//Go to original position.
	al_fseek(file, original_pos, ALLEGRO_SEEK_SET);

	while (semi_colon_pos == -1 && bracket_open_pos == -1 && bracket_close_pos == -1){
		//Break on EOF.
		if (al_feof(file)){
			cout << "EOF reached.\n";
			return -1;
		}
		ustr_line_buffer = al_fget_ustr(file);
		al_ustr_append(ustr_buffer, ustr_line_buffer);

		semi_colon_pos = al_ustr_find_chr(ustr_buffer, 0, ';');
		bracket_open_pos = al_ustr_find_chr(ustr_buffer, 0, '{');
		bracket_close_pos = al_ustr_find_chr(ustr_buffer, 0, '}');
	}

	//Find the first punctuation offset.
	if (semi_colon_pos > bracket_open_pos){
		if (semi_colon_pos > bracket_close_pos){
			last_punct = semi_colon_pos;
		}
		else{
			last_punct = bracket_close_pos;
		}
	}
	else{
		if (bracket_open_pos > bracket_close_pos){
			last_punct = bracket_open_pos;
		}
		else{
			last_punct = bracket_close_pos;
		}
	}
	if (semi_colon_pos == -1){
		semi_colon_pos = last_punct + 1;
	}
	if (bracket_open_pos == -1){
		bracket_open_pos = last_punct + 1;
	}
	if (bracket_close_pos == -1){
		bracket_close_pos = last_punct + 1;
	}
	if (semi_colon_pos < bracket_open_pos){
		if (semi_colon_pos < bracket_close_pos){
			first_punct = semi_colon_pos;
		}
		else{
			first_punct = bracket_close_pos;
		}
	}
	else{
		if (bracket_open_pos < bracket_close_pos){
			first_punct = bracket_open_pos;
		}
		else{
			first_punct = bracket_close_pos;
		}
	}

	//Get the declaration ustr.
	al_fseek(file, original_pos, ALLEGRO_SEEK_SET);
	al_fread(file, ustr_line_buffer, first_punct);
	al_ustr_remove_range(ustr_buffer, first_punct, al_ustr_size(ustr_buffer));
	al_ustr_append_chr(ustr_buffer, 0);
	al_ustr_assign(declaration_ustr, ustr_buffer);
	final_pos = al_ftell(file);
	al_fclose(file);
	return final_pos;
};

string get_declaration_type(ALLEGRO_USTR* declaration_ustr){
	//size_t i;
	int i;
	string string_buffer = "";
	bool was_whitespace = true;

	//Check for the first word in the string.
	i = 0;
	while (1){
		if (i >= al_ustr_size(declaration_ustr)){
			break;
		}
		if (was_whitespace){
			if (!is_whitespace(al_ustr_get(declaration_ustr, i))){
				string_buffer += al_ustr_get(declaration_ustr, i);
				was_whitespace = false;
			}
		}
		else{
			if (is_whitespace(al_ustr_get(declaration_ustr, i))){
				break;
				was_whitespace = true;
			}
			else{
				string_buffer += al_ustr_get(declaration_ustr, i);
			}
		}
		i++;
	}
	return string_buffer;
};

string get_declaration_content(ALLEGRO_USTR* declaration_ustr){
	string declaration_type = get_declaration_type(declaration_ustr);
	int type_length = declaration_type.size();
	int type_position = al_ustr_find_cstr(declaration_ustr, 0, declaration_type.c_str());
	int i;
	string string_buffer;
	bool was_whitespace = true;
	bool parenthesis_open = false;
	bool quotation_open = false;

	//Check for the first word after type.
	i = type_position + type_length;
	while (1){
		if (i >= al_ustr_size(declaration_ustr)){
			break;
		}
		//Ignore all whitespaces between parenthesis.
		if (al_ustr_get(declaration_ustr, i) == '('){
			parenthesis_open = true;
		}
		else if (al_ustr_get(declaration_ustr, i) == ')'){
			if (parenthesis_open){
				parenthesis_open = false;
			}
			else{
				cout << "Opening parenthesis needed.\n";
			}
		}

		if (al_ustr_get(declaration_ustr, i) == '\"'){
			if (quotation_open){
				quotation_open = false;
			}
			else{
				quotation_open = true;
			}
		}

		if (parenthesis_open && is_whitespace(al_ustr_get(declaration_ustr, i))){
			i++;
			continue;
		}

		if (was_whitespace){
			if (!is_whitespace(al_ustr_get(declaration_ustr, i))){
				string_buffer += al_ustr_get(declaration_ustr, i);
				was_whitespace = false;
			}
		}
		else{
			if (is_whitespace(al_ustr_get(declaration_ustr, i)) && !quotation_open){
				break;
				was_whitespace = true;
			}
			else{
				string_buffer += al_ustr_get(declaration_ustr, i);
			}
		}
		i++;
	}
	return string_buffer;
}

ALLEGRO_USTR* get_declaration_ustr_content(ALLEGRO_USTR* declaration_ustr){
	string declaration_type = get_declaration_type(declaration_ustr);
	int type_length = declaration_type.size();
	int type_position = al_ustr_find_cstr(declaration_ustr, 0, declaration_type.c_str());
	int i;
	ALLEGRO_USTR* ustr_buffer = al_ustr_new("");
	bool was_whitespace = true;
	bool parenthesis_open = false;
	bool quotation_open = false;

	//Check for the first word after type.
	for (i = type_length + type_position; i < (int)al_ustr_length(declaration_ustr); i++){
		//Ignore all whitespaces between parenthesis.
		if (al_ustr_get(declaration_ustr, i) == '('){
			parenthesis_open = true;
		}
		else if (al_ustr_get(declaration_ustr, i) == ')'){
			if (parenthesis_open){
				parenthesis_open = false;
			}
			else{
				cout << "Opening parenthesis needed.\n";
			}
		}

		if (al_ustr_get(declaration_ustr, i) == '\"'){
			if (quotation_open){
				quotation_open = false;
			}
			else{
				quotation_open = true;
			}
		}

		if (parenthesis_open && is_whitespace(al_ustr_get(declaration_ustr, i))){
			continue;
		}

		if (was_whitespace){
			if (!is_whitespace(al_ustr_get(declaration_ustr, i))){
				al_ustr_append_chr(ustr_buffer, al_ustr_get(declaration_ustr, i));
				was_whitespace = false;
			}
		}
		else{
			if (is_whitespace(al_ustr_get(declaration_ustr, i)) && !quotation_open){
				break;
				was_whitespace = true;
			}
			else{
				al_ustr_append_chr(ustr_buffer, al_ustr_get(declaration_ustr, i));
			}
		}
	}
	return ustr_buffer;
}

char get_current_char(string filename, int current_position){
	ALLEGRO_FILE* file = NULL;
	char char_buffer;
	file = al_fopen(filename.c_str(), "r");
	al_fseek(file, current_position, ALLEGRO_SEEK_SET);
	char_buffer = al_fgetc(file);
	al_fclose(file);
	return char_buffer;
}

#endif