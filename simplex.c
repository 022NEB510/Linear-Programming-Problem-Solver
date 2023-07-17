#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char objective_function[100];
char first_constraint[100];
char second_constraint[100];

char keyword[4];
int operation;
int i;
int period;
char a[10] = "";
char b[10] = "";
char ovar;
char fvar;
char svar;
char rhs[10] = "";
int count_a;
int count_b;
int count_rhs;

int row1[6];
int row2[6];
int row3[6];

void objective_function_extraction(char expression[]);
void constraint_extraction(char expression[]);
void simplex_calculation();
void intarr_to_floatarr(int iarray[], float farray[]);

int main()
{
    printf("This is an app for solving Linear Programming Problems of Maximization and Minimization developed by Vinit Baral.\n--------------------------\n");
    printf("Enter the objective function: ");
    scanf("%[^ ] %[^\n]", keyword, objective_function);
    printf("Enter the first constraint: ");
    scanf(" %[^\n]", first_constraint);
    printf("Enter the second constraint: ");
    scanf(" %[^\n]", second_constraint);

    if (strncmp(keyword, "Max", 3) == 0)
    {
        operation = 1;
    }
    else if (strncmp(keyword, "Min", 3) == 0)
    {
        operation = 0;
    }
    else
    {
        printf("\nEnter the objective function correctly: ");
    }

    objective_function_extraction(objective_function);
    row3[0] = atoi(a) * -1;
    row3[1] = atoi(b) * -1;
    row3[2] = 0;
    row3[3] = 0;
    row3[4] = 1;
    row3[5] = 0;
    char fvar3 = fvar;
    char svar3 = svar;
    constraint_extraction(first_constraint);
    row1[0] = atoi(a);
    row1[1] = atoi(b);
    row1[2] = 1;
    row1[3] = 0;
    row1[4] = 0;
    row1[5] = atoi(rhs);
    char fvar2 = fvar;
    char svar2 = svar;
    constraint_extraction(second_constraint);
    row2[0] = atoi(a);
    row2[1] = atoi(b);
    row2[2] = 0;
    row2[3] = 1;
    row2[4] = 0;
    row2[5] = atoi(rhs);
    char fvar1 = fvar;
    char svar1 = svar;
    if (operation == 0)
    {
        int temp; // for transpose
        temp = row1[1];
        row1[1] = row2[0];
        row2[0] = temp;
        temp = row2[5];
        row2[5] = row3[1];
        row3[1] = temp;
        temp = row3[0];
        row3[0] = row1[5];
        row1[5] = temp;
        row3[0] *= -1;
        row3[1] *= -1;
        row1[5] *= -1;
        row2[5] *= -1;
    }
    if (operation == 1 || operation == 0)
    {
        if ((fvar1 == fvar2 && fvar2 == fvar3) && (svar1 == svar2 && svar2 == svar3))
        {
            simplex_calculation();
        }
        else
        {
            printf("\n Wrong INPUT FROM USER !!!!!!");
        }
    }
}

void objective_function_extraction(char expression[])
{
    i = 0;
    period = 0;
    count_a = 0;
    count_b = 0;
    count_rhs = 0;
    char temp_a[10] = "";
    char temp_b[10] = "";
    while (expression[i] != '\0')
    {

        if (expression[i] >= 'A' && expression[i] <= 'Z' && period == 0)
        {
            ovar = expression[i];
            period = 1;
        }
        else if (expression[i] == '=')
        {
            period = 2;
        }
        else if (((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '-') && period == 2)
        {
            temp_a[count_a] = expression[i];
            count_a++;
        }
        else if (expression[i] >= 'a' && expression[i] <= 'z' && period == 2)
        {
            fvar = expression[i];
            period = 3;
        }
        else if (((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '-') && period == 3)
        {
            temp_b[count_b] = expression[i];
            count_b++;
        }
        else if (expression[i] >= 'a' && expression[i] <= 'z' && period == 3)
        {
            svar = expression[i];
        }
        i++;
    }
    strcpy(a, temp_a);
    strcpy(b, temp_b);
}

void constraint_extraction(char expression[])
{
    i = 0;
    period = 0;
    count_a = 0;
    count_b = 0;
    count_rhs = 0;
    char temp_a[10] = "";
    char temp_b[10] = "";
    while (expression[i] != '\0')
    {
        if (((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '-') && period == 0)
        {
            temp_a[count_a] = expression[i];
            count_a++;
        }
        else if (expression[i] >= 'a' && expression[i] <= 'z' && period == 0)
        {
            fvar = expression[i];
            period = 1;
        }
        else if (expression[i] >= 'a' && expression[i] <= 'z' && period == 1)
        {
            svar = expression[i];
            period = 2;
        }
        else if (((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '-') && period == 1)
        {
            temp_b[count_b] = expression[i];
            count_b++;
        }
        else if (expression[i] == '<' || expression[i] == '>')
        {
            period = 3;
        }
        else if (((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '-') && period == 3)
        {
            rhs[count_rhs] = expression[i];
            count_rhs++;
        }
        i++;
    }
    strcpy(a, temp_a);
    strcpy(b, temp_b);
}

void intarr_to_floatarr(int iarray[], float farray[])
{
    for (int i = 0; i <= 5; i++)
    {
        farray[i] = (float)iarray[i];
    }
}

void simplex_calculation()
{
    int update_on_x = 0;
    int update_on_y = 0;
    float frow1[5];
    float frow2[5];
    float frow3[5];
    intarr_to_floatarr(row1, frow1);
    intarr_to_floatarr(row2, frow2);
    intarr_to_floatarr(row3, frow3);
    float value_of_x = 0;
    float value_of_y = 0;
    while (frow3[0] < 0 || frow3[1] < 0)
    {
        if (frow3[0] <= frow3[1])
        { // C1 being the pivot column
            if (frow1[5] / frow1[0] <= frow2[5] / frow2[0])
            { // R1 being the pivot row
                float divisor = frow1[0];
                float first_magic_factor = frow2[0] * -1;
                float second_magic_factor = frow3[0] * -1;
                for (int i = 0; i <= 5; i++)
                {
                    frow1[i] = frow1[i] / divisor;
                    frow2[i] = frow2[i] + first_magic_factor * frow1[i];
                    frow3[i] = frow3[i] + second_magic_factor * frow1[i];
                }
                value_of_x = frow1[5];
                update_on_x = 1;
                if (update_on_y)
                {
                    value_of_y += first_magic_factor * value_of_x;
                }
            }
            else
            { // R2 being the pivot Row
                float divisor = frow2[0];
                float first_magic_factor = frow1[0] * -1;
                float second_magic_factor = frow3[0] * -1;
                for (int i = 0; i <= 5; i++)
                {
                    frow2[i] = frow2[i] / divisor;
                    frow1[i] = frow1[i] + first_magic_factor * frow2[i];
                    frow3[i] = frow3[i] + second_magic_factor * frow2[i];
                }
                value_of_x = frow2[5];
                update_on_x = 1;
                if (update_on_y)
                {
                    value_of_y += first_magic_factor * value_of_x;
                }
            }
        }
        else
        { // C2 being the pivot column
            if (frow1[5] / frow1[1] <= frow2[5] / frow2[1])
            { // R1 being the pivot row
                float divisor = frow1[1];
                float first_magic_factor = frow2[1] * -1;
                float second_magic_factor = frow3[1] * -1;
                for (int i = 0; i <= 5; i++)
                {
                    frow1[i] = frow1[i] / divisor;
                    frow2[i] = frow2[i] + first_magic_factor * frow1[i];
                    frow3[i] = frow3[i] + second_magic_factor * frow1[i];
                }
                value_of_y = frow1[5];
                update_on_y = 1;
                if (update_on_x)
                {
                    value_of_x += first_magic_factor * value_of_y;
                }
            }
            else
            { // R2 being the pivot Row
                float divisor = frow2[1];
                float first_magic_factor = frow1[1] * -1;
                float second_magic_factor = frow3[1] * -1;
                for (int i = 0; i <= 5; i++)
                {
                    frow2[i] = frow2[i] / divisor;
                    frow1[i] = frow1[i] + first_magic_factor * frow2[i];
                    frow3[i] = frow3[i] + second_magic_factor * frow2[i];
                }
                value_of_y = frow2[5];
                update_on_y = 1;
                if (update_on_x)
                {
                    value_of_x += first_magic_factor * value_of_y;
                }
            }
        }
    }
    printf("\n-----------\n");
    if (operation)
    {
        printf("\nThe Maximum Value of %c is %.2f at %c = %.2f and %c = %.2f !", ovar, frow3[5], fvar, value_of_x, svar, value_of_y);
    }
    else
    {
        printf("\nThe Minimum Value of %c is %.2f at %c = %.2f and %c = %.2f !", ovar, frow3[5], fvar, frow3[2], svar, frow3[3]);
    }
}
