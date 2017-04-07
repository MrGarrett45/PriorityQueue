#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    int priority;
    int ticketNum;
    char *info;
}node;
 
typedef struct {
    node *nodes;
    int length;
    int size;
}heap;

int tNumGlobal = 1;

void bubbleUp(heap *h, int i, int x, int priority)
{
  while (i > 1 && h->nodes[x].priority > priority) 
    {
        h->nodes[i] = h->nodes[x];
        i = x;
        x = x / 2;
    }
}

void kiosk_submit_order (heap *h, int priority, char *info) {
    
    if (h->length + 1 >= h->size) {
        if(h->size)
        {
          h->size = h->size * 2;
        }
        else
        {
          h->size = 4;
        }
      
        h->nodes = (node *)realloc(h->nodes, h->size * sizeof(node));
    }
    
    int i = h->length + 1;
    int x = i / 2;
    
    bubbleUp(h, i, x, priority);
      
    h->nodes[i].priority = priority;
    h->nodes[i].info = info;
    h->length++;
    h->nodes[i].ticketNum = tNumGlobal;
    tNumGlobal++;
}

void heapify(heap *h, int i) {
  int k, x;
  while (1) 
    {
        k = i;
        x = 2 * i;
        
        if (k == i) 
        {
            break;
        }
        if (h->nodes[x].priority < h->nodes[k].priority && x <= h->length) 
        {
            k = x;
        }
        if (h->nodes[x + 1].priority < h->nodes[k].priority && x + 1 <= h->length) 
        {
            k = x;
            k++;
        }
    
        h->nodes[i] = h->nodes[k];
        i = k;
    }
}

char *kiosk_complete_next (heap *h) {
    int i = 1;
    if (!h->length) 
    {
        return NULL;
    }
  
    char *info = h->nodes[1].info;
    h->nodes[1] = h->nodes[h->length];
    
    h->length--;
    heapify(h, 1);
    h->nodes[i] = h->nodes[h->length + 1];
    
    return info;
}

int kiosk_peek(heap *h){
  if(h->length == 0)
  {
    return -1;
  }
  else
  {
    return h->nodes[1].ticketNum;
  }
}

int kiosk_queue_size(heap *h) {
  return h->length;
}
 
int main () {
    heap *h = (heap *)malloc(sizeof(heap));
  
    kiosk_submit_order(h, 3, "Richard Nixon");
    kiosk_submit_order(h, 4, "Steve Aoki");
    kiosk_submit_order(h, 5, "Bob Ross");
    kiosk_submit_order(h, 1, "Arnold Schwartz");
    kiosk_submit_order(h, 2, "Garrett McLaughlin");
    kiosk_submit_order(h, 6, "James McLaughlin");
    
    int test = kiosk_peek(h);
    printf("Peek: %d\n", test);
  
    int test2 = kiosk_queue_size(h);
    printf("Size: %d\n", test2);
  
    int i;
    for (i = 0; i < 6; i++) {
        printf("%s\n", kiosk_complete_next(h));
    }
    return 0;
}
 
