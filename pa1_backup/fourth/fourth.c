#include <stdio.h>
#include <stdlib.h>

int ** createMatrix( int rows, int cols )
{
  int ** matrix;

  matrix = (int**) malloc(rows * sizeof(int *));

  for( int i = 0; i < rows; i++ )
  {
      matrix[i] = (int *)malloc(cols * sizeof(int));
  }

  for( int i = 0; i < rows; i++ )
  {
      for( int j = 0; j < cols; j++ )
      {
          matrix[i][j] = 0;
      }
  }

  return matrix;
}

int ** multiply_matrices( int ** A, int ** B, int rA, int cA, int cB )
{
	int **product = createMatrix(rA,cB);
	
	for( int i = 0; i < rA; i++ )
	{
		for( int j = 0; j < cB; j++ )
		{
			for( int k = 0; k < cA; k++ )
			{
				product[i][j] += A[i][k] * B[k][j];
			}
		}
	}
   return product;
}

void printMatrix( int ** M, int rows, int cols )
{
  for( int i = 0; i < rows; i++ )
  {
      for( int j = 0; j < cols; j++ )
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
    int rows_A, cols_A;

    fscanf(fp, "%d\t%d\n", &rows_A, &cols_A);

    int ** A = createMatrix(rows_A, cols_A);

    for( int i = 0; i < rows_A; i++ )
    {
        for( int j = 0; j < cols_A; j++ )
        {
           fscanf(fp, "%d\t", &A[i][j]);
        }
    }

    int rows_B, cols_B;

    fscanf(fp, "%d\t%d\n", &rows_B, &cols_B);

    int ** B = createMatrix(rows_B, cols_B);

    for( int i = 0; i < rows_B; i++ )
    {
        for( int j = 0; j < cols_B; j++ )
        {
           fscanf(fp, "%d\t", &B[i][j]);
        }
    }

    //printMatrix(A, rows_A, cols_A);
    //printMatrix(B, rows_B, cols_B);
    
    if( cols_A != rows_B )
    {
    	printf("bad-matrices");
    	return 0;
    }
    int ** C =  createMatrix(rows_A, cols_B);
    C = multiply_matrices(A, B, rows_A, cols_A, cols_B);
    printMatrix( C, rows_A, cols_B);

    return 0;

}
