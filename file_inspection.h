#ifndef FILE_INSPECTION_H
#define FILE_INSPECTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
using namespace std;

bool is_whitespace(char c);
int get_declaration_string(string filename, int original_pos, ALLEGRO_USTR* declaration_ustr);
string get_declaration_type(ALLEGRO_USTR* declaration_ustr);
string get_declaration_content(ALLEGRO_USTR* declaration_ustr);
ALLEGRO_USTR* get_declaration_ustr_content(ALLEGRO_USTR* declaration_ustr);
char get_current_char(string filename, int current_position);

#endif