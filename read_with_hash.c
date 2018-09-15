#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#define MAX 100

int main()
{
	unsigned char value;
	hash_table *hash = create_hash_table();
	FILE *file_in;
	FILE *file_out;
	char filename[MAX];
	printf("Digite o nome do seu arquivo:\n");
	scanf(" %[^\n]s", filename);
	file_in = fopen(filename, "r");
	file_out = fopen("out.txt", "w+");
	while(!feof(file_in))
	{
		value = fgetc(file_in);
		put(hash, value);
	}
	fclose(file_in);
	print_hs(hash);

	return 0;
}

