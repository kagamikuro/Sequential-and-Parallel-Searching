#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	int status;
	status = mkdir("inputs/test2",S_IRWXU | S_IRWXG | S_IRWXO);
	if(!status)
		printf("Directory test2 created\n");
	int fd;
	int MAX = 100000;
	char pattern[MAX];
	fd = open("inputs/test2/pattern.txt",O_CREAT|O_APPEND|O_TRUNC,S_IRUSR|S_IWUSR);
	if(fd ==-1){
		printf("couldn't create pattern for test2\n");
		return -1;
	}
	int ch = 'a';
	int i = 0;
	for(i=0;i<MAX;i++)
		pattern[MAX] = ch + i%26; 
	write(fd,pattern,MAX);
	printf("create pattern for test2 successfully\n");
	return 0;
	

}
