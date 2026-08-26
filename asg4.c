#include <stdio.h>

void bucketSort(float a[], int n)
{
    float bucket[10][100];
    int count[10] = {0};
    int i, j, k;
    float temp;

    for (i = 0; i < n; i++)
    {
        k = (int)a[i] / 10;
        if (k == 10)
            k = 9;
        bucket[k][count[k]++] = a[i];
    }

    for (i = 0; i < 10; i++)
    {
        for (j = 1; j < count[i]; j++)
        {
            temp = bucket[i][j];
            k = j - 1;

            while (k >= 0 && bucket[i][k] > temp)
            {
                bucket[i][k + 1] = bucket[i][k];
                k--;
            }

            bucket[i][k + 1] = temp;
        }
    }

    k = 0;

    for (i = 0; i < 10; i++)
        for (j = 0; j < count[i]; j++)
            a[k++] = bucket[i][j];
}

int main()
{
    float a[100];
    int n, i;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("Enter percentages:\n");
    for (i = 0; i < n; i++)
        scanf("%f", &a[i]);

    bucketSort(a, n);

    printf("\nSorted percentages:\n");
    for (i = 0; i < n; i++)
        printf("%.2f ", a[i]);

    printf("\n\nTop Five Scores:\n");

    for (i = n - 1; i >= 0 && i >= n - 5; i--)
        printf("%.2f\n", a[i]);

    return 0;
}