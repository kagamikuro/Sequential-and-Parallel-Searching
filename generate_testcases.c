#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	int testNumber;
	for(testNumber=0;testNumber<20;testNumber++){
		char dirName[1000];
		sprintf(dirName,"inputs/test%d",testNumber);
		int status;
		status = mkdir(dirName,S_IRWXU | S_IRWXG | S_IRWXO);
		if(!status)
			printf("Directory test%d created\n",testNumber);

		long textLength;
		if(testNumber>=0 && testNumber<4)
			textLength = 100;
		if(testNumber>=4 && testNumber<8)
                        textLength = 10000;
		if(testNumber>=8 && testNumber<12)
                        textLength = 1000000;
		if(testNumber>=12 && testNumber<16)
                        textLength = 100000000;
		if(testNumber>=16 && testNumber<20)
                        textLength = 10000000000;

		char textName[1000];
		sprintf(textName,"inputs/test%d/text.txt",testNumber);
		int handle_text;
		char text[textLength];
		handle_text = open(textName,O_CREAT|O_RDWR);
		if(handle_text ==-1)
                	printf("couldn't create tsxt for test%d\n",testNumber);
		int ch = 'a';	
		int i;
		for(i=0;i<textLength-1;i++)				
			text[i] = ch;
		text[textLength-1] = 'b';
		write(handle_text,text,textLength);	
		
	}	





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
