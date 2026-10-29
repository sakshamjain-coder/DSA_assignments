#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

char expStack[MAX][MAX];
int etop = -1;

int prec(char c)
{
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int isOp(char c)
{
    return c == '+' || c == '-' ||
           c == '*' || c == '/' || c == '^';
}

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}

void pushExp(char s[])
{
    strcpy(expStack[++etop], s);
}

void popExp(char s[])
{
    strcpy(s, expStack[etop--]);
}

/* Infix to Postfix */
void infixToPostfix(char in[], char out[])
{
    int i, j = 0;
    char c;
    top = -1;

    for (i = 0; in[i]; i++)
    {
        c = in[i];

        if (isalnum((unsigned char)c))
            out[j++] = c;

        else if (c == '(')
            push(c);

        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
                out[j++] = pop();

            if (top != -1) pop();
        }

        else if (isOp(c))
        {
            while (top != -1 && stack[top] != '(' &&
                  (prec(stack[top]) > prec(c) ||
                  (prec(stack[top]) == prec(c) && c != '^')))
                out[j++] = pop();

            push(c);
        }
    }

    while (top != -1)
        out[j++] = pop();

    out[j] = '\0';
}

/* Postfix to Prefix */
void postfixToPrefix(char in[], char out[])
{
    int i;
    char a[MAX], b[MAX], t[MAX];

    etop = -1;

    for (i = 0; in[i]; i++)
    {
        if (isalnum((unsigned char)in[i]))
        {
            t[0] = in[i];
            t[1] = '\0';
            pushExp(t);
        }
        else if (isOp(in[i]))
        {
            popExp(b);
            popExp(a);

            sprintf(t, "%c%s%s", in[i], a, b);
            pushExp(t);
        }
    }

    popExp(out);
}

/* Prefix to Postfix */
void prefixToPostfix(char in[], char out[])
{
    int i;
    char a[MAX], b[MAX], t[MAX];

    etop = -1;

    for (i = strlen(in) - 1; i >= 0; i--)
    {
        if (isalnum((unsigned char)in[i]))
        {
            t[0] = in[i];
            t[1] = '\0';
            pushExp(t);
        }
        else if (isOp(in[i]))
        {
            popExp(a);
            popExp(b);

            sprintf(t, "%s%s%c", a, b, in[i]);
            pushExp(t);
        }
    }

    popExp(out);
}

/* Postfix to Infix */
void postfixToInfix(char in[], char out[])
{
    int i;
    char a[MAX], b[MAX], t[MAX];

    etop = -1;

    for (i = 0; in[i]; i++)
    {
        if (isalnum((unsigned char)in[i]))
        {
            t[0] = in[i];
            t[1] = '\0';
            pushExp(t);
        }
        else if (isOp(in[i]))
        {
            popExp(b);
            popExp(a);

            sprintf(t, "(%s%c%s)", a, in[i], b);
            pushExp(t);
        }
    }

    popExp(out);
}

/* Infix to Prefix */
void infixToPrefix(char in[], char out[])
{
    char post[MAX];

    infixToPostfix(in, post);
    postfixToPrefix(post, out);
}

/* Prefix to Infix */
void prefixToInfix(char in[], char out[])
{
    char post[MAX];

    prefixToPostfix(in, post);
    postfixToInfix(post, out);
}

int main()
{
    int choice;
    char in[MAX], out[MAX];

    do
    {
        printf("\n1. Infix to Postfix\n");
        printf("2. Infix to Prefix\n");
        printf("3. Prefix to Infix\n");
        printf("4. Prefix to Postfix\n");
        printf("5. Postfix to Infix\n");
        printf("6. Postfix to Prefix\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6)
        {
            printf("Enter expression: ");
            scanf("%99s", in);
        }

        switch (choice)
        {
            case 1:
                infixToPostfix(in, out);
                printf("Postfix: %s\n", out);
                break;

            case 2:
                infixToPrefix(in, out);
                printf("Prefix: %s\n", out);
                break;

            case 3:
                prefixToInfix(in, out);
                printf("Infix: %s\n", out);
                break;

            case 4:
                prefixToPostfix(in, out);
                printf("Postfix: %s\n", out);
                break;

            case 5:
                postfixToInfix(in, out);
                printf("Infix: %s\n", out);
                break;

            case 6:
                postfixToPrefix(in, out);
                printf("Prefix: %s\n", out);
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}