#include <stdio.h>
#include <stdlib.h>

/* Circular singly linked list with a header node.
   Terms are kept in descending order of exponent. */
typedef struct Node {
    int coef;
    int exp;
    struct Node *next;
} Node;

Node *createHeader(void) {
    Node *h = (Node *)malloc(sizeof(Node));
    h->coef = 0;
    h->exp = 0;      /* header is never treated as a term; we stop at head */
    h->next = h;
    return h;
}

/* Insert a term keeping descending order, combining like terms and
   removing the term if its coefficient becomes zero. */
void insertTerm(Node *head, int coef, int exp) {
    if (coef == 0) return;

    Node *prev = head;
    Node *cur = head->next;
    while (cur != head && cur->exp > exp) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != head && cur->exp == exp) {
        cur->coef += coef;
        if (cur->coef == 0) {
            prev->next = cur->next;
            free(cur);
        }
        return;
    }

    Node *n = (Node *)malloc(sizeof(Node));
    n->coef = coef;
    n->exp = exp;
    n->next = cur;
    prev->next = n;
}

void readPoly(Node *head) {
    int more, c, e;
    while (scanf("%d", &more) == 1 && more == 1) {
        if (scanf("%d %d", &c, &e) != 2) break;
        insertTerm(head, c, e);
    }
}

Node *addPoly(Node *a, Node *b) {
    Node *res = createHeader();
    Node *tail = res;
    Node *p = a->next, *q = b->next;

    while (p != a || q != b) {
        int c, e;
        if (q == b || (p != a && p->exp > q->exp)) {
            c = p->coef; e = p->exp; p = p->next;
        } else if (p == a || q->exp > p->exp) {
            c = q->coef; e = q->exp; q = q->next;
        } else {
            c = p->coef + q->coef; e = p->exp;
            p = p->next; q = q->next;
        }
        if (c != 0) {
            Node *n = (Node *)malloc(sizeof(Node));
            n->coef = c;
            n->exp = e;
            n->next = res;
            tail->next = n;
            tail = n;
        }
    }
    return res;
}

void printPoly(const char *label, Node *head) {
    printf("%s = ", label);
    if (head->next == head) {
        printf("0\n");
        return;
    }
    Node *t = head->next;
    int first = 1;
    while (t != head) {
        if (!first) printf(" ");
        printf("%+dx^%d", t->coef, t->exp);
        first = 0;
        t = t->next;
    }
    printf("\n");
}

void freePoly(Node *head) {
    Node *t = head->next;
    while (t != head) {
        Node *nx = t->next;
        free(t);
        t = nx;
    }
    free(head);
}

int main(void) {
    Node *p1 = createHeader();
    Node *p2 = createHeader();

    readPoly(p1);
    readPoly(p2);

    Node *sum = addPoly(p1, p2);

    printPoly("P1", p1);
    printPoly("P2", p2);
    printPoly("SUM", sum);

    freePoly(p1);
    freePoly(p2);
    freePoly(sum);
    return 0;
}
