#include <stdio.h>
#include <stdlib.h>

#define Q_ASSERT(expr)  do {if(NULL == expr) return -1;} while(0);
#define Q_MALLOC(size)  malloc(size)
#define Q_FREE(ptr)  do {if(ptr) free(ptr);} while(0);
//#define Q_SIZE(q)  if(q != NULL) return q->size;
typedef struct node
{
    struct node *prev;
    struct node *next;
}NODE;

typedef struct
{
    NODE *head;
    NODE *tail;
    int size;
}QUEUE;

int pop(QUEUE *q, NODE* node)
{
    NODE *p_next = NULL;
    Q_ASSERT(q);
    
    //头节点后的第一个节点非空
    if (q->head->next)
    {
        p_next = q->head->next;  
        q->head->next = p_next->next;
        Q_FREE(p_next);
        q->size--;
        return 0;
    }
    else 
    {
        return -1;
    }
}


int push(QUEUE *q, NODE* node)
{
    Q_ASSERT(q);   
    Q_ASSERT(node);  
    
    q->tail->next = node;
    q->tail = node;
    q->size++;
    return 0;
}


int queue_init(QUEUE *q)
{
    Q_ASSERT(q);
    q->head = q->tail = (NODE*)Q_MALLOC(sizeof(NODE));      //创建一个头结点
    if (q->tail)
    {
        q->tail->next = NULL;
        q->size = 0;
    }
    else 
    {
        return -1;
    }
}

int queue_free(QUEUE *q)
{
    NODE* p_head= NULL;
    NODE* p_next= NULL;
    Q_ASSERT(q);

    p_head = q->head;  
    while (p_head)
    {
        p_next = q->head->next;
        Q_FREE(p_head);
        p_head = p_next;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}


int main()
{

    QUEUE q;
    queue_init(&q);
    NODE* node1 = (NODE*)Q_MALLOC(sizeof(NODE));
    NODE* node2 = (NODE*)Q_MALLOC(sizeof(NODE));
    push(&q, node1);
    push(&q, node2);
    pop(&q, node2);
    printf("q szie %d\n", q.size);
    return 0;

}














