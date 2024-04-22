#include <stdio.h>

int flag[] = {0,0};
int indexm[][3] = {{9,9,9},{9,9,9},{9,9,9}};
int cost_mat[][3] = {{0,0,0},{0,0,0},{0,0,0}};
int path_matrix[8][3];
int flag_draw = 0;
int matrix_drawing_flag = 0;
int flag_extreme = 0;
int path_cost=0, min_path_cost, max_path_cost;
int min_path_number, max_path_number;
int i,j,k;
int person_chance=0;
int position;
int blankColumn, blankRow, row, column;
int flagBlank = 0;

void chancePerson()
{
    person_chance = 1;
    place(position);
}

void place(int pos)
{
        if(pos>9 || pos<1)
        {
            printf("Position out of bound... please put position b/w 1-9\n");
            person_chance = 0;
            return;
        }
        column = (pos - 1) % 3;
        row = (pos - 1) / 3;
        int pos_value = indexm[row][column];
        if(pos_value != 9|| pos_value == 0 || pos_value == 1)
        {
            printf("Sorry ... You can't place the X here !\n");
            person_chance = 0;

        }
        else
        {
            indexm[row][column] = 1;
            // chance[1] = 0;
        }
}

int isWinningAI() //AI is winning
{
    if(indexm[0][0]+indexm[1][0]+indexm[2][0] == 0 || indexm[0][1]+indexm[1][1]+indexm[2][1] == 0 || indexm[0][2]+indexm[1][2]+indexm[2][2] == 0)
    {
        //return 1;
        flag[0] = 1;
    }
    if(indexm[0][0]+indexm[0][1]+indexm[0][2] == 0 || indexm[1][0]+indexm[1][1]+indexm[1][2] == 0 || indexm[2][0]+indexm[2][1]+indexm[2][2] == 0)
    {
        //return 1;
        flag[0] = 1;
    }
    if(indexm[0][0]+indexm[1][1]+indexm[2][2] == 0 || indexm[0][2]+indexm[1][1]+indexm[2][0] == 0)
    {
        //return 1;
        flag[0] = 1;
    }

    if(flag[0])return 1;
    else return 0;
}

int isWinningPerson()
{
        if(indexm[0][0]+indexm[1][0]+indexm[2][0] == 3 || indexm[0][1]+indexm[1][1]+indexm[2][1] == 3 || indexm[0][2]+indexm[1][2]+indexm[2][2] == 3)
    {
        //return 1;
        flag[1] = 1;
    }
    if(indexm[0][0]+indexm[0][1]+indexm[0][2] == 3 || indexm[1][0]+indexm[1][1]+indexm[1][2] == 3 || indexm[2][0]+indexm[2][1]+indexm[2][2] == 3)
    {
        //return 1;
        flag[1] = 1;
    }
    if(indexm[0][0]+indexm[1][1]+indexm[2][2] == 3 || indexm[0][2]+indexm[1][1]+indexm[2][0] == 3)
    {
        //return 1;
        flag[1] = 1;
    }

    if(flag[1])return 1;
    else return 0;
}

int isDraw()
{
    if(!isWinningAI() || !isWinningPerson())
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(indexm[i][j] == 9)
                {
                    flag_draw = 0;
                    break;
                }
                else
                {
                    flag_draw = 1;
                }
            }
            if(!flag_draw)
            {
                break;
            }
        }
    }
    if(flag_draw)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void goAI()
{
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            path_cost += cost_mat[i][j];
            if(indexm[i][j] == 9 && flagBlank != 1)
            {
                blankRow = i;
                blankColumn = j;
                flagBlank = 1;
            }
        }
        path_matrix[k][0] = path_cost;
        path_matrix[k][1] = blankRow;
        path_matrix[k][2] = blankColumn;
        //printf("Path cost at path %d is %d\n", k, path_cost);
        flagBlank = 0;
        path_cost = 0;
        k++;
    }

    for(j=0; j<3; j++)
    {
        for(i=0; i<3; i++)
        {
            path_cost += cost_mat[i][j];
            if(indexm[i][j] == 9 && flagBlank != 1)
            {
                blankRow = i;
                blankColumn = j;
                flagBlank = 1;
            }
        }
        path_matrix[k][0] = path_cost;
        path_matrix[k][1] = blankRow;
        path_matrix[k][2] = blankColumn;
       // printf("Path cost at path %d is %d\n", k, path_cost);
       flagBlank = 0;
        path_cost = 0;
        k++;
    }

    for(i=0; i<3; i++)
    {
        path_cost += cost_mat[i][i];
        if(indexm[i][i] == 9 && flagBlank != 1)
        {
            blankRow = blankColumn = i;
            flagBlank = 1;
        }
        path_matrix[k][0] = path_cost;
        path_matrix[k][1] = blankRow;
        path_matrix[k][2] = blankColumn;

    }
    //printf("Path cost at path %d is %d\n", k, path_cost);
    flagBlank = 0;
    path_cost = 0;
    k++;
    for(i=0; i<3; i++)
    {
        path_cost += cost_mat[2-i][i];
        if(indexm[2-i][i] == 9 && flagBlank != 1)
        {
            blankRow = 2-i;
            blankColumn = i;
            flagBlank = 1;
        }
        path_matrix[k][0] = path_cost;
        path_matrix[k][1] = blankRow;
        path_matrix[k][2] = blankColumn;

    }
    //printf("Path cost at path %d is %d\n", k, path_cost);
    flagBlank = 0;
    path_cost = 0;
    k=0;

    // FOR LOOP FOR MINIMUM COST AND BLANK SPOTS AT THAT PATH
    for(k=0; k<8; k++)
    {
        if(k==0)
        {
            min_path_cost = path_matrix[k][0];
        }
        if(path_matrix[k][0] <= min_path_cost)
        {
            min_path_cost = path_matrix[k][0];
            min_path_number = k;
        }
    }

    // FOR LOOP FOR MAXIMUM COST AND BLANK SPOTS AT THAT PATH
    for(k=0; k<8; k++)
    {
        if(k==0)
        {
            max_path_cost = path_matrix[k][0];
        }
        if(path_matrix[k][0] >= max_path_cost) //greater than or equal to just becuase k is still 0 in first iteration
        {
            max_path_cost = path_matrix[k][0];
            max_path_number = k;
        }

    }
    k=0;


    //printf("Minimum path number = %d, Maximum path number = %d, Minimum path cost = %d, Maximum path cost = %d\n\n", min_path_number, max_path_number, min_path_cost, max_path_cost);
    //printf("Min Blank row = %d, Min blank column = %d, Max blank row = %d, Max blank row = %d\n", path_matrix[min_path_number][1], path_matrix[min_path_number][2], path_matrix[max_path_number][1], path_matrix[max_path_number][2]);
    if(!flag_extreme)
    {
        if(min_path_cost + max_path_cost == 0)
        {
            indexm[path_matrix[min_path_number][1]][path_matrix[min_path_number][2]] = 0;
        }
        if(max_path_cost + min_path_cost > 0)
        {
            indexm[path_matrix[max_path_number][1]][path_matrix[max_path_number][2]] = 0;
        }
        if(min_path_cost + max_path_cost < 0)
        {
            indexm[path_matrix[min_path_number][1]][path_matrix[min_path_number][2]] = 0;
        }
    }
    flag_extreme = 0;

}

void costMatrix()
{
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            // If triangulation has already happened
            if((indexm[0][0]==1 && indexm[2][0]==1 && indexm[2][2]) || (indexm[0][2]==1 && indexm[2][2]==1 && indexm[2][0]))
            {
                flag_extreme = 0;
            }
            // Defying advantage of corner
            else if(((i==0 && j==0) || (i==0 && j==2) || (i==2 && j==0) || (i==2 && j==2))&& indexm[1][1] == 9)
            {
                flag_extreme = 1;
                indexm[1][1] = 0;
            }
            // Avoiding triangulation
            else if((indexm[0][0]==1 && indexm[2][2]==1) && indexm[0][1] == 9)
            {
                flag_extreme = 1;
                indexm[0][1] = 0;
            }
            //Avoiding triangulatoin
            else if((indexm[0][2]==1 && indexm[2][0]==1) && indexm[0][1] == 9)
            {
                flag_extreme = 1;
                indexm[0][1] = 0;
            }

            // Cost assignment to each cell
            if(indexm[i][j]==0)
            {
                cost_mat[i][j] = -1;
            }
            if(indexm[i][j]==1)
            {
                cost_mat[i][j] = 1;
            }
            else if(indexm[i][j]==9)
            {
                cost_mat[i][j] = 0;
            }

        }
    }
}

void drawMatrix()
{
   if(matrix_drawing_flag)
    {
         for(int i = 0; i < 3; i++)
        {
            printf("|");
            for(int j = 0; j < 3; j++)
            {
                if(indexm[i][j] == 0)
                {
                    printf(" O |");
                }
                else if(indexm[i][j] == 1)
                {
                    printf(" X |");
                }
                else
                {
                printf("   |");
                }
            }
            printf("\n\n");
        }
    }
    else
    {
        int pos_counter = 1;
        for(int i = 0; i < 3; i++)
        {
            printf("|");
            for(int j = 0; j < 3; j++)
            {
                printf(" %d |", pos_counter);
                pos_counter++;
            }
            printf("\n\n");
        }
    }

}

void main()
{
    printf("WELCOME TO TIC TAC TOE, YOU ARE PLAYING AGAINST A VIRTUAL AI ENABLED AGENT 'BATMAN'\n\n");
    printf("BATMAN DARES YOU TO WIN !\n\n");
    drawMatrix();
    while(!isWinningAI() || !isWinningAI() || !isDraw)
    {
        matrix_drawing_flag = 1;
        while(person_chance != 1)
        {
            printf("PERSON.... please enter the position where you want to place X: - ");
            scanf("%d", &position);
            chancePerson();
        }
        drawMatrix();
        person_chance = 0;

        if(isWinningAI())
        {
            printf("THE AI HAS WON !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            break;
        }
        if(isWinningPerson())
        {
            printf("THE PERSON HAS WON !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            break;
        }
        if(isDraw())
        {
            printf("THE MATCH IS DRAW !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            break;
        }

        printf("Now its chance for the AI\n");

        costMatrix();
        k=0;
        goAI();
        drawMatrix();

        if(isWinningAI())
        {
            printf("THE AI HAS WON !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            break;
        }
        if(isWinningPerson())
        {
            printf("THE PERSON HAS WON !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            break;
        }
        if(isDraw())
        {
            printf("THE MATCH IS DRAW !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            break;
        }


    }
}