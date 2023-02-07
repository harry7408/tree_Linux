#pragma once
#include "list.h"
#define END 0
#define YES 1
#define NO 2
int visited[1024];
int vi_count;
int dir_count;
int file_count;

int word_comp(const char*, const char*);
void sort(char**, int);
void remove_file(char**, int*, int);
void dirSeek(char*);
