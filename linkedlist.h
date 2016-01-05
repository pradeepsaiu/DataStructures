struct Data
{
        int value;
};

struct Node
{
        struct Data obj;
        struct Node * next;
        struct Node * prev;
};

struct  List
{
        struct Node *head;
        struct Node *tail;
};

struct Stack
{
        struct List *stack;
};

struct Queue
{
        struct List *queue;
};

