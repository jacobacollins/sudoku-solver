/*Jacob Collins*/
/*sudoku solver*/
/*CS241*/


/*Just felt like these macros would make it easier to change code if needed*/
#define undefined '.'
#define errorCheck FALSE
#define TRUE 1
#define FALSE 0
#define LOW '1'
#define HIGH '9'
/*This makes it easier to redefine the size of the array if needed*/
#define N '9'
#define newline '\n'

#include <stdio.h>

/*Function declarations*/
int fillBoard(int sudoku[][N]);
int checkRow(int sudoku[][N]);
int checkCol(int sudoku[][N]);
int checkRegion(int sudoku[][N]);
int recursive(int sudoku[][N], int index);
int checkCell(int sudoku[][N], int index, int num);
int cantSolve(int sudoku[][N]);
void makeBoard(int sudoku[][N]);

/*main method with error checking*/
int main (void)
{
  int sudoku[N][N];
  int index = 0;
  int error;

   while ((error = fillBoard(sudoku)) != EOF)
      {
        error += checkRow(sudoku);

        error += checkCol(sudoku);
        error += checkRegion(sudoku);

        if (error) printf("Error\n\n");
        else
          {
            if (errorCheck) makeBoard(sudoku);
            recursive(sudoku, index);
            if (!cantSolve(sudoku)) makeBoard(sudoku);
          }
      }
      return 0;
}


/*This fills the sudoku board with values from the array*/
int fillBoard(int sudoku[][N])
{
    int i, num, row, col;
    int error = FALSE;

  for (i = 0; (num = getchar()) != newline; i++)
       {
        if (num == EOF) return EOF;
        putchar(num);
        if((num < LOW || num > HIGH) && (num != undefined)) error = TRUE;
        if (num == undefined) num = '0';

        row = (i / 9) % 9;
        col = i % 9;
        sudoku[row][col] = num - '0';
       }
            putchar(newline);
            if (i != 81) error = TRUE;
            return error;
          }

/*Checks for row errors*/
int checkRow(int sudoku[][N])
{
     int rowLoop, columnLoop,c ;


       for (rowLoop = 0; rowLoop < 9; rowLoop++)
         {
        for (columnLoop = 0; columnLoop < 9; columnLoop++)
          {/*got the column offset*/
            for (c = columnLoop + 1; c < 9; c++)
              {
                while ((sudoku[rowLoop][columnLoop] != 0) &&
                      (sudoku[rowLoop][columnLoop] == sudoku[rowLoop][c]))
                  {
                    return TRUE;
                  }
                }
              }
            }

       return FALSE;
}


/*Checks columns for errors*/
int checkCol(int sudoku[][N])
{
int rowLoop, columnLoop, c;
    for (columnLoop = 0; columnLoop < 9; columnLoop++)
          {
        for (rowLoop = 0; rowLoop < 9; rowLoop++)
          {/*Got the row offset*/
            for (c = rowLoop + 1; c < 9; c++)
              {
             while((sudoku[rowLoop][columnLoop] != 0) &&
                  (sudoku[rowLoop][columnLoop] == sudoku[c][columnLoop]))
                  {
                    return TRUE;
                  }
              }
          }
      }
    return FALSE;
}


/*checks each 3x3 sub region for errors*/
int checkRegion(int sudoku[][N])
{
int rowLoop, columnLoop, r, c;
    for (rowLoop = 0; rowLoop < 9; rowLoop += 3)
        {
       for (columnLoop = 0; columnLoop < 9; columnLoop += 3)
          {
            for (r = 0; r < 9; r++)
              {
                for (c = r + 1; c < 9; c++)
                  {
                    while((sudoku[rowLoop + r / 3][columnLoop + r % 3] != 0) &&
                         (sudoku[rowLoop + r / 3][columnLoop + r % 3] ==
                          sudoku[rowLoop + c / 3][columnLoop + c % 3]) )
                      {
                        return TRUE;

                     }
                  }
              }
          }
      }
    return FALSE;
}


/*If a puzzle has no solution this will return such*/
int cantSolve(int sudoku[][N])
{
    int i, j;
       for (i = 0; i < 9; i++)
        {
        for (j = 0; j < 9; j++)
          {
            while(!sudoku[i][j])
              {
                printf("No solution\n\n");
                return TRUE;
              }
          }
      }
   return FALSE;
}


/*This prints out the board for the sudoku values*/
void makeBoard(int sudoku[][N])
{
    int row, col;
    for (row = 0; row < 9; row++)
      {
        if (row == 3 || row == 6)
          {
            printf("---------------------\n");
          }
        for (col = 0; col < 9; col++)
          {
            printf(" ");
            if (sudoku[row][col]) printf("%d", sudoku[row][col]);
            else printf(".");
            if(col == 2 || col == 5) printf(" |");

          }
    printf("\n\n");
       }
}


/*Got our main recursive solver*/
int recursive(int sudoku[][N], int index)
{
   int num;
   int row = index / 9;
   int col = index % 9;

      while(index == 81)
          {
           return TRUE;
          }
            if (sudoku[row][col] != 0)
              {
                return recursive(sudoku, ++index);        /* recursive call */
              }
  else
          {
            for (num = 1; num <= 9; num++)
              {
            if (checkCell(sudoku, index, num))
              {
                sudoku[row][col] = num;
                if (recursive(sudoku, index)) return TRUE;
                sudoku[row][col] = 0;
              }
          }
        return FALSE;
     }
}


 /*Checks to see Valid moves for rows, columns, and regions*/
int checkCell(int sudoku[][N],int start, int num)
{
   int r, c;
   int row = start / 9;
   int column = start % 9;
   int regionFirstRow = row - (row %3 );
   int regionFirstColumn = column - (column % 3);


            /*Checks rows for valid moves*/
   for(c = 0; c < 9; c++)
     {
        if(sudoku[row][c] == num)
          {
            return FALSE;
          }
      }
            /*Checks columns for valid moves*/
    for(r = 0; r < 9; r++)
      {
        if(sudoku[r][column] == num)
          {
            return FALSE;
          }
      }
 /*FINISH THIS!!!!!!!!!*/
            /*Checks each 3x3 region for valid moves*/
   for(r = 0; r < 3; r++)
     {
        for(c = 0; c < 3; c++)
          {
            if(sudoku[regionFirstRow + r][regionFirstColumn + c] == num)
              {
                return FALSE;
              }
          }
      }
    return TRUE;
}
