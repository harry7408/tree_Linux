#include "list.h"
#include<math.h>
char* check_permission(struct stat* pbuf, p_list* list)
{
    if (S_ISDIR(pbuf->st_mode))
        list->permission[0] = 'd';
    else if (S_ISCHR(pbuf->st_mode))
        list->permission[0] = 'c';
    else if (S_ISBLK(pbuf->st_mode))
        list->permission[0] = 'b';
    else if (S_ISFIFO(pbuf->st_mode))
        list->permission[0] = 'p';
    else if (S_ISSOCK(pbuf->st_mode))
        list->permission[0] = 's';
    else if (S_ISLNK(pbuf->st_mode))
        list->permission[0] = 'l';
    else
        list->permission[0] = '-';
    if (pbuf->st_mode & S_IRUSR)
        list->permission[1] = 'r';
    else
        list->permission[1] = '-';

    if (pbuf->st_mode & S_IWUSR)
        list->permission[2] = 'w';
    else
        list->permission[2] = '-';
    if (pbuf->st_mode & S_IXUSR)
        list->permission[3] = 'x';
    else
        list->permission[3] = '-';
    if (pbuf->st_mode & S_IRGRP)
        list->permission[4] = 'r';
    else
        list->permission[4] = '-';
    if (pbuf->st_mode & S_IWGRP)
        list->permission[5] = 'w';
    else
        list->permission[5] = '-';
    if (pbuf->st_mode & S_IXGRP)
        list->permission[6] = 'x';
    else
        list->permission[6] = '-';
    if (pbuf->st_mode & S_IROTH)
        list->permission[7] = 'r';
    else
        list->permission[7] = '-';
    if (pbuf->st_mode & S_IWOTH)
        list->permission[8] = 'w';
    else
        list->permission[8] = '-';

    if (pbuf->st_mode & S_IXOTH)
        list->permission[9] = 'x';
    else
        list->permission[9] = '-';
    list->permission[10] = '\0';
    return list->permission;
}
int get_Inum(struct stat* pbuf)
{
    return (int)pbuf->st_ino;
}

int get_Dev(struct stat* pbuf)
{
    return (int)pbuf->st_dev;
}

double get_Size(struct stat* pbuf)
{
    return (double)pbuf->st_size;
}
void print_list(struct stat* pbuf,char *c)
{
    p_list *p=malloc(sizeof(p_list));
    struct passwd* pwd;
    char* mode;
    
    mode = check_permission(pbuf, p);
    p->i_num = get_Inum(pbuf);
    p->d_num = get_Dev(pbuf);
    p->filesize = get_Size(pbuf);
    strcpy(p->permission, mode);
    pwd = getpwuid(pbuf->st_uid);
    strcpy(p->owner, pwd->pw_name);
    if(p->filesize<1000)
     printf(" [%7d %-5d %-9s %-5s %6.0f] %-6s\n", p->i_num, p->d_num, p->permission, p->owner,p->filesize,c);	    
    else
    printf(" [%7d %-5d %-9s %-5s %5.1f%c] %-6s\n", p->i_num, p->d_num, p->permission, p->owner,floor(p->filesize/1000),'K',c);
}
