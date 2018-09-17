#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
//#include "hash_table.h"
#define MAX 100000
#define MAX_SIZE 10000

typedef struct HEAP heap;
typedef struct hash_table hash_table;
typedef struct ELEMENT element;
typedef struct TREE tree;

struct TREE
{
	unsigned char data;
	unsigned int freq;
	tree *left;
	tree *right;
};

struct HEAP 
{
	int begin;
    int size;// tamanho
    tree *tree[257];
};

struct ELEMENT
{
	unsigned char key;//elementos do arquivo lido
	unsigned int freq;//valores de frequencias
};

struct hash_table
{
	element *table[257];//array de ponteiros para cada estrutura element
};

//heap functions
heap* create_h();//cria a heap

void enqueue(heap *heap, int element,unsigned char data);//coloca no array as frequencias e seus respectivos elementos

void build_heap(heap *heap);//constroi a heap

void print_heap(heap* heap);//imprime a heap

int get_parent_i(heap* heap,int i);//obtém o indice do pai

int get_left_i(heap* heap,int i);//obtém o indice da esquerda

int get_right_i(heap* heap,int i);//obtém o indice da direita

void heapfy(heap* heap,int i);//da min heapify para que a cabeça do array seja a menor frequencia sempre

void heapsort(heap* heap);//ordena as frequencias

tree* dequeuehp(heap* heap);//acho q não vamos usar essa mas ela pega o elemento sempre do final do jeito q tá,o seja,dps que dá o heapsort,ela sempre pega o menor

void hashtoheap(heap *heap,hash_table *hash);//passa os elementos que estão na hash para a heap,(ou ao menos tenta)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// hash functions ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

unsigned int create_index(unsigned char key)
{
	unsigned int convert = key;
	return convert % 257;
}

void put(hash_table *ht, unsigned char key)
{
	unsigned int  index;
	index = create_index(key); // cria chave baseada no caracter
	if(ht->table[index] != NULL) // caso esse espaço na hash seja diferente de nulo 
	{																													 // a frequencia é aumentada
		ht->table[index]->freq++;
		return;
	}
	else if(ht->table[index]==NULL) // se for igual a nulo ele cria um novo nó
	{
		//index = create_index(index+1); // falta
		element *new_element = (element*) malloc(sizeof(element));
		new_element->key = key;
		new_element->freq = 1;
		ht->table[index] = new_element;
	}
}
void putt(hash_table *ht,unsigned char key,unsigned char comp)
{
	unsigned int  index;
	index = create_index(key); // cria chave baseada no caracter

		//index = create_index(index+1); // falta
		element *new_element = (element*) malloc(sizeof(element));
		new_element->key = key;
		new_element->freq = comp;
		ht->table[index] = new_element;
	
}
int get(hash_table *ht,unsigned char key)
{
	unsigned char  index;
	index = create_index(key);
	while(ht->table[index]!=NULL)
	{
		if(ht->table[index]->key==key)
		{
			return ht->table[index]->freq;
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
		if(ht->table[index]!=NULL) printf("%x = %d\n", ht->table[index]->key, ht->table[index]->freq);
	}
	printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// tree fuctions //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tree* create_empty_tree(int freq, int data)
{
	tree *new_tree = (tree*) malloc(sizeof(tree));
	new_tree->freq = freq;
	new_tree->data = data;
	new_tree->right = NULL;
	new_tree->left = NULL;
	
	return new_tree;
}
tree* create_huff_tree(tree *left, tree *right)
{
	tree *new_tree = (tree*) malloc(sizeof(tree));
	new_tree->left = left;
	new_tree->right = right;
	new_tree->freq = left->freq + right->freq;
	new_tree->data = 19;
	return new_tree;
}
int is_empty(tree *htf)
{
	if(htf == NULL)return 1;
	else return 0;
}
void print_in_order(tree *hft)
{
	
	if(!is_empty(hft))
	{
		if(hft->data !=19)printf("[%c]", hft->data);
		else printf("*");
		print_in_order(hft->left);
		print_in_order(hft->right);
	}
	
}

tree* build_hufftree(tree *htf, heap *heap)
{
	tree *aux = NULL;
	tree *aux2 = NULL;
	int truesize;
	while(heap->begin < heap->size)
    {

  		aux = NULL;
  		aux2 = NULL;

       
        aux = dequeuehp(heap);
        truesize = heap->size;
        heapsort(heap);
        heap->size = truesize;
        
        aux2 = dequeuehp(heap);
        truesize = heap->size;
        heapsort(heap);
        heap->size = truesize;
		
		if(aux2->data == 19 && aux->data != 19)
		{
			htf = create_huff_tree(aux2, aux);
		}
		else
		{
			htf = create_huff_tree(aux, aux2);
		}
        //htf = create_huff_tree(left, right);
      //  printf("raiz%d\n", htf->freq);
		heap->tree[++heap->size] = htf;
      
        print_in_order(htf); 
        printf("\n");
        truesize = heap->size;
        heapsort(heap);
        heap->size = truesize;
    }
   
    return htf;
}
unsigned char set_bit(unsigned char c, unsigned int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}
void treetohash(tree *htf, hash_table *ht, unsigned char comp)
{
	if(htf == NULL)
	{
		return;
	}
	else if(htf->data != 19)
	{
		putt(ht,htf->data,comp);
		comp ^= 1;// comp--
		comp = comp<<1;
		return;
	}
	else
	{
		
		comp = comp>>1;
		treetohash(htf->left,ht,comp);
		
		comp = comp<<1;
		comp = comp>>1;
		comp = set_bit(comp,1);
		treetohash(htf->right,ht,comp);
		comp ^= 1;
		comp = comp<<1;
	}
	return;

}














































int main()
{
	unsigned char value;
	hash_table *hash = create_hash_table();
	heap *heap = create_h();
	tree *hufftree = NULL;
	int truesize;
    //tree* mytree = create_empty_tree();
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
		if(value != 0xff && value != 0xa && value != 0x9) put(hash, value); // insere o elemento na hash
	}
	fclose(file_in);
	print_hash(hash);
  // transfere a hash para a heap
  	hashtoheap(heap,hash); // envia os elementos da hash para a heap
  
  // ordena a heap
  	truesize = heap->size;
	heapsort(heap); // ordena a heap
	heap->size = truesize;
  // cria a arvore
  hufftree = build_hufftree(hufftree, heap);
  //imprimindo
 // print_in_order(hufftree);
  //
  hash= create_hash_table();
  treetohash(hufftree,hash,0);
  //
  print_hash(hash);
  return 0;
}




































void hashtoheap(heap *heap,hash_table *hash)
{
	int i;
	//print_hash(hash);
	for(i = 0;i < 257;i++)
	{
       if(hash->table[i]!=NULL) 
       {
		    enqueue(heap,hash->table[i]->freq,hash->table[i]->key);//enfileira na heap primeiro a frequencia depois o valor
       }
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// heap functions ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
heap* create_h()
{
    heap* h = (heap*) malloc(sizeof(heap));
    h->begin = 1;
    h->size = 0;
    return h;
}

tree* dequeuehp(heap *heap)
{
        tree *item = heap->tree[heap->size];
        heap->size--;
        heapfy(heap,heap->begin);
        return item;
    
}

void enqueue(heap *heap,int freq,unsigned char data)
{
	tree *new_tree = create_empty_tree(freq, data);
	heap->tree[++heap->size] = new_tree;
}

void build_heap(heap *heap)
{
    int i;
    for(i = (heap->size)/2;i;i--)
    {
        heapfy(heap,i);
    }
}
/*
void print_heap(heap* heap)
{
    int i;
    for(i = 1;i <= heap->size;++i)
    {
        printf("%x,%d#\n",heap->data[i],heap->freq[i]);
    }
    printf("\n");
}
*/
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
    tree *auxz = NULL;
  	left_index = get_left_i(heap,i); // encontra o filho esquerdo
    right_index = get_right_i(heap,i); // encontra o filho direito
    
  	if((left_index <= heap->size) &&  (heap->tree[left_index]->freq < heap->tree[i]->freq)) // Verifica se o filho esquerdo é valdio
    {																																						// e se sua frequencia é menor que a  
        smallest = left_index;																									// do pai
    }
    else
    {
        smallest = i;                                                         // assume que o menor é o pai
    }
    if((right_index <= heap->size) && (heap->tree[right_index]->freq < heap->tree[smallest]->freq)) // verifica se o direito é menor 
    {																																										// que o menor
        smallest = right_index;
    }
    if((heap->tree[i]->freq != heap->tree[smallest]->freq))                               // se a frequencia do indice 
    {																																					// não for a menor ele realiza a troca
        
    	auxz = heap->tree[i];
        heap->tree[i] = heap->tree[smallest];
        heap->tree[smallest] = auxz;
        heapfy(heap,smallest);
    }
}
void heapsort(heap* heap)
{
	tree *hufftree = NULL;
	tree *left = NULL;
	tree *right = NULL;
	tree *aux = NULL;
	build_heap(heap); // constroi a heap
     
  	int current,last,current2;
    for(current = heap->size;current >= heap->begin;current--)
    {
     //   printf("%d\n", heap->tree[heap->begin]->freq);
        aux = heap->tree[current];
        heap->tree[current] = heap->tree[heap->begin];
        heap->tree[heap->begin] = aux;
        heap->size--;
        heapfy(heap,heap->begin);
    } 
 
}	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////