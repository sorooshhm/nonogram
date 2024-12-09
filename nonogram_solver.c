// Soroosh Hamedifar; 40310HINT877
#include <stdio.h>
#define SIZE 30
#define HINT 10

void input(int[][HINT], int[][HINT], int, int);
void initializeArr(int[][HINT], int);
int validateRow(int r);
int isValidCol(int c, int r);
int solve(int r, int c, int index);

int rows, columns;
int arr[SIZE][SIZE];
int columnsHint[SIZE][HINT];
int rowsHint[SIZE][HINT];

int main()
{
    scanf("%d %d", &rows, &columns);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            arr[i][j] = 0;
        }
    }

    initializeArr(columnsHint, columns);
    initializeArr(rowsHint, rows);
    input(rowsHint, columnsHint, rows, columns);
    printf("Start !!\n");

    int res = solve(0, 0, 0);
    printf("res is : %d \n", res);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf(arr[i][j] ? "EE" : "  ");
        }
        printf("\n");
    }
    return 0;
}

void initializeArr(int hints[][HINT], int size)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < HINT; j++)
        {
            hints[i][j] = 0;
        }
    }
}

void input(int rowsHint[][HINT], int columnsHint[][HINT], int n, int m)
{
    int index = 0;
    while (n--)
    {
        int k;
        scanf("%d ", &k);
        for (int i = 0; i < k; i++)
        {
            scanf("%d", &rowsHint[index][i]);
        }
        index++;
    }
    index = 0;
    while (m--)
    {
        int k;
        scanf("%d ", &k);
        for (int i = 0; i < k; i++)
        {
            scanf("%d", &columnsHint[index][i]);
        }
        index++;
    }
};

int validateRow(int r)
{
    int index = 0;
    int filled = 0;
    int state = 0;
    for (int i = 0; i < columns; i++)
    {
        if (arr[r][i])
        {
            filled++;
            state = 1;
        }
        if (arr[r][i + 1] == 0 && state)
        {
            if (!rowsHint[r][index])
                break;
            if (filled != rowsHint[r][index])
                return 0;
            else
            {
                filled = 0;
                state = 0;
                index++;
            }
        }
    }

    if (index == 0 || (filled > 0) || rowsHint[r][index])
    {
        return 0;
    }
    return 1;
}

int isValidCol(int c, int r)
{
    int filled = 0;
    int index = 0;
    int state = 0;
    for (int i = 0; i <= r; i++)
    {
        if (arr[i][c])
        {
            filled++;
            state = 1;
        }
        else
        {
            state = 0;
        }
        if (filled && !state)
        {
            if (filled != columnsHint[c][index])
            {
                return 0;
            }
            // printf("Yesssss\n");
            filled = 0;
            state = 0;
            index++;
        }
    }
    if (filled > columnsHint[c][index])
        return 0;
    return 1;
}

int solve(int r, int c, int index)
{
    if (r == rows)
    {
        return 1;
    }
    if (c == columns)
    {
        if (!validateRow(r))
        {
            return 0;
        }
        return solve(r + 1, 0, 0);
    }
    int h = rowsHint[r][index];
    if (c + h > columns)
    {
        return 0;
    }
    if (h)
    {
        if (arr[r][c - 1] == 0)
        {
            int check = 1;
            for (int i = 0; i < h; i++)
            {
                arr[r][c + i] = 1;
                if (!isValidCol(c + i, r))
                {
                    check = 0;
                    break;
                }
            }
            if (check && solve(r, c + h, index + 1))
            {
                return 1;
            }
        }
    }
    for (int i = 0; i < h; i++)
    {
        arr[r][c + i] = 0;
    }
    if (solve(r, c + 1, index) && isValidCol(c, r))
    {
        return 1;
    }
    return 0;
}