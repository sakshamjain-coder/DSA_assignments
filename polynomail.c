#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int coeff;
    int exp;
    struct Node *next;
};

typedef struct Node Node;

Node *createNode(int coeff, int exp)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;

    return newNode;
}

Node *insertTerm(Node *head, int coeff, int exp)
{
    Node *newNode, *temp, *prev;

    if (coeff == 0)
        return head;

    if (head == NULL)
        return createNode(coeff, exp);

    temp = head;
    prev = NULL;

    do
    {
        if (temp->exp == exp)
        {
            temp->coeff += coeff;

            if (temp->coeff == 0)
            {
                if (temp->next == temp)
                {
                    free(temp);
                    return NULL;
                }

                if (temp == head)
                {
                    prev = head;

                    while (prev->next != head)
                        prev = prev->next;

                    head = head->next;
                    prev->next = head;
                    free(temp);
                    return head;
                }

                prev->next = temp->next;
                free(temp);
            }

            return head;
        }

        if (temp->exp < exp)
            break;

        prev = temp;
        temp = temp->next;

    } while (temp != head);

    newNode = createNode(coeff, exp);

    if (temp == head && exp > head->exp)
    {
        newNode->next = head;

        prev = head;
        while (prev->next != head)
            prev = prev->next;

        prev->next = newNode;
        return newNode;
    }

    newNode->next = temp;

    if (prev != NULL)
        prev->next = newNode;

    return head;
}

Node *createPolynomial()
{
    Node *head = NULL;
    int n, i, coeff, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coeff, &exp);

        if (exp < 0)
        {
            printf("Exponent must be non-negative.\n");
            i--;
            continue;
        }

        head = insertTerm(head, coeff, exp);
    }

    return head;
}

void displayPolynomial(Node *head)
{
    Node *temp;
    int first = 1;
    long long c;

    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    temp = head;

    do
    {
        c = temp->coeff;

        if (!first)
        {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        }
        else if (c < 0)
        {
            printf("-");
        }

        if (c < 0)
            c = -c;

        if (temp->exp == 0)
        {
            printf("%lld", c);
        }
        else
        {
            if (c != 1)
                printf("%lld", c);

            printf("x");

            if (temp->exp != 1)
                printf("^%d", temp->exp);
        }

        first = 0;
        temp = temp->next;

    } while (temp != head);

    printf("\n");
}

Node *addPolynomial(Node *p1, Node *p2)
{
    Node *result = NULL;
    Node *temp;

    if (p1 != NULL)
    {
        temp = p1;

        do
        {
            result = insertTerm(result,
                                temp->coeff,
                                temp->exp);

            temp = temp->next;

        } while (temp != p1);
    }

    if (p2 != NULL)
    {
        temp = p2;

        do
        {
            result = insertTerm(result,
                                temp->coeff,
                                temp->exp);

            temp = temp->next;

        } while (temp != p2);
    }

    return result;
}

void freePolynomial(Node *head)
{
    Node *temp, *next;

    if (head == NULL)
        return;

    temp = head->next;

    while (temp != head)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }

    free(head);
}

int main()
{
    Node *p1 = NULL;
    Node *p2 = NULL;
    Node *sum = NULL;
    int choice;

    do
    {
        printf("\n--- POLYNOMIAL OPERATIONS ---\n");
        printf("1. Create First Polynomial\n");
        printf("2. Create Second Polynomial\n");
        printf("3. Display Polynomials\n");
        printf("4. Add Polynomials\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                freePolynomial(p1);
                p1 = createPolynomial();
                printf("First polynomial: ");
                displayPolynomial(p1);
                break;

            case 2:
                freePolynomial(p2);
                p2 = createPolynomial();
                printf("Second polynomial: ");
                displayPolynomial(p2);
                break;

            case 3:
                printf("P1(x) = ");
                displayPolynomial(p1);

                printf("P2(x) = ");
                displayPolynomial(p2);
                break;

            case 4:
                freePolynomial(sum);
                sum = addPolynomial(p1, p2);

                printf("Sum = ");
                displayPolynomial(sum);
                break;

            case 5:
                freePolynomial(p1);
                freePolynomial(p2);
                freePolynomial(sum);

                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}