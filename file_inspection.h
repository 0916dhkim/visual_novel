#ifndef FILE_INSPECTION_H
#define FILE_INSPECTION_H

#include <iostream>
#include <fstream>
#include <string>
#include "file_inspection.h"
using namespace std;

bool is_whitespace(char c);
fstream::pos_type get_declaration_string(string filename, fstream::pos_type original_pos, string* declaration_string);
string get_declaration_type(string declaration_string);
string get_declaration_content(string declaration_string);
char get_current_char(string filename, fstream::pos_type current_position);

#endif