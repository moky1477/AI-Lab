#include <stdio.h>
#include <stdlib.h>

#define INT_MAX_VALUE 2147483647

int myMin(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int myAbs(int i)
{
    if (i < 0)
    {
        return -i;
    }
    return i;
}

int main()
{
    int rows, columns;
    printf("Enter No. of rows : ");
    scanf("%d", &rows);

    printf("Enter No. of columns : ");
    scanf("%d", &columns);

    int maze[rows][columns];

    printf("Start Co-ordinates : ");
    int s_row;
    scanf("%d", &s_row);
    int s_col;
    scanf("%d", &s_col);

    printf("End Co-ordinates : ");
    int e_row;
    scanf("%d", &e_row);
    int e_col;
    scanf("%d", &e_col);

    int k;
    printf("How many blocks you want to put? ");
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        printf("Enter block Co-ordinates: ");
        int k1, k2;
        scanf("%d", &k1);
        scanf("%d", &k2);
        maze[k1][k2] = -1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (maze[i][j] != -1)
            {
                maze[i][j] = myAbs(e_row - i) + myAbs(e_col - j);
            }
        }
    }

    int openlist[rows][columns];
    int closedlist[rows][columns];

    printf("\nHeuristics Matrix : \n");
    for (int i = 0; i < rows; i++)
    {
        printf("----");
    }
    for (int i = 0; i < rows; i++)
    {
        printf("\n");
        for (int j = 0; j < columns; j++)
        {
            openlist[i][j] = INT_MAX_VALUE;
            closedlist[i][j] = 0;
            printf("%d | ", maze[i][j]);
        }
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            printf("----");
        }
    }
    printf("\n");
    openlist[s_row][s_col] = maze[s_row][s_col];
    int r_mat[] = {0, 0, 1, -1};
    int c_mat[] = {1, -1, 0, 0};
    int x = rows * columns;
    while (x--)
    {
        int Min = INT_MAX_VALUE;
        int r = 0, c = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (Min > openlist[i][j] && closedlist[i][j] == 0)
                {
                    Min = openlist[i][j];
                    r = i;
                    c = j;
                }
            }
        }
        printf("Current coordinates: %d %d\n", r, c);
        if (r == e_row && c == e_col)
        {
            printf("Coordinates Found!!");
            return 0;
        }
        openlist[r][c] = INT_MAX_VALUE;
        closedlist[r][c] = 1;
        for (int i = 0; i < 4; i++)
        {
            int n_r = r + r_mat[i];
            int n_c = c + c_mat[i];
            if (n_r >= 0 && n_r < rows && n_c >= 0 && n_c < columns && maze[n_r][n_c] != -1)
            {
                openlist[n_r][n_c] = maze[n_r][n_c];
            }
        }
    }
    printf("Did not find any path!!");
    return 0;
}
