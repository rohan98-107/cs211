#include <stdio.h>
#include <stdlib.h>

double ** createMatrix( int rows, int cols )
{
    double ** matrix;
    
    matrix = (double**) malloc(rows * sizeof(double *));
    
    for( int i = 0; i < rows; i++ )
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
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

void freeMatrix( double ** A, int rows )
{
    for( int i = 0; i < rows; i++ )
    {
        free( A[i] );
    }
    
    free(A);
    return;
    
}

double ** multiply_matrices( double ** A, double ** B, int rA, int cA, int cB )
{
    double **product = createMatrix(rA,cB);
    
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

void printMatrix( double ** M, int rows, int cols )
{
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < cols; j++ )
        {
            printf("%0.0lf\t", M[i][j]);
        }
        printf("\n");
    }
}

double ** findTranspose( double ** A, int rows, int cols )
{
    double ** A_t = createMatrix( cols, rows );
    
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < cols; j++ )
        {
            A_t[j][i] = A[i][j];
        }
    }
    
    return A_t;
}

double ** findInverse( double ** X, int n )
{
    double ** X_inv = createMatrix( n, n );
    double ** X_copy = X;
    
    for( int i = 0; i < n; i++ )
        X_inv[i][i] = 1;
    
    for( int i = 0; i < n; i++ ) // inverse calculation
    {
        for( int j = 0; j < n; j++ )
        {
            // for upper triangular use ( i < j ); lower triangular use ( i > j)
            if( i != j ) /*if( i < j )*/
            {
                double factor = X_copy[j][i]/X_copy[i][i];
                for( int k = 0; k < n /* n */; k++ )
                {
                    X_copy[j][k] += -1*factor*X_copy[i][k];
                    X_inv[j][k] += -1*factor*X_inv[i][k];
                }
            }
        }
    }
    
    /*for( int i = n-1; i > 0; i-- ) // lower triangluar matrix
     {
     for( int j = n-1; j > 0; j-- )
     {
     if( i > j )
     {
     double factor = X_copy[j][i]/X_copy[i][i];
     for( int k = n-1; k >= 0; k-- )
     {
     X_copy[j][k] += -1*factor*X_copy[i][k];
     X_inv[j][k] += -1*factor*X_inv[i][k];
     }
     }
     }
     }*/
    
    for( int i = 0; i < n; i++ )
    {
        double val = X_copy[i][i];
        for( int j = 0; j < n; j++ )
        {
            X_copy[i][j] = X_copy[i][j]/val;
            X_inv[i][j] = X_inv[i][j]/val;
        }
    }
    
    freeMatrix( X_copy, n );
    //return X_copy;
    return X_inv;
}

int main( int argc, char ** argv )
{
    FILE* train_fp;
    FILE* test_fp;
    train_fp = fopen( argv[1], "r" );
    test_fp = fopen( argv[2], "r" );
    //train_fp = fopen( "/Users/rohanrele/Documents/Misc/TestEnvironment/TestEnvironment/train.txt", "r" );
    //test_fp = fopen( "/Users/rohanrele/Documents/Misc/TestEnvironment/TestEnvironment/test.txt", "r" );

    
    int N, K, M;
    fscanf( train_fp, "%d", &K );
    fscanf( train_fp, "%d", &N );
    fscanf( test_fp, "%d", &M );
    
    double ** trainMatrix = createMatrix( N, K + 1);
    double ** testMatrix = createMatrix( M, K + 1 );
    double ** weights = createMatrix( K + 1, 1 );
    double ** init_prices = createMatrix( N, 1 );
    
    //populate train and test matrices and Y
    for( int i = 0; i < N; i++ )
    {
    	  trainMatrix[i][0] = 1.00;
        for( int j = 1; j <= K; j++ )
            fscanf(train_fp, "%lf,", &trainMatrix[i][j]);
        fscanf(train_fp, "%lf", &init_prices[i][0]);
    }
    
    for( int i = 0; i < M; i++ )
    {
    	  testMatrix[i][0] = 1.00;
        for( int j = 1; j <= K; j++ )
            fscanf(test_fp, "%lf,", &testMatrix[i][j]);
    }
    
    //
    
    //now find weights using train matrix
    
    double ** temp = createMatrix( K+1, K+1 );
    double ** pseudo = createMatrix( K+1, N);
    temp = findInverse(multiply_matrices( findTranspose(trainMatrix, N, K+1) , trainMatrix, K+1, N, K+1 ), K+1);
    pseudo = multiply_matrices( temp, findTranspose(trainMatrix, N, K+1), K+1, K+1, N );
    weights = multiply_matrices( pseudo, init_prices, K+1, N, 1 );
    //
    
    //calculate prices by doing test*weights = prices
    
    double ** results = createMatrix(M, 1);
    results = multiply_matrices(testMatrix, weights, M, K+1, 1);
    printMatrix(results, M, 1);
    
    return 0;
    
}