#include <stdio.h>

struct Student {
    int roll;
    char name[30];
    float marks;
};

void display(struct Student s[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d\t%s\t%.2f\n", s[i].roll, s[i].name, s[i].marks);
}

void linear(struct Student s[], int n, int key) {
    int i;
    for (i = 0; i < n; i++)
        if (s[i].roll == key) {
            printf("Found: %d %s %.2f\n",
                   s[i].roll, s[i].name, s[i].marks);
            return;
        }
    printf("Not Found\n");
}

void insertion(struct Student s[], int n) {
    int i, j;
    struct Student t;

    for (i = 1; i < n; i++) {
        t = s[i];
        j = i - 1;
        while (j >= 0 && s[j].roll > t.roll) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = t;
    }
}

void selection(struct Student s[], int n) {
    int i, j, min;
    struct Student t;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (s[j].roll < s[min].roll)
                min = j;

        t = s[i];
        s[i] = s[min];
        s[min] = t;
    }
}

void shell(struct Student s[], int n) {
    int gap, i, j;
    struct Student t;

    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++) {
            t = s[i];
            for (j = i; j >= gap &&
                 s[j - gap].roll > t.roll; j -= gap)
                s[j] = s[j - gap];
            s[j] = t;
        }
}

void binary(struct Student s[], int n, int key) {
    int l = 0, h = n - 1, m;

    while (l <= h) {
        m = (l + h) / 2;

        if (s[m].roll == key) {
            printf("Found: %d %s %.2f\n",
                   s[m].roll, s[m].name, s[m].marks);
            return;
        }

        if (s[m].roll < key)
            l = m + 1;
        else
            h = m - 1;
    }
    printf("Not Found\n");
}

int main() {
    struct Student s[50];
    int n, i, ch, key;

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Roll, Name, Marks: ");
        scanf("%d %s %f",
              &s[i].roll, s[i].name, &s[i].marks);
    }

    do {
        printf("\n1.Display 2.Linear 3.Insertion");
        printf("\n4.Selection 5.Shell 6.Binary 7.Exit");
        printf("\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                display(s, n);
                break;

            case 2:
                printf("Roll: ");
                scanf("%d", &key);
                linear(s, n, key);
                break;

            case 3:
                insertion(s, n);
                display(s, n);
                break;

            case 4:
                selection(s, n);
                display(s, n);
                break;

            case 5:
                shell(s, n);
                display(s, n);
                break;

            case 6:
                shell(s, n);
                printf("Roll: ");
                scanf("%d", &key);
                binary(s, n, key);
                break;

            case 7:
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (ch != 7);

    return 0;
}