#include "mytree.h"

int word_comp(const char* w1, const char* w2)
{ char c1,c2;
  while(1)
  {
	  if(*w1 != *w2) 
	  {
		c1=*w1+32*(*w1>='A' && *w1<='Z');
		c2=*w2+32*(*w2>='A' && *w2<='Z');
		if(c1 !=c2) break;
	  }
	  if(*w1==0 || *w2==0) break;
	  w1++;
	  w2++;
  }
  if(*w1==*w2) return 0;
  return c1-c2;
}

void sort(char** cdp, int num)
{
	int min;
	for (int i = 0; i < num; i++) 
	{
		min = i;
		for (int j = i + 1; j < num; j++) 
		{
			if (word_comp(cdp[min], cdp[j]) > 0)
				min = j;
		}
		if (i != min) 
		{
			char* tmp = cdp[min];
			cdp[min] = cdp[i];
			cdp[i] = tmp;
		}
	}
}
void remove_file(char** cdp, int* ip, int num)
{
	while (*ip<num && (cdp[*ip])[0] == '.' ) 
	{
	  (*ip)++;
	}
}

void dirSeek(char* path)
{
	struct stat stats;
	char* file[512];
	char pathname[512];
	int cnt = 0, read_count = 0;
	DIR* dirp;
	struct dirent* dentry;
	visited[vi_count] = YES;
	if ((dirp = opendir(path)) < 0) 
	{
		perror("open error");
		exit(1);
	}
	
	while ((dentry = readdir(dirp)) != NULL) 
	{
		file[cnt] = dentry->d_name;
		cnt++;
	}
	
	sort(file, cnt);
	remove_file(file, &read_count, cnt);
	
	for (int i = read_count; i < cnt; i++)
	{ 	
		for (int j = 0; j < vi_count; j++)
		{
			if (visited[j] == YES)
				printf(" │   ");
			else
				printf("     ");
		}

		if ((i + 1) != cnt) 
		{
			printf(" ├");
		}
		else 
		{
			visited[vi_count] = NO;
			printf(" └");
		}

		printf("── ");
		strcpy(pathname,path);
                if (pathname[strlen(pathname) - 1] != '/')
		strcat(pathname, "/");
		strcat(pathname, file[i]);
		if(lstat(pathname, &stats)<0) 
		{perror("stat error"); exit(1);}
		print_list(&stats,file[i]);
		if (S_ISDIR(stats.st_mode)) 
		{
			vi_count++;
			dir_count++;
			dirSeek(pathname);
			vi_count--;
		}
		else
			file_count++;
	}
}

int main()
{
	memset(visited, 0, sizeof(int) * 1024);
	struct stat st;
	lstat(".",&st);
	print_list(&st,".");
	dirSeek(".");
	printf("\n\n%d directories, %d files\n", dir_count, file_count);
	return 0;
}
