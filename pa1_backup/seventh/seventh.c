#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char translate( char *word )
{	
	char temp;
	
	while( strlen(word) != 0 )
	{
		temp = *word++;
	}
	
	return temp;
	
}

int main( int argc, char** argv)
{
	int i = 1;
	while( i < argc )
	{
		char *str = argv[i];
		printf("%c", translate(str));
		i++;
	}
	return 0;
}