#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *next;

}Node;

void swap(Node *x, Node *y)
{
    int temp = x->val;
    x->val = y->val;
    y->val = temp;
}

void printlist(Node *head)
{
    Node *current = head;

    while( current->next != NULL)
    {
        printf("%d\t", current->val);
        current = current->next;
    }
}

int occurenceOf(int *target,Node *head)
{
    Node *temp = head;

    while( temp->next != NULL)
    {
        if( temp->val == *target)
            return 1;
        temp = temp->next;
    }

    return 0;
}

void sort(Node *head)
{
    Node *current = head;
    Node *ptr;
    Node *min;

    while(current->next != NULL)
    {
        min = current;
        ptr = current->next;

        while(ptr->next != NULL)
        {
            if( min->val > ptr->val )
            {
                min = ptr;
            }

            ptr = ptr->next;
        }

        swap(current, min);
        current = current->next;
    }

    return;
}

Node * addNode(Node *new,Node *head)
{
	 if(occurenceOf(&new->val, head) == 1)
	 	return head;

    new->next = head;
    head = new;
    return head;
}

Node * deleteNode(int *target,  Node *head)
{
    if( occurenceOf(target, head) == 0 || head == NULL )
        return head;
    else if( head->val == *target)
    {
        head = head->next;
    }
    else
    {
        Node *curr = head->next;
        Node *prev = head;

        while( curr->next != NULL )
        {
            if( curr->val == *target )
            {
                prev->next = curr->next;
                break;
            }
            else
            {
                prev = prev->next;
                curr = curr->next;
            }
        }

    }

    return head;

}


int main(int argc, char** argv)
{
    FILE* fp;
    fp= fopen(argv[1], "r" );
    char pair[5];
    
    if( fp == NULL )
    {
    	printf("error");
    	return 0;
    }

    Node *head = (Node *)malloc( sizeof(Node) );

    char op;

    do
    {
        int temp;
        Node *new = (Node *)malloc(sizeof(Node));

        fscanf(fp, "%c\t%d", &op, &temp );

        new->val = temp;

        if( op == 'i' )
        {
            head = addNode(new,head);
        }
        else if( op == 'd' )
        {
            head = deleteNode(&temp,head);
        }
        else
            continue;

    } while( fgets(pair, 5, fp) != NULL );

    sort(head);

    int n = 0;
    for( Node* temp = head; temp->next != NULL; temp = temp->next)
    	n++;
    printf("%d\n", n);
    printlist(head);

    return 0;
}
