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
	int handle;
	int MAX = 100000;
	char pattern[MAX];
	handle = open("inputs/test2/pattern.txt",O_CREAT|O_RDWR);
	if(handle ==-1){
		printf("couldn't create pattern for test2\n");
		return -1;
	}
	int ch = 'a';
	int i = 0;
	for(i=0;i<MAX;i++){
		pattern[i] = ch + i%26; 
	}
	write(handle,pattern,MAX);
	printf("create pattern for test2 successfully\n");
	return 0;
	

}
