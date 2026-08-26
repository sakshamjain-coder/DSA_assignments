#include <stdio.h>

int main()
{
    int a[10][10], sparse[100][3], transpose[100][3], fastTranspose[100][3];
    int rows, cols, i, j, k, n;
    int count[100], position[100];

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &rows, &cols);

    printf("Enter elements of the matrix:\n");
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &a[i][j]);

    n = 0;

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (a[i][j] != 0)
            {
                n++;
                sparse[n][0] = i;
                sparse[n][1] = j;
                sparse[n][2] = a[i][j];
            }

    sparse[0][0] = rows;
    sparse[0][1] = cols;
    sparse[0][2] = n;

    printf("\nSparse Matrix (Triplet Form):\n");
    for (i = 0; i <= n; i++)
        printf("%d %d %d\n", sparse[i][0], sparse[i][1], sparse[i][2]);

    /* Simple Transpose */
    transpose[0][0] = cols;
    transpose[0][1] = rows;
    transpose[0][2] = n;

    k = 1;

    for (j = 0; j < cols; j++)
        for (i = 1; i <= n; i++)
            if (sparse[i][1] == j)
            {
                transpose[k][0] = sparse[i][1];
                transpose[k][1] = sparse[i][0];
                transpose[k][2] = sparse[i][2];
                k++;
            }

    printf("\nTranspose:\n");
    for (i = 0; i <= n; i++)
        printf("%d %d %d\n", transpose[i][0], transpose[i][1], transpose[i][2]);

    /* Fast Transpose */
    fastTranspose[0][0] = cols;
    fastTranspose[0][1] = rows;
    fastTranspose[0][2] = n;

    for (i = 0; i < cols; i++)
        count[i] = 0;

    for (i = 1; i <= n; i++)
        count[sparse[i][1]]++;

    position[0] = 1;

    for (i = 1; i < cols; i++)
        position[i] = position[i - 1] + count[i - 1];

    for (i = 1; i <= n; i++)
    {
        j = sparse[i][1];
        k = position[j];

        fastTranspose[k][0] = sparse[i][1];
        fastTranspose[k][1] = sparse[i][0];
        fastTranspose[k][2] = sparse[i][2];

        position[j]++;
    }

    printf("\nFast Transpose:\n");
    for (i = 0; i <= n; i++)
        printf("%d %d %d\n", fastTranspose[i][0],
               fastTranspose[i][1], fastTranspose[i][2]);

    return 0;
}