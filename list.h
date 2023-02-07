#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
typedef struct print_List {
    int i_num;
    int d_num;
    char permission[11];
    char owner[20];
    double filesize;
    char filename[4096];
}p_list;

char* check_permission(struct stat*, p_list*);
int get_Inum(struct stat*);
int get_Dev(struct stat*);
double get_Size(struct stat*);
void print_list(struct stat*,char *);
