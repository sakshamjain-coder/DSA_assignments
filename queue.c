#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

void addJob()
{
    int job;

    if (rear == MAX - 1)
    {
        printf("Queue Overflow!\n");
        return;
    }

    printf("Enter job ID: ");
    scanf("%d", &job);

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = job;

    printf("Job added successfully\n");
}

void deleteJob()
{
    if (front == -1 || front > rear)
    {
        printf("Queue Underflow!\n");
        return;
    }

    printf("Job %d processed successfully\n", queue[front]);
    front++;

    if (front > rear)
    {
        front = rear = -1;
    }
}

void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Pending jobs: ");

    for (i = front; i <= rear; i++)
    {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- JOB QUEUE MENU ---\n");
        printf("1. Add Job\n");
        printf("2. Delete Job\n");
        printf("3. Display Jobs\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addJob();
                break;

            case 2:
                deleteJob();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}