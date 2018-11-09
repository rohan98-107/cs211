#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int isVowel( char c )
{
	if(c == 'A' || c == 'E' || c == 'I' ||  
      c == 'O' || c == 'U' || c == 'a' ||  
      c == 'e' || c == 'i' || c == 'o' ||
      c == 'u' )
   {
		return 1;           
	}
   else 
   {
   	return 0;
   }
}

char* translate( char *word )
{	
	char *myword = (char*)calloc(100,sizeof(char));
	char *tmp;
	char *tmp2;
	tmp = myword;
	tmp2 = word;
	while( word != NULL )
	{
		*myword++ = *word++;
		break;
	}

	char* finalWord = (char *)calloc( 100, sizeof(char));
	
	if( isVowel(*tmp) == 1 )
	{
		strcpy(finalWord, tmp);
		strcat(finalWord, tmp2+1);
		strcat(finalWord, "yay" );
	}
	else 
	{
		strcpy(finalWord, tmp2+1);
		strcat(finalWord, tmp);
		strcat(finalWord, "ay" );
	}
	
	return finalWord;
}

int main( int argc, char **argv)
{	
	int i = 1; 
	while( i < argc )
	{
		char* str = " ";
		str = argv[i];
		printf("%s ", translate(str));
		i++;
	}
	return 0;
}