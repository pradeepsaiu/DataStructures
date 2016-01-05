#include<stdio.h>
#include<stdlib.h>
#include"bst.h"

void insertNode(struct Node * insert, struct Data value)
{

	if(insert->obj.val < value.val)
	{
		if(insert->right != NULL)
			insertNode(insert->right,value);
		else
		{
			insert->right = createNode(value);
			insert->right->parent = insert;
		}
	}
	else if(insert->obj.val > value.val)
	{
		if(insert->left != NULL)
			insertNode(insert->left,value);
		else
		{
			insert->left = createNode(insert);
			insert->left->parent = insert;
		}
	}
	else
		printf("Value already found inside the tree");
}
void insert(struct Tree * bst, struct Data value)
{
	if(bst->root!=NULL)
		insertNode(bst->root,value);
	else
		bst->root =  createNode(value);
}

struct Node * searchNode(struct Node *node,struct Data value)
{
	if(node->obj.val < value.val)
        {
                if(node->right != NULL)
                        searchNode(node->right,value);
                else
                        return NULL;
        }
        else if(node->obj.val > value.val)
        {
                if(node->left != NULL)
                        searchNode(node->left,value);
                else
                	return NULL;
        }
        else
                return node;

}
struct Node * search(struct Tree *bst, struct Data value)
{
	struct Node * temp;

	if(bst->root != NULL)
	{
		temp = searchNode(bst->root,value);
		return temp;
	}
	else
		return NULL;
}
void inorder(struct Node * node)
{
	if(node!=NULL)
	{
		inorder(node->left);
		printf("\t%d",node->obj.val);
		inorder(node->right);
	}
}


void postorder_del(struct Tree *bst,struct Node *node)
{
	struct Data value;
	if(node!= NULL)
	{
		postorder_del(bst,node->left);
		postorder_del(bst,node->right);
		value.val = node->obj.val;
		removenode(bst,value);
	}
}
void removeLeaf(struct Tree *bst,struct Node *temp)
{
	if(temp->parent == NULL)
	{
		free(bst->root);
		bst->root = NULL;
	}
	else
	{
		if(temp->parent->left==temp)
		{
			free(temp->parent->left);
			temp->parent->left = NULL;
		}
		else
		{
			free(temp->parent->right);
			temp->parent->right =NULL;
		}
	}
}

void shortCircuit(struct Tree *bst,struct Node *temp)
{
	if(temp->parent == NULL)
	{
		if(temp->left == NULL)
		{
			temp->right->parent = NULL;
			bst->root = temp->right;
			free(temp);
		}
		else
		{
			temp->left->parent = NULL;
			bst->root = temp->left;
			free(temp);
		}
	}
	else if(temp->parent->left == temp)
	{
		if(temp->right==NULL)
		{
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
			free(temp);
		}
		else
		{
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
			free(temp);
		}
	}
	else
	{
                if(temp->right==NULL)
                {
                        temp->parent->right = temp->left;
                        temp->left->parent = temp->parent;
                        free(temp);
                }
                else
                { 
                        temp->parent->right = temp->right;
                        temp->right->parent = temp->parent;
                        free(temp);
                }


	}
}

void promotion(struct Tree *bst,struct Node *temp)
{
	struct Node *traverse;
	int num;struct Data copy;

	traverse = temp->right;
	while(traverse->left!=NULL)
	{
		traverse = traverse->left;
	}
	num = traverse->obj.val;
	copy.val = num;
	removenode(bst,copy);
	temp->obj.val = num;

}

void removenode(struct Tree *bst, struct Data value)
{
	struct Node * temp;
	temp = search(bst,value);
	if(temp!=NULL)
	{
		if(temp->right == NULL && temp->left == NULL)
			removeLeaf(bst,temp);
		else if(temp->right ==NULL || temp->left ==NULL)
			 shortCircuit(bst,temp);
		else
			promotion(bst,temp);
	}
	else
	{
		printf("Element not in the tree.");
	}
}
int main()
{
	struct Tree *tree1;
	struct Data input1;
	struct Node *temp;
	char input_buffer[10];
	int num;
	FILE *fp;

	tree1 = createTree();


        fp = fopen("tree.txt","r");

        while( fgets(input_buffer,sizeof(input_buffer),fp ))
        {
		num = atoi (input_buffer);
		input1.val = num;
		insert(tree1,input1);
	}
	num=1;
	printf("\Elements in the Tree->\n");
	inorder(tree1->root);
	while(num!=0)
	{
		printf("\n Press 0 to exit, or enter the number to be searched.\n");
		scanf("%d",&num);
		input1.val=num;
		temp = search(tree1,input1);

		if(temp!=NULL)
		{
			if(temp->parent==NULL)
			{
				printf("\nIt's the root node\n");
			}
			else
				printf("\nparent => %d",temp->parent->obj.val);
			if(temp->left!=NULL)
				printf("\nleft_child => %d",temp->left->obj.val);
			if(temp->right!=NULL)
				printf("\nright_child => %d",temp->right->obj.val);
		}
	}
	num=1;
	while(num!=0)
	{
		printf("\nPress 0 to exit, or enter a number to be deleted\n");
		scanf("%d",&num);
		input1.val =num;
		removenode(tree1,input1);
		inorder(tree1->root);
	}

	postorder_del(tree1,tree1->root);

	free(fp);
	free(tree1);
	return 0;
}
