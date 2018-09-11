#include <stdio.h>
#include <stdlib.h>
typedef struct hash_table hash_table;
typedef struct element element;

struct element
{
	unsigned char key;
	unsigned char value;
};

struct hash_table
{
	element *table[256];
};


hash_table* create_hash_table()
{
	unsigned char i;
	hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
	for(i=0;i<256;i++)
	{
		new_hash_table->table[i] = NULL;
		new_hash_table->table[i]->value=0;
	}
	return new_hash_table;
}

int create_index(unsigned char key)
{
	return key % 257;
}

void put(hash_table *ht, unsigned char key)
{
	unsigned char  index;
	index = create_index(key);
	while(ht->table[index]!=NULL)
	{
		if(ht->table[index]->key==key)
		{
			ht->table[index]->value++;
			break;
		}
 		index = create_index(index+1);
	}
	if(ht->table[index]==NULL)
	{
		element *new_element = (element*) malloc(sizeof(element));
		new_element->key = key;
		new_element->value = 1;
		ht->table[index] = new_element;
	}
}

int get(hash_table *ht,unsigned char key)
{
	unsigned char  index;
	index = create_index(key);
	while(ht->table[index]!=NULL)
	{
		if(ht->table[index]->key==key)
		{
			return ht->table[index]->value;
		}
		index = create_index(index+1);
	}
	return 0;
}

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
