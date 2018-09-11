#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 100000

typedef struct HEAP heap;
struct HEAP 
{
    int size;
    void *items[MAX_SIZE];
};

heap* create_h();

void enqueue(heap *heap,void *element);

void build_heap(heap *heap);

void print_heap(heap* heap);

int get_parent_i(heap* heap,int i);

int get_left_i(heap* heap,int i);

int get_right_i(heap* heap,int i);

void heapfy(heap* heap,int i);

void heapsort(heap* heap);

void* dequeue(heap* heap);

void swap(void* element1, void* element2);

int main()
{
    heap* heap = create_h();
    int num[MAX_SIZE],cont=0,i=1;
    int mysize;
    scanf("%d",&mysize);
    while(i <= mysize)
    {
        scanf("%d",&num[i]);
        enqueue(heap,&num[i]);
        cont++;
        i++;
    }
    cont = heap->size;
    build_heap(heap);
    heapsort(heap);
    heap->size = cont;
    print_heap(heap);
    return 0;
}

heap* create_h()
{
    heap* h = (heap*) malloc(sizeof(heap));
    h->size = 0; 
    return h;
}

void swap(void* element1, void* element2)
{
    printf("%d \n",*((int*)(element1)));
    printf("%d \n",*((int*)(element2)));
    void* aux = NULL;
    aux = element1;
    element1 = element2;
    element2 = aux;
    printf("%d!! \n",*((int*)(element1)));
    printf("%d! \n",*((int*)(element2)));
}

void* dequeue(heap *heap)
{
    if (heap->size == 0) 
    {
        printf("Heap underflow");
        //return -1;
    } 
    else{
        void* item = heap->items[heap->size];
        heap->size--;
        heapfy(heap,1);
        return item;
    }
}

void enqueue(heap *heap,void *element)
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
        printf("%d ",*((int*)(heap->items[i])));
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
    int smallest,left_index,right_index;
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
        // printf("%d#\n",*((int*)(heap->items[i])));
        // printf("%d$\n",*((int*)(heap->items[smallest])));
        swap(heap->items[i],heap->items[smallest]);
        heapfy(heap,smallest);
    }
}

void heapsort(heap* heap)
{
    int i;
    for(i = heap->size;i >= 1;i--)
    {
        printf("%d\n",i);
        printf("the element I want: %d\n",*((int*)(heap->items[1])));
        swap(heap->items[i],heap->items[1]);
        heap->size--;
        heapfy(heap,1);
    }
}
