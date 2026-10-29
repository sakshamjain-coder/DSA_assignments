#include <stdio.h>
#include <ctype.h>
#include <math.h>

int stack[50], top = -1;

int main() {
    char exp[100];
    int i, a, b;

    printf("Enter postfix: ");
    scanf("%99s", exp);

    for (i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i]))
            stack[++top] = exp[i] - '0';
        else {
            b = stack[top--];
            a = stack[top--];

            switch (exp[i]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
                case '^': stack[++top] = (int)pow(a, b); break;
            }
        }
    }

    printf("Value = %d\n", stack[top]);
    return 0;
}