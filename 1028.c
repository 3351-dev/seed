#include <stdio.h>
#include <stdlib.h>


//hello?
// Five

void func1();
void func2(int num);
void func3(int num);

int main(int argc, char **argv)
{
	int select, i, cnt, num;

	printf("Input select [1~4] : ");
	scanf("%d", &select);
	
	switch(select){
		case 1:
			func1();
			break;
		case 2:
			printf("Input Num : ");
			scanf("%d", &i);
			func2(i);
			break;
		case 3:
			if(argc!=2){
				printf("argc err\n");
				break;
			}
			i = atoi(argv[1]);
			func3(i);
			break;
		case 4:
			cnt=0;

			while(1){
				if(argv[cnt]==NULL)
					break;
				cnt++;
			}
//			printf("%d\n", cnt);

			for(int i=1; i<cnt; i++){
				for(int j=1; j<10; j++){
					num=atoi(argv[i]);
					printf("%s x %d = %d\n",argv[i],j,num*j);
				}
				printf("- - - - -\n");
			}
			printf("sol 4\n");		
			break;
		default :
			printf("Error Num. Retry...\n");
			break;
	}

}

void func1()
{
	for(int i=2;i<10;i++){
		for(int j=1;j<10;j++){
			printf("%d x %d = %d\n", i,j,i*j);
		}
		printf("- - - - - - \n");
	}
	printf("1 sol\n");
}


void func2(int num)
{
	for(int i=1;i<10;i++){
		printf("%d x %d = %d\n", num, i, num*i);
	}
	printf("2 sol\n");
}

void func3(int num)
{
	for(int i=1;i<10;i++){
		printf("%d x %d = %d\n", num, i, num*i);
	}
	printf("3 sol\n");
}
