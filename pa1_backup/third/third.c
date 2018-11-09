#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 10000

typedef struct Node_struct
{
    int val;
    struct Node_struct *next;
    
}Node;

int search(Node *table_entry, int *target)
{
    Node *temptr = table_entry;
    while(temptr != NULL)
    {
        if( temptr->val == *target )
        {
            return 1;
        }
        temptr = temptr->next;
    }
    
    return 0;
    
    /*Node *temp = head;
     
     while( temp->next != NULL)
     {
     if( temp->val == *target)
     return 1;
     temp = temp->next;
     }
     
     return 0;*/
}

Node * insert(Node *table_entry, Node *x)
{
    Node *ptr = table_entry;
    if(ptr == NULL)
        ptr = x;
    else
    {
        x->next = ptr;
        ptr = x;
    }
    
    return ptr;
    /*new->next = head;
     head = new;
     return head;*/
}

int main(int argc, char** argv)
{
    FILE* fp;
    //char* filename = argv[1];
    fp = fopen( argv[1], "r" );
    Node *hashtable[SIZE] = {NULL};
    char line[4];
    int key = 0;
    int inputval = 0;
    char op;
    
    if( fp == NULL )
    {
        printf("error");
        return 0;
    }
    
    //int i = 0;
    int count;
    do
    {
        count = fscanf(fp, "%c\t%d", &op, &inputval);
        
        if(count < 2)
        		break;
        		
        Node *new = (Node *)malloc(sizeof(Node));
        key = inputval % SIZE;
        if( inputval < 0 )
            key = SIZE + (inputval % SIZE);
        new->val = inputval;
        new->next = NULL;
        
        if( op == 'i' )
        {
            if( search(hashtable[key%SIZE],&inputval) == 1)
                printf("duplicate\n");
            else
            {
                hashtable[key%SIZE] = insert(hashtable[key%SIZE],new);
                printf("inserted\n");
            }
            
        }
        else if( op == 's' )
        {
            if( search(hashtable[key%SIZE],&inputval) == 1 )
                printf("present\n");
            else
                printf("absent\n");
        }
        else 
        	break;
        	
       // i++;
        
    } while( fgets(line, 4, fp ) != NULL );
    
    return 0;
}
