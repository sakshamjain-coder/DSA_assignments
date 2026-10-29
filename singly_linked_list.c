#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int prn;
    char name[50];
    struct Node *next;
};

typedef struct Node Node;


Node *createNode(int prn, char name[])
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    return newNode;
}


Node *addPresident(Node *head, int prn, char name[])
{
    Node *newNode = createNode(prn, name);

    newNode->next = head;
    head = newNode;

    printf("President added successfully.\n");
    return head;
}


Node *addSecretary(Node *head, int prn, char name[])
{
    Node *newNode = createNode(prn, name);
    Node *temp;

    if (head == NULL)
        return newNode;

    temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;

    printf("Secretary added successfully.\n");
    return head;
}


Node *addMember(Node *head, int prn, char name[])
{
    Node *newNode = createNode(prn, name);
    Node *temp;

    if (head == NULL)
    {
        printf("Add the president first.\n");
        free(newNode);
        return head;
    }

    if (head->next == NULL)
    {
        head->next = newNode;
    }
    else
    {
        temp = head;

        while (temp->next->next != NULL)
            temp = temp->next;

        newNode->next = temp->next;
        temp->next = newNode;
    }

    printf("Member added successfully.\n");
    return head;
}


Node *deleteMember(Node *head, int prn)
{
    Node *temp = head;
    Node *prev = NULL;

    while (temp != NULL && temp->prn != prn)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Student not found.\n");
        return head;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Student deleted successfully.\n");
    return head;
}


void display(Node *head)
{
    Node *temp = head;

    if (head == NULL)
    {
        printf("No students registered.\n");
        return;
    }

    printf("\nPRN\tName\n");
    printf("----------------------\n");

    while (temp != NULL)
    {
        printf("%d\t%s\n", temp->prn, temp->name);
        temp = temp->next;
    }
}


int countMembers(Node *head)
{
    int count = 0;
    Node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}


void sortList(Node *head)
{
    Node *i, *j;
    int tempPRN;
    char tempName[50];

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->prn > j->prn)
            {
                tempPRN = i->prn;
                i->prn = j->prn;
                j->prn = tempPRN;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);
            }
        }
    }

    printf("List sorted by PRN.\n");
}

Node *reverseList(Node *head)
{
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    printf("List reversed successfully.\n");
    return prev;
}


Node *mergeLists(Node *head1, Node *head2)
{
    Node *temp;

    if (head1 == NULL)
        return head2;

    temp = head1;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = head2;

    return head1;
}

void freeList(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    Node *head2 = NULL;

    int choice, prn, n, i;
    char name[50];

    do
    {
        printf("\n===== PINNACLE CLUB =====\n");
        printf("1. Add President\n");
        printf("2. Add Regular Member\n");
        printf("3. Add Secretary\n");
        printf("4. Delete Member by PRN\n");
        printf("5. Display Members\n");
        printf("6. Count Members\n");
        printf("7. Sort by PRN\n");
        printf("8. Merge Two Lists\n");
        printf("9. Reverse List\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {
            case 1:
                printf("Enter President PRN: ");
                scanf("%d", &prn);

                printf("Enter President Name: ");
                scanf(" %49[^\n]", name);

                head = addPresident(head, prn, name);
                break;

            case 2:
                printf("Enter Member PRN: ");
                scanf("%d", &prn);

                printf("Enter Member Name: ");
                scanf(" %49[^\n]", name);

                head = addMember(head, prn, name);
                break;

            case 3:
                printf("Enter Secretary PRN: ");
                scanf("%d", &prn);

                printf("Enter Secretary Name: ");
                scanf(" %49[^\n]", name);

                head = addSecretary(head, prn, name);
                break;

            case 4:
                printf("Enter PRN to delete: ");
                scanf("%d", &prn);

                head = deleteMember(head, prn);
                break;

            case 5:
                display(head);
                break;

            case 6:
                printf("Total members: %d\n",
                       countMembers(head));
                break;

            case 7:
                sortList(head);
                display(head);
                break;

            case 8:
                printf("How many nodes in the second list? ");
                scanf("%d", &n);

                head2 = NULL;

                for (i = 0; i < n; i++)
                {
                    printf("Enter PRN: ");
                    scanf("%d", &prn);

                    printf("Enter Name: ");
                    scanf(" %49[^\n]", name);

                    head2 = addSecretary(head2, prn, name);
                }

                head = mergeLists(head, head2);
                head2 = NULL;

                printf("Lists merged successfully.\n");
                display(head);
                break;

            case 9:
                head = reverseList(head);
                display(head);
                break;

            case 10:
                freeList(head);
                head = NULL;

                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 10);

    return 0;
}