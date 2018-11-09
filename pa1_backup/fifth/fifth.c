#include <stdio.h>
#include <stdlib.h>

int ** createMatrix( int n )
{
  int ** matrix;

  matrix = (int**) malloc(n * sizeof(int *));

  for( int i = 0; i < n; i++ )
  {
      matrix[i] = (int *)malloc(n * sizeof(int));
  }

  for( int i = 0; i < n; i++ )
  {
      for( int j = 0; j < n; j++ )
      {
          matrix[i][j] = 0;
      }
  }

  return matrix;
}

int duplicateElements( int ** A, int n )
{
	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			for( int k = 0; k < n; k++ )
			{
				for( int l = 0; l < n; l++ )
				{
					if( l == j && k == i )
						continue;
					if( A[i][j] == A[k][l] )
						return 1;
				}
			}
		}		
	}
	
	return 0;
}
int magicMatrix(int ** A, int n)
{
	int magicSum = 0;
	int tempSum = 0;
	//int row;
	
	for( int i = 0; i < n; i++ )
		magicSum += A[i][0];
	
	for( int i = 0; i < n; i++ )
	{
		tempSum = 0;
		for( int j = 0; j < n; j++ )
		{
			tempSum += A[i][j];
		}
		
		if( tempSum != magicSum )
			return 0;
	}
	
	tempSum = 0;
	for( int i = 0; i < n; i++ )
	{
		tempSum = 0;
		for( int j = 0; j < n; j++ )
		{
			tempSum += A[j][i];
		}
		
		if( tempSum != magicSum )
			return 0;
	}
	
	return 1;
}

void printMatrix( int ** M, int n )
{
  for( int i = 0; i < n; i++ )
  {
      for( int j = 0; j < n; j++ )
      {
         printf("%d\t", M[i][j]);
      }
      printf("\n");
  }
}
int main(int argc, char** argv)
{
    FILE *fp;
    fp = fopen( argv[1], "r");
    int n;

    fscanf(fp, "%d\n", &n);

    int ** A = createMatrix(n);
    //int count = 0;
    for( int i = 0; i < n; i++ )
    {
    	for ( int j = 0; j < n; j++ )
    	{
    		fscanf(fp, "%d\t", &A[i][j]);
    	}
    	
    }
    
    if( duplicateElements( A, n ) == 1 )
    	printf("not-magic\n");
    else 
    {
    	if( magicMatrix(A, n) == 1 )
    		printf("magic\n");
   	 else 
    		printf("not-magic\n");
    }


    return 0;

}