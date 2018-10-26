
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>




////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

char *textData;
int textLength;

char *patternData;
int patternLength;

clock_t c0, c1;
time_t t0, t1;

void outOfMemory()
{
	fprintf (stderr, "Out of memory\n");
	exit (0);
}

void readFromFile (FILE *f, char **data, int *length)
{
	int ch;
	int allocatedLength;
	char *result;
	int resultLength = 0;

	allocatedLength = 0;
	result = NULL;

	

	ch = fgetc (f);
	while (ch >= 0)
	{
		resultLength++;
		if (resultLength > allocatedLength)
		{
			allocatedLength += 10000;
			result = (char *) realloc (result, sizeof(char)*allocatedLength);
			if (result == NULL)
				outOfMemory();
		}
		result[resultLength-1] = ch;
		ch = fgetc(f);
	}
	*data = result;
	*length = resultLength;
}

int readData (int testNumber)
{
	FILE *f;
	char fileName[1000];
#ifdef DOS
        sprintf (fileName, "inputs\\test%d\\text.txt", testNumber);
#else
	sprintf (fileName, "inputs/test%d/text.txt", testNumber);
#endif
	f = fopen (fileName, "r");
	if (f == NULL)
		return 0;
	readFromFile (f, &textData, &textLength);
	fclose (f);
#ifdef DOS
        sprintf (fileName, "inputs\\test%d\\pattern.txt", testNumber);
#else
	sprintf (fileName, "inputs/test%d/pattern.txt", testNumber);
#endif
	f = fopen (fileName, "r");
	if (f == NULL)
		return 0;
	readFromFile (f, &patternData, &patternLength);
	fclose (f);

	printf ("Read test number %d\n", testNumber);

	return 1;

}



int hostMatch(long *comparisons,int threads)
{
	int i,j,k, lastI;
	
	i=0;
	j=0;
	k=0;
	lastI = textLength-patternLength;
        *comparisons=0;
	long temp_comparisons=0;
	int position = -1;
	#pragma omp parallel for num_threads(threads) private(k,j) shared(i,temp_comparisons)  	
		for(i=0;i<=lastI;i++){
			if(position != -1)// pattern has been found
				continue;
			
			
			k=i;			
			j=0;
			if(textData[k] != patternData[j]){
				temp_comparisons++;
				continue;
			}
				
			while(textData[k] == patternData[j] && j<patternLength &&k<textLength ){
				
					k++;
					j++;
					temp_comparisons++;
				
				if(k<textLength && j<patternLength && textData[k] != patternData[j])//for next comparison if text and pattern doesn't much the loop quit but comparison need add 1
					temp_comparisons++;
				
			}
			if(j == patternLength){
				position = i;
				
			}
			

			                        
			
							
			
		}

	*comparisons = temp_comparisons;		
	return position;
}
void processData(int threads)
{
	unsigned int result;
        long comparisons;

	printf ("Text length = %d\n", textLength);
	printf ("Pattern length = %d\n", patternLength);

	result = hostMatch(&comparisons,threads);
	if (result == -1)
		printf ("Pattern not found\n");
	else
		printf ("Pattern found at position %d\n", result);
        printf ("# comparisons = %ld\n", comparisons);

}

int main(int argc, char **argv)
{
	
	int threads;

	
	readData (1);
	for(threads=1;threads<=64;threads=threads*2){
		printf("using %d threads:\n",threads);	
		c0 = clock(); t0 = time(NULL);	
   		processData(threads);
		c1 = clock(); t1 = time(NULL);
        	printf("using %d threads: on test0 elapsed wall clock time = %ld\n", threads, (long) (t1 - t0));
        	printf("using %d threads: elapsed CPU time = %f\n\n", threads, (float) (c1 - c0)/CLOCKS_PER_SEC); 
	}


}
