#include <stdio.h>
#include <stdlib.h>
typedef struct hash_table hash_table;
typedef struct element element;

/*	estrutura element
	essa estrutura armazenará a key(byte) e o counter(frequência)
	que será armazenda posteriormente no array de ponteiros da estrutura hash_table

*/

struct element
{
	unsigned char key; //byte representado em hexadecimal
	unsigned char counter; // frequencia do byte 
};
/* estrutura hash_table
	contém um array de ponteiros com 256 posições que é a quantidade de números hexadecimais
	esse array de ponteiros é do tipo element

*/
struct hash_table
{
	element *table[256];	
};


/*	função create_hash_table
	 aloca memórica e o endereço da estrutura hash_table para um novo ponteiro
	aponta todos os ponteiros do array da estrutura hash_table para nulo
*/

hash_table* create_hash_table()
{
	int i;
	hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
	for(i=0;i<257;i++)
	{
		new_hash_table->table[i] = NULL;
	}
	return new_hash_table;
}

/*	função create_index
	cria o indice que armazenará a key(byte) e a frequência desse byte   
*/
unsigned char create_index(unsigned char key)
{
	return key % 257;
}

/* 	função put
	recebe como parâmetros a hash e a key(byte)
	é criado o indice que será a posição desse byte no array de ponteiro da estrutura hash_table que aponta para estrutura element
	caso a já tenha uma key(byte) armazenado em alguma posição do array da hash, a frequência(counter) será incrementada
	caso contrário, será alocada memória e o mesmo endereço da estrtura element para um ponteiro
	esse ponteiro do tipo element vai receber a key(byte) e a frequência(counter) dessa key receberá o valor um
*/
void put(hash_table *ht, unsigned char key)
{
	unsigned char  index;
	index = create_index(key);
	while(ht->table[index]!=NULL)
	{
		if(ht->table[index]->key==key)
		{
			ht->table[index]->counter++;
			break;
		}
 		index = create_index(index+1);
	}
	if(ht->table[index]==NULL)
	{
		element *new_element = (element*) malloc(sizeof(element));
		new_element->key = key;
		new_element->counter = 1;
		ht->table[index] = new_element;
	}
}
/* função get
	recebe como parâmetros a hash e a key(byte)
	é criado o indice com a key(byte) passada, esse indice será a posição dessa key(byte) na hash
	se a key(byte) que está armazenada na hash for igual a key passada no parâmetro da função
	a função retornará a frequência dessa key(byte)
*/
int get(hash_table *ht,unsigned char key)
{
	unsigned char  index;
	index = create_index(key);
	while(ht->table[index]!=NULL)
	{
		if(ht->table[index]->key==key)
		{
			return ht->table[index]->counter;
		}
		index = create_index(index+1);
	}
	return 0;
}
/* função remove_ht
	recebe como parâmetros a hash e a key(byte)
	é criado o indice com a key(byte) passada, esse indice será a posição dessa key(byte) na hash
	se a key(byte) que está armazenada na hash for igual a key passada no parâmetro da função
	o endereço de memória da posição indice na hash será limpado
	e a chave passará a ser -1  
*/
void remove_ht(hash_table *ht, unsigned char key)
{
	unsigned char index;
	index = create_index(key);
	while(ht->table[index]!=NULL)
	{
		if(ht->table[index]->key==key)
		{
			free(ht->table[index]);
			ht->table[index]->key = -1;
		}
		index = create_index(index+1);
	}
}
/* função print_hs
	imprime a key(byte) no determinado indice da hash e a frequência(counter) dessa key(byte)

*/
void print_hs(hash_table *ht)
{
	int index;
	for(index=0;index<257;index++)
	{
		if(ht->table[index]!=NULL)
		printf("%x = %d\n", ht->table[index]->key, ht->table[index]->counter);
	}
	printf("\n");
}
