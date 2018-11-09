#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9


int ** createBoard()
{
    int ** grid;

    grid = (int**) malloc(N * sizeof(int *));

    for( int i = 0; i < N; i++ )
    {
        grid[i] = (int *)malloc(N * sizeof(int));
    }

    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < N; j++ )
        {
            grid[i][j] = 0;
        }
    }

    return grid;
}

bool inColumn( int ** grid, int *col, int *num )
{
    for( int i = 0; i < N; i++ )
    {
        if( grid[i][*col] == *num )
            return true;
    }

    return false;
}

bool inRow( int ** grid, int *row, int *num )
{
    for( int i = 0; i < N; i++ )
    {
        if( grid[*row][i] == *num )
            return true;
    }

    return false;
}

bool inBox( int ** grid, int *row, int *col, int *num)
{
    int i = *row % (N/3);
    int j = *col % (N/3);

    for( int x = *row-i; x < *row-i + 3; x++ )
    {
        for( int y = *col-j; y < *col-j + 3; y++ )
        {
            if( grid[x][y] == *num )
            {
                    return true;
            }
        }
    }

    return false;
}

/*bool isValid( int ** grid, int row_index, int col_index, int num )
 {
 if( !inRow(grid, row_index, num) && !inColumn(grid, col_index, num) && !inBox(grid, row_index, col_index, num) )
 return true;
 return false;
 }*/

void printGrid( int ** grid )
{
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < N; j++ )
        {
            printf("%d\t", grid[i][j]);
        }
        printf("\n");
    }
}
bool solveSudoku( int ** grid )
{
    for( int row = 0; row < N; row++ )
    {
        for( int col = 0; col < N; col++ )
        {
            if(grid[row][col] == 0)
            {
                for( int num = 1; num <= 9; num++ )
                {
                    if(!inRow(grid, &row, &num) && !inColumn(grid, &col, &num) && !inBox(grid, &row, &col, &num))
                    {
                        grid[row][col] = num;
                        if(solveSudoku(grid))
                            return true;
                        else grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}
bool doubleCheck( int ** grid )
{
    for( int row = 0; row < N; row++ )
    {
        for( int col = 0; col < N; col++ )
        {
            if( grid[row][col] != 0 )
            {
                for( int i = 0; i < N; i++ )
                {
                    if( grid[row][i] == grid[row][col] && i != col )
                        return false;
                }

                for( int i = 0; i < N; i++ )
                {
                    if( grid[i][col] == grid[row][col] && i != row )
                        return false;
                }

                for( int i = row - row%3; i < row-(row%3) + 3; i++ )
                {
                    for( int j = col - col%3; j < col-(col%3) + 3; j++ )
                    {
                        if( grid[i][j] == grid[row][col] && i != row && j != col )
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

int main( int argc, char ** argv )
{
    FILE* fp;
    fp = fopen( argv[1], "r" );
    //fp = fopen( "/Users/rohanrele/Documents/Misc/TestEnvironment/TestEnvironment/test.txt", "r" );
    int ** input_grid = createBoard();
    for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < N; j++ )
        {
            char temp = '-';
            fscanf( fp, "%c\t", &temp);
            if( temp != '-' )
                input_grid[i][j] = (int) (temp - '0');
        }
    }

    if(solveSudoku(input_grid))
    {
        if(doubleCheck(input_grid))
            printGrid(input_grid);
        else
            printf("no-solution");
    }
    else
        printf("no-solution");

    return 0;
}
