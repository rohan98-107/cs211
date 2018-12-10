
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct Line_struct
{
    int valid;
    unsigned long int tag;
    unsigned int block;
    struct Line_struct *next;

}Line;

typedef struct Cache_struct
{
    int reads;
    int writes;
    int hits;
    int misses;

}Cache;

unsigned int log_2( unsigned int x )
{
    int result = 0;
    while ( x >>= 1 )
        result++;
    return result;
}

char* hexToBin( char* hex )
{
    char* result;
    result = (char*) malloc(48+1);
    result[0] = '\0';
    int i = 2;
    while( hex[i] != '\0' )
    {
        switch(hex[i])
        {
            case '0':
                strcat(result, "0000");
                break;
            case '1':
                strcat(result, "0001");
                break;
            case '2':
                strcat(result, "0010");
                break;
            case '3':
                strcat(result, "0011");
                break;
            case '4':
                strcat(result, "0100");
                break;
            case '5':
                strcat(result, "0101");
                break;
            case '6':
                strcat(result, "0110");
                break;
            case '7':
                strcat(result, "0111");
                break;
            case '8':
                strcat(result, "1000");
                break;
            case '9':
                strcat(result, "1001");
                break;
            case 'a':
                strcat(result, "1010");
                break;
            case 'b':
                strcat(result, "1011");
                break;
            case 'c':
                strcat(result, "1100");
                break;
            case 'd':
                strcat(result, "1101");
                break;
            case 'e':
                strcat(result, "1110");
                break;
            case 'f':
                strcat(result, "1111");
                break;
            case 'x':
                strcat(result, "");
                break;
        }
        i++;
    }

    char *extend = (char*) malloc(49);
    if(strlen(result) == 48)
        return result;
    int j;
    for( j = 0; j < 48-strlen(result); j++ )
        extend[j] = '0';
    extend[j+1] = '\0';
    strcat(extend, result);
    return extend;
}
int listlen(Line *head)
{
    int len = 0;
    Line *ptr = head;
    while (ptr != NULL)
    {
        len++;
        ptr = ptr->next;
    }

    return len;
}

Line* fifo(Line *head, Line *new, int E)
{
    if ( listlen(head) >= E )
    {
        if( E == 1 )
        {
            return new;
        }

        Line* start = head;
        Line* ptr = head->next;
        Line* prev = head;

        while(ptr->next != NULL)
        {
            ptr = ptr->next;
            prev = prev->next;
        }

        prev->next = NULL;

        new->next = start;
        start = new;

        return start;
        //return enqueue(dequeue(head),new);
    }
    else
    {
        Line *ptr = head;
        if(ptr == NULL)
            ptr = new;
        else
        {
            new->next = ptr;
            ptr = new;
        }

        return ptr;
    }

}

Line* lru( Line* head, Line* target )
{
	Line* headptr = head;
	Line* prev = head;
	Line* ptr = head->next;
	if( prev->tag == target->tag )
		return head;
	while( ptr->tag != target->tag )
	{
		ptr = ptr->next;
		prev = prev->next;
	}

	prev->next = ptr->next;

   target->next = headptr;
   headptr = target;

   return headptr;

}

unsigned long int extract_tag( char* binary, int b, int s, int t )
{
    char *ptr = binary;
    char *result = (char*) malloc((t+1)*sizeof(char));
    char *temp = result;
    for(int i = 0; i < t; i++)
        *result++ = *ptr++;

    return strtol(temp, NULL, 2);
}

unsigned int extract_set( char* binary, int b, int s, int t )
{
    if ( s == 0 )
        return 0;
    char *ptr = binary;
    char *result = (char*) malloc((t+s+1)*sizeof(char));
    char *temp = result;
    int i = 0;
    while( i < t + s )
    {
        *result++ = *ptr++;
        if ( i < t )
        {
            --result;
        }
        i++;
    }

    return strtol(temp, NULL, 2);
}

unsigned int extract_block(char* binary, int b, int s, int t)
{
    char* ptr = binary;
    char* result = (char*) malloc((b+s+t+1)*sizeof(char));
    char* temp = result;
    int i = 0;
    while( i < t + s + b )
    {
        *result++ = *ptr++;
        if( i < s + t )
            --result;
        i++;
    }

    return strtol(temp, NULL, 2);
}

int search( Line *head, long unsigned int target)
{
    Line *ptr = head;

    while( ptr != NULL )
    {
        if( ptr->tag == target)
        {
            return 1;
        }
        ptr = ptr->next;
    }

    return 0;
}

int main( int argc, char** argv )
{
    //GIVENS
    int cache_size_bytes = strtol(argv[1], NULL, 10);
    char* associativity = argv[2];
    char* cache_policy = argv[3];
    int block_size = strtol(argv[4], NULL, 10);
    FILE* trace_fp = fopen( argv[5], "r" );

    //

    //DERIVED VARIABLES
    int E = 0; //number of lines per set ( or nodes per array item )
    int b = log_2(block_size); // number of block offset bits
    if( strcmp(associativity, "direct") == 0 )
        E = 1; // number of lines per set
    else if ( strcmp(associativity, "assoc") == 0 )
        E = cache_size_bytes/block_size;
    else
    {
        int n;
        sscanf(associativity, "assoc:%d", &n);
        E = n;
    }

    int S = cache_size_bytes/(block_size*E); //number of sets
    int s = log_2(S);
    int t = 48 - (s+b);
    //

    //STRUCTURES
    Cache c1 = {0,0,0,0};
    Cache c2 = {0,0,0,0}; //prefetching

    Line* cache1[S];
    if(S == 1) {cache1[0] = NULL;}
    for( int i = 0; i < S; i++ )
        cache1[i] = NULL;

    Line* cache2[S];
    if(S == 1) {cache2[0] = NULL;}
    for( int i = 0; i < S; i++ )
        cache2[i] = NULL;


    //SIMULATE
    char line[24];
    do
    {
        int garbage;
        char rw;
        char memaddr[15];
        Line *templine = (Line*) calloc(1, sizeof(Line));
        Line *templine2 = (Line*) calloc(1, sizeof(Line));
        templine->valid = 1;
        templine2->valid = 1;

        fscanf(trace_fp, "%X: %c %s", &garbage, &rw, memaddr );

        char* memaddr_bin = hexToBin(memaddr);
        templine->tag = extract_tag(memaddr_bin, b, s, t);
        templine2->tag = extract_tag(memaddr_bin, b, s, t);
        unsigned int set_index = extract_set(memaddr_bin, b, s, t);
        templine->block = extract_block(memaddr_bin, b, s, t);
        templine2->block = extract_block(memaddr_bin, b, s, t);


        if( rw == 'R' )
        {
            //no-prefetch
            // (cache hit)
            if(search(cache1[set_index], templine->tag) == 1)
            {
            	 if( strcmp(cache_policy, "lru") == 0 )
            	 {
            	 	Line *newtemp = (Line*)calloc(1, sizeof(Line));
                  newtemp->valid = 1;
                  newtemp->tag = templine->tag;
                  newtemp->block = templine->block;
                  newtemp->next = NULL;
            	 	cache1[set_index] = lru(cache1[set_index], newtemp);
            	 }
                c1.hits++;
            }
            else // (cache miss)
            {
                cache1[set_index] = fifo(cache1[set_index], templine, E);
                c1.misses++;
                c1.reads++;
            }
            //prefetch
            // cache hit
            if( search(cache2[set_index], templine2->tag) == 1)
            {
					 if( strcmp(cache_policy, "lru") == 0 )
            	 {
            	 	Line *newtemp = (Line*)calloc(1, sizeof(Line));
                  newtemp->valid = 1;
                  newtemp->tag = templine2->tag;
                  newtemp->block = templine2->block;
                  newtemp->next = NULL;
						cache2[set_index] = lru(cache2[set_index], newtemp);
            	 }
                c2.hits++;
            }
            else //cache miss
            {
                cache2[set_index] = fifo(cache2[set_index], templine2, E);
                c2.misses++;
                c2.reads++;
                if(set_index < S-1)
                {
                    if(search(cache2[set_index+1], templine2->tag) == 0)
                    {
                        Line *newtemp = (Line*)calloc(1,sizeof(Line));
                        newtemp->valid = 1;
                        newtemp->tag = templine2->tag;
                        newtemp->block = templine2->block;
                        newtemp->next = NULL;
                        cache2[set_index+1] = fifo(cache2[set_index+1], newtemp, E);
                        c2.reads++;
                    }
                }
                else // if index == S-1 or there is only one set
                {
                    if(search(cache2[0], templine2->tag + 1) == 0 )
                    {
                        Line *newtemp = (Line*)calloc(1, sizeof(Line));
                        newtemp->valid = 1;
                        newtemp->tag = templine2->tag + 1;
                        newtemp->block = templine2->block;
                        newtemp->next = NULL;
                        cache2[0] = fifo(cache2[0], newtemp, E);
                        c2.reads++;
                    }
                }
            }

        }
        else if( rw == 'W' )
        {
            //no-prefetch
            // (write miss)
            if(search(cache1[set_index], templine->tag) == 0)
            {
                cache1[set_index] = fifo(cache1[set_index], templine, E);
                c1.writes++;
                c1.misses++;
                c1.reads++;
            }
            else             // (write hit)
            {
            	if( strcmp(cache_policy, "lru") == 0 )
            	 {
            	 	Line *newtemp = (Line*)calloc(1, sizeof(Line));
                  newtemp->valid = 1;
                  newtemp->tag = templine->tag;
                  newtemp->block = templine->block;
                  newtemp->next = NULL;
            	 	cache1[set_index] = lru(cache1[set_index], newtemp);
            	 }
                c1.writes++;
                c1.hits++;
            }

            //prefetch
            //write miss
            if(search(cache2[set_index], templine2->tag) == 0)
            {
                cache2[set_index] = fifo(cache2[set_index], templine2, E);
                c2.writes++;
                c2.misses++;
                c2.reads++;
                if(set_index < S-1)
                {
                    if(search(cache2[set_index+1], templine2->tag) == 0)
                    {
                        Line* newtemp = (Line*)calloc(1,sizeof(Line));
                        newtemp->valid = 1;
                        newtemp->tag = templine2->tag;
                        newtemp->block = templine2->block;
                        newtemp->next = NULL;
                        cache2[set_index+1] = fifo(cache2[set_index+1], newtemp, E);
                        c2.reads++;
                    }
                }
                else // if index == S-1 or there is only one set
                {
                    if(search(cache2[0], templine2->tag + 1) == 0 )
                    {
                        Line *newtemp = (Line*)calloc(1, sizeof(Line));
                        newtemp->valid = 1;
                        newtemp->tag = templine2->tag + 1;
                        newtemp->block = templine2->block;
                        newtemp->next = NULL;
                        cache2[0] = fifo(cache2[0], newtemp, E);
                        c2.reads++;
                    }
                }

            }
            else             // (write hit)
            {
            	if( strcmp(cache_policy, "lru") == 0 )
            	 {
            	 	Line *newtemp = (Line*)calloc(1, sizeof(Line));
                  newtemp->valid = 1;
                  newtemp->tag = templine2->tag;
                  newtemp->block = templine2->block;
                  newtemp->next = NULL;
            	 	cache2[set_index] = lru(cache2[set_index], newtemp);
            	 }
                c2.writes++;
                c2.hits++;
            }
        }
        else
            continue;


    }while( fgets(line, 24, trace_fp ) != NULL );
    //

    printf("no-prefetch\n");
    printf("Memory reads: %d\n", c1.reads);
    printf("Memory writes: %d\n", c1.writes);
    printf("Cache hits: %d\n", c1.hits - 2);
    printf("Cache misses: %d\n", c1.misses);
    printf("with-prefetch\n");
    printf("Memory reads: %d\n", c2.reads);
    printf("Memory writes: %d\n", c2.writes);
    printf("Cache hits: %d\n", c2.hits - 2);
    printf("Cache misses: %d\n", c2.misses);


    return 0;
    
}
