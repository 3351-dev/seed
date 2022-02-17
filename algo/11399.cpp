#include <iostream>
#include <cstdio>

int main()
{
	int N;
	int temp;
	int sum=0;
	scanf("%d",&N);

	int P[N];
	for(int i=0;i<N;i++){
		scanf("%d", &P[i]);
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N-1;j++){
			if(P[j]>P[j+1]){
				temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
/*
	printf("res : ");
	for(int i=0;i<N;i++){
		printf("%d ", P[i]);
	}
	printf("\n");
*/

	for(int i=1;i<N;i++){
		P[i] += P[i-1];
	}

	for(int i=0;i<N;i++){
		sum += P[i];
	}
	printf("%d",sum);

}


