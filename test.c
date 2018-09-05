#include <stdio.h>
#include <stdlib.h>
#define MAX 3
int main()
{
	unsigned char a;
	//int a, i=0;
	FILE *fp;
	char filename[100];
	printf("Digite o nome do seu arquivo:\n");
	scanf(" %[^\n]s", filename);
	fp = fopen(filename, "r");
	while(!feof(fp))
	{
		a = fgetc(fp);
		//test[0] = a;
		//break;
		printf("(%x)", a);
	}
	fclose(fp);
	//printf("%s\n", test);

	return 0;
}