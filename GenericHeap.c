#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 100000

typedef struct HEAP heap;
struct HEAP 
{
    int size;
    int items[MAX_SIZE];
};

heap* create_h();

void enqueue(heap *heap, int element);

void build_heap(heap *heap);

void print_heap(heap* heap);

int get_parent_i(heap* heap,int i);

int get_left_i(heap* heap,int i);

int get_right_i(heap* heap,int i);

void heapfy(heap* heap,int i);

void heapsort(heap* heap);

int dequeue(heap* heap);

int main()
{
    heap* heap = create_h();
    int num[MAX_SIZE],cont=0,i=1;
    int mysize;
    scanf("%d",&mysize);
    while(i <= mysize)
    {
        scanf("%d",&num[i]);
        enqueue(heap,num[i]);
        cont++;
        i++;
    }
    cont = heap->size;
    build_heap(heap);
    heapsort(heap);
    heap->size = cont;
    print_heap(heap);
    int eu = dequeue(heap);
    printf("%d!!!!\n",eu);
    return 0;
}
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

void enqueue(heap *heap,int element)
{
    heap->items[++heap->size] = element;
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
        printf("%d ",heap->items[i]);
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
    int smallest,left_index,right_index,aux;
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
        heapfy(heap,smallest);
    }
}

void heapsort(heap* heap)
{
    int i,aux=0;
    for(i = heap->size;i >= 1;i--)
    {
        aux = heap->items[i];
        heap->items[i] = heap->items[1];
        heap->items[1] = aux;
        heap->size--;
        heapfy(heap,1);
    }
}
