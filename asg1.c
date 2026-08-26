#include <stdio.h>

int main()
{
    int choice, r1, c1, r2, c2, i, j, k;
    int a[10][10], b[10][10], result[10][10];

    printf("Matrix Operations\n");
    printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Transpose\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Enter rows and columns: ");
            scanf("%d%d", &r1, &c1);

            printf("Enter elements of first matrix:\n");
            for (i = 0; i < r1; i++)
                for (j = 0; j < c1; j++)
                    scanf("%d", &a[i][j]);

            printf("Enter elements of second matrix:\n");
            for (i = 0; i < r1; i++)
                for (j = 0; j < c1; j++)
                    scanf("%d", &b[i][j]);

            printf("Addition of matrices:\n");
            for (i = 0; i < r1; i++)
            {
                for (j = 0; j < c1; j++)
                    printf("%d ", a[i][j] + b[i][j]);
                printf("\n");
            }
            break;

        case 2:
            printf("Enter rows and columns: ");
            scanf("%d%d", &r1, &c1);

            printf("Enter elements of first matrix:\n");
            for (i = 0; i < r1; i++)
                for (j = 0; j < c1; j++)
                    scanf("%d", &a[i][j]);

            printf("Enter elements of second matrix:\n");
            for (i = 0; i < r1; i++)
                for (j = 0; j < c1; j++)
                    scanf("%d", &b[i][j]);

            printf("Subtraction of matrices:\n");
            for (i = 0; i < r1; i++)
            {
                for (j = 0; j < c1; j++)
                    printf("%d ", a[i][j] - b[i][j]);
                printf("\n");
            }
            break;

        case 3:
            printf("Enter rows and columns of first matrix: ");
            scanf("%d%d", &r1, &c1);

            printf("Enter elements of first matrix:\n");
            for (i = 0; i < r1; i++)
                for (j = 0; j < c1; j++)
                    scanf("%d", &a[i][j]);

            printf("Enter rows and columns of second matrix: ");
            scanf("%d%d", &r2, &c2);

            if (c1 != r2)
            {
                printf("Matrix multiplication not possible.");
                break;
            }

            printf("Enter elements of second matrix:\n");
            for (i = 0; i < r2; i++)
                for (j = 0; j < c2; j++)
                    scanf("%d", &b[i][j]);

            for (i = 0; i < r1; i++)
                for (j = 0; j < c2; j++)
                {
                    result[i][j] = 0;
                    for (k = 0; k < c1; k++)
                        result[i][j] += a[i][k] * b[k][j];
                }

            printf("Multiplication of matrices:\n");
            for (i = 0; i < r1; i++)
            {
                for (j = 0; j < c2; j++)
                    printf("%d ", result[i][j]);
                printf("\n");
            }
            break;

        case 4:
            printf("Enter rows and columns: ");
            scanf("%d%d", &r1, &c1);

            printf("Enter elements of matrix:\n");
            for (i = 0; i < r1; i++)
                for (j = 0; j < c1; j++)
                    scanf("%d", &a[i][j]);

            printf("Transpose of matrix:\n");
            for (j = 0; j < c1; j++)
            {
                for (i = 0; i < r1; i++)
                    printf("%d ", a[i][j]);
                printf("\n");
            }
            break;

        default:
            printf("Invalid choice.");
    }

    return 0;
}