#ifndef lab7_h
#define lab7_h
struct Data
{
        int val;
};

struct Node
{
        struct Data obj;
        struct Node *left;
        struct Node *right;
        struct Node *parent;
};

struct Tree
{
        struct Node *root;
};

struct Tree * createTree()
{
        struct Tree * t1 = malloc(sizeof(struct Tree));
        t1->root = NULL;
        return t1;
}

struct Node * createNode(struct Data value)
{

        struct Node * node1 = malloc(sizeof(struct Node));
        node1->obj = value;
        node1->left = NULL;
        node1->right = NULL;
        node1->parent =NULL;

}

void insertNode(struct Node *, struct Data );
void insert(struct Tree * , struct Data  );
struct Node * searchNode(struct Node ,struct Data  );
struct Node * search(struct Tree , struct Data );
void inorder(struct Node );
void removenode(struct Tree * ,struct Data );
void postorder_del(struct Tree * ,struct Node );
void removeLeaf(struct Tree * ,struct Node );
void shortCircuit(struct Tree * ,struct Node * );
void promotion(struct Tree * ,struct Node * );

#endif
