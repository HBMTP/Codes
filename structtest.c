#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
//#include "hash_table.h"
#define MAX 100000
#define MAX_SIZE 100000

typedef struct HEAP heap;
typedef struct hash_table hash_table;
typedef struct element element;

struct HEAP 
{
    int size;// tamanho
    unsigned char data[MAX_SIZE];//os elementos recebidos da hash
    int items[MAX_SIZE];//as frequencias
};

struct element
{
	unsigned char key;//elementos do arquivo lido
	unsigned char value;//valores de frequencias
};

struct hash_table
{
	element *table[257];//array de ponteiros para cada estrutura element
};


heap* create_h();//cria a heap

void enqueue(heap *heap, int element,unsigned char data);//coloca no array as frequencias e seus respectivos elementos

void build_heap(heap *heap);//constroi a heap

void print_heap(heap* heap);//imprime a heap

int get_parent_i(heap* heap,int i);//obtém o indice do pai

int get_left_i(heap* heap,int i);//obtém o indice da esquerda

int get_right_i(heap* heap,int i);//obtém o indice da direita

void heapfy(heap* heap,int i);//da min heapify para que a cabeça do array seja a menor frequencia sempre

void heapsort(heap* heap);//ordena as frequencias

int dequeue(heap* heap);//acho q não vamos usar essa mas ela pega o elemento sempre do final do jeito q tá,o seja,dps que dá o heapsort,ela sempre pega o menor

void hashtoheap(heap *heap,hash_table *hash);//passa os elementos que estão na hash para a heap,(ou ao menos tenta)

hash_table* create_hash_table()
{
	int i;
	hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
	for(i = 0;i < 257; i++)
	{
		new_hash_table->table[i] = NULL;
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

void print_hash(hash_table *ht)
{
	int index;
	for(index=0;index < 257;index++)
	{
		if(ht->table[index]!=NULL) printf("%x = %d\n", ht->table[index]->key, ht->table[index]->value);
	}
	printf("\n");
}

int main()
{
	unsigned char value;
	hash_table *hash = create_hash_table();
	heap *heap = create_h();
	FILE *file_in;
	FILE *file_out;
	char filename[MAX], letter;
	printf("Digite o nome do seu arquivo:\n");
	scanf(" %[^\n]s", filename);
	file_in = fopen(filename, "r");
	file_out = fopen("out.txt", "w+");
	while(!feof(file_in))
	{
		value = fgetc(file_in);
		//printf("%x = ", value);
		put(hash, value);
		//printf("%x\n", create_index(value));
		fprintf(file_out,"(%x)", value);
	}
	fclose(file_in);
	hashtoheap(heap,hash);
	int constsize = heap->size;
	heapsort(heap);
	heap->size= constsize;
	print_heap(heap);
	return 0;
}

void hashtoheap(heap *heap,hash_table *hash)
{
	int i;
	print_hash(hash);
	for(i = 0;i < 257;i++)
	{
       if(hash->table[i]!=NULL) 
       {
		    enqueue(heap,hash->table[i]->value,hash->table[i]->key);
       }
	}
}

//heap begin
heap* create_h()
{
    heap* h = (heap*) malloc(sizeof(heap));
    h->size = 0;
    return h;
}

int dequeue(heap *heap)
{
    if (heap->size == 0) 
    {
        printf("Heap underflow");
        return -1;
    } 
    else{
        int item = heap->items[heap->size];
        heap->size--;
        heapfy(heap,1);
        return item;
    }
}

void enqueue(heap *heap,int element,unsigned char data)
{
    heap->items[++heap->size] = element;
    heap->data[heap->size] = data;
}
void build_heap(heap *heap)
{
    int i;
    for(i = (heap->size)/2;i;i--)
    {
        heapfy(heap,i);
    }
}
void print_heap(heap* heap)
{
    int i;
    for(i = 1;i <= heap->size;++i)
    {
        printf("%x,%d#\n",heap->data[i],heap->items[i]);
    }
    printf("\n");
}
int get_parent_i(heap* heap,int i)
{
    int result = i/2;
    return result;
}
int get_left_i(heap* heap,int i)
{
    int result = 2*i;
    return result;
}
int get_right_i(heap* heap,int i)
{
    int result = 2*i + 1;
    return result;
}
void heapfy(heap* heap,int i)
{
    int smallest,left_index,right_index,aux,aux2;
    left_index = get_left_i(heap,i);
    right_index = get_right_i(heap,i);
    if((left_index <= heap->size) &&  (heap->items[left_index] < heap->items[i]))
    {
        smallest = left_index;
    }
    else
    {
        smallest = i;
    }
    if((right_index <= heap->size) && (heap->items[right_index] < heap->items[smallest]))
    {
        smallest = right_index;
    }
    if((heap->items[i] != heap->items[smallest]))
    {
        aux = heap->items[i];
        heap->items[i] = heap->items[smallest];
        heap->items[smallest] = aux;
        aux2 = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = aux2;
        heapfy(heap,smallest);
    }
}

void heapsort(heap* heap)
{
	build_heap(heap);
	print_heap(heap);
    int i,aux=0,aux2=0;
    for(i = heap->size;i >= 1;i--)
    {
    	printf("The element I want: %d\n",heap->items[1]);
        aux = heap->items[i];
        heap->items[i] = heap->items[1];
        heap->items[1] = aux;
        aux2 = heap->data[i];
        heap->data[i] = heap->data[1];
        heap->data[1] = aux2;
        heap->size--;
        heapfy(heap,1);
    }
}	