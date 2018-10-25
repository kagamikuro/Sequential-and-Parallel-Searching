#include<stdio.h>
#include<omp.h>

int main(){

	int sum = 0;
	int n;
	#pragma omp parallel for num_threads(8)
		for(n=1;n<=100;n++)
			sum += n;

	printf("%d\n",sum);

}
