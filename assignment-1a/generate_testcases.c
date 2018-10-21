#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <errno.h>
int main()
{


	extern int errno;

	int testNumber;
	for(testNumber=0;testNumber<20;testNumber++){
		char dirName[1000];
		sprintf(dirName,"inputs/test%d",testNumber);
		int status;
		status = mkdir(dirName,S_IRWXU | S_IRWXG | S_IRWXO);
		if(!status)
			printf("Directory test%d created\n",testNumber);

		long textLength;
		long patternLength = 4;// 2 4 5 10

		if(testNumber>=0 && testNumber<4){
			if(testNumber%4==0)
                                patternLength = 2;
                        if(testNumber%4==1)
                                patternLength = 4;
                        if(testNumber%4==2)
                                patternLength = 5;
                        if(testNumber%4==3)
                                patternLength = 10;
                        textLength = 100/patternLength;

		}
		if(testNumber>=4 && testNumber<8){
			if(testNumber%4==0)
                                patternLength = 20;
                        if(testNumber%4==1)
                                patternLength = 40;
                        if(testNumber%4==2)
                                patternLength = 50;
                        if(testNumber%4==3)
                                patternLength = 100;
                        textLength = 10000/patternLength;

		}
		if(testNumber>=8 && testNumber<12){
			if(testNumber%4==0)
                                patternLength = 200;
                        if(testNumber%4==1)
                                patternLength = 400;
                        if(testNumber%4==2)
                                patternLength = 500;
                        if(testNumber%4==3)
                                patternLength = 1000;
                        textLength = 1000000/patternLength;
		}
		if(testNumber>=12 && testNumber<16){
			if(testNumber%4==0)
                                patternLength = 2000;
                        if(testNumber%4==1)
                                patternLength = 4000;
                        if(testNumber%4==2)
                                patternLength = 5000;
                        if(testNumber%4==3)
                                patternLength = 10000;
                        textLength = 100000000/patternLength;

		}
		if(testNumber>=16 && testNumber<20){
			if(testNumber%4==0)
				patternLength = 20000; 
			if(testNumber%4==1)
                                patternLength = 40000; 
			if(testNumber%4==2)
                                patternLength = 50000; 
			if(testNumber%4==3)
                                patternLength = 100000;
			textLength = 10000000000/patternLength;
		}

		char textName[1000];
		sprintf(textName,"inputs/test%d/text.txt",testNumber);
		int handle_text;
		char *text = (char*)malloc(textLength * sizeof(char)); 
		handle_text = open(textName,O_CREAT|O_RDWR,0777);
		if(handle_text ==-1){
			printf("errno=%d\n",errno);
                	printf("couldn't create text for test%d\n",testNumber);
		}
		int ch = 'a';	
		int i;
		for(i=0;i<textLength-1;i++)				
			text[i] = ch;
		text[textLength-1] = 'b';
		write(handle_text,text,textLength);
		free(text);		

	 
		char patternName[1000];
		sprintf(patternName,"inputs/test%d/pattern.txt",testNumber);
		int handle_pattern;
		char pattern[patternLength];
		handle_pattern = open(patternName,O_CREAT|O_RDWR,0777);
		if(handle_pattern ==-1){
			printf("errno=%d\n",errno);
               		printf("couldn't create pattern for test%d\n",testNumber);
               	}
		     	
		pattern[patternLength-1] = 'b';
		for(i=patternLength-2;i>=0;i--)	
			pattern[i] = 'a';
		write(handle_pattern,pattern,patternLength);
		if(handle_text!=-1 && handle_pattern!=-1)
			printf("create text and pattern for test%d successfully\n",testNumber);		
	}

	return 0;

}
