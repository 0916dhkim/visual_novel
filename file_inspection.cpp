#ifndef FILE_INSPECTION
#define FILE_INSPECTION

#include <iostream>
#include <fstream>
#include <string>
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
		if (file.eof()){
			return NULL;
		}
		getline(file, line_buffer);
		string_buffer += line_buffer + "\n";
		find_semi_colon = string_buffer.find(';');
		find_bracket_open = string_buffer.find('{');
		find_bracket_close = string_buffer.find('}');
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
	if (first_punctuation == 0){
		file.get();
		*declaration_string = "";
	}
	else {
		char_buffer = new char[first_punctuation + 1];
		file.get(char_buffer, first_punctuation + 1, '\0');
		file.get();
		line_buffer = char_buffer;
		*declaration_string = line_buffer;
	}

	return file.tellg();
};

string get_declaration_type(string declaration_string){
	size_t i;
	string string_buffer="";
	bool was_whitespace = true;

	//Check for the first word in the string.
	for (i = 0; i < declaration_string.size(); i++){
		if (was_whitespace){
			if (!is_whitespace(declaration_string.at(i))){
				string_buffer += declaration_string.at(i);
				was_whitespace = false;
			}
		}
		else{
			if (is_whitespace(declaration_string.at(i))){
				break;
				was_whitespace = true;
			}
			else{
				string_buffer += declaration_string.at(i);
			}
		}
	}
	return string_buffer;
};

string get_declaration_content(string declaration_string){
	string declaration_type = get_declaration_type(declaration_string);
	size_t type_length = declaration_type.size();
	size_t type_position = declaration_string.find(declaration_type);
	size_t i;
	string string_buffer;
	bool was_whitespace = true;
	bool parenthesis_open = false;
	bool quotation_open = false;

	//Check for the first word after type.
	for (i = type_length + type_position; i < declaration_string.size(); i++){
		//Ignore all whitespaces between parenthesis.
		if (declaration_string.at(i) == '('){
			parenthesis_open = true;
		}
		else if (declaration_string.at(i) == ')'){
			if (parenthesis_open){
				parenthesis_open = false;
			}
			else{
				cout << "Opening parenthesis needed.\n";
			}
		}

		if (declaration_string.at(i) == '\"'){
			if (quotation_open){
				quotation_open = false;
			}
			else{
				quotation_open = true;
			}
		}

		if (parenthesis_open && is_whitespace(declaration_string.at(i))){
			continue;
		}

		if (was_whitespace){
			if (!is_whitespace(declaration_string.at(i))){
				string_buffer += declaration_string.at(i);
				was_whitespace = false;
			}
		}
		else{
			if (is_whitespace(declaration_string.at(i)) && !quotation_open){
				break;
				was_whitespace = true;
			}
			else{
				string_buffer += declaration_string.at(i);
			}
		}
	}
	return string_buffer;
};

char get_current_char(string filename, fstream::pos_type current_position){
	fstream file;
	file.open(filename);
	file.seekg(current_position);
	return file.get();
};

#endif