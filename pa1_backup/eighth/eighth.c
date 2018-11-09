#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int val;
	struct node *left;
	struct node *right;
	
}node;

node * createNode(int val)
{
	node *new = (node*)malloc(sizeof(node));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	
	return new;
}

int search( node *root, int target)
{
	node *curr = root;
	while(curr != NULL)
	{
		if(curr->val == target)
			return 1;
		else if( curr->val < target )
			curr = curr->right;
		else 
			curr = curr->left;
	}
	
	return 0;
}

/*int getHeighthelp( node* root, int val, int height )
{
	if( root == NULL )
		return 0;
	if( root->val == val )
		return height;
		
	int temp = getHeighthelp( root->left, val, height+1);
	if( temp != 0 )
		return temp;
	temp = getHeighthelp(root->right, val, height+1);
	return temp;
}*/

int getHeight( node* root, int val)
{
	//return getHeighthelp(root, val, 1);
	int height = 1;
	node* ptr = root;
	while( ptr->val != val && ptr != NULL )
	{
		if( ptr->val < val )
			ptr = ptr->right;
		else 
			ptr = ptr->left;
		height++;
	}
	
	return height;
}

node * insert( node *root, int val)
{
	if( root == NULL )
		return createNode(val);
	else if( val < root->val )
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);

	return root;
}

void printTree( node *root )
{
	if( root != NULL )
	{
		printf("%d\n", root->val);
		printTree(root->left);
		printTree(root->right);
	}
	else 
		return;
}

int main( int argc, char** argv)
{
	FILE* fp;
	fp = fopen( argv[1], "r" );
	char line[4];
	int x;
	char op;
	node* root = NULL;
	if( fp == NULL )
	{
		printf("error");
		return 0;
	}
	//int i = 0;
	int count;
	do
	{
		//printf("%d\n", i);
		count = fscanf(fp, "%c\t%d", &op, &x);
		
		if( count < 2 )
			break;
			
		if( op == 'i' )
		{
			if( search(root, x) == 1 )
				printf("duplicate\n");
			else 
			{
				root = insert(root, x);
				printf("inserted %d\n", getHeight(root, x) );
			}
		}
		else if( op == 's' )
		{
			if( search(root, x) == 1 )
				printf("present %d\n", getHeight(root,x) );
			else 
				printf("absent\n");
		}
		else 
			break;
			
		//i++;
		
	}while( fgets(line, 4, fp) != NULL );
	//printTree(root);
	return 0;

}

