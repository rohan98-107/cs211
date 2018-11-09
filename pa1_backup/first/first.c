#include <stdio.h>
#include <stdlib.h>

void swap(int*, int*);
void sortFrom(int[], int, int);

int main(int argc, char** argv)
{
    FILE* fileptr;
    fileptr = fopen( argv[1] , "r" );
    char line[100];
    int arr[100];
    int temp;
    
    
    int len = atoi( fgets(line, 100, fileptr) );
    
    int i = 0;
    int j = 0;
    do
    {
        fscanf(fileptr, "%d\t", &temp);
        if(temp % 2 == 0)
        {
            arr[j] = temp;
            j++;
        }
        else
        {
            arr[len-1-i] = temp;
            i++;
        }
        
    } while( i + j < len );
    
    int partition = 0;
    while( arr[partition] % 2 == 0 )
        partition++;
    
    sortFrom(arr, 0, partition);
    sortFrom(arr, partition, len);
    
    for(int j = 0; j < len; j++)
    {
        printf("%d\t", arr[j]);
    }
    
    return 0;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void sortFrom(int arr[], int beg_index, int end_index)
{
    int mindex;
    
    for( int i = beg_index; i < end_index - 1; i++ )
    {
        mindex = i;
        for( int j = i + 1; j < end_index; j++ )
        {
            if( arr[j] < arr[mindex] )
                mindex = j;
        }
        
        swap(&arr[i], &arr[mindex]);
    }
    
    return;
}
