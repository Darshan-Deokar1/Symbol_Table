#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
// #define begin _startMatrix_()L
// #define end _endMatrix_()

int hash_func(string ch)
{
    int key = 0;
    int i = 0;
    while (ch[i] != 0)
    {
        key += ch[i];
        i++;
    }
    return key % 101;
}

typedef struct hash_node
{
    string variable;
    int value;
    struct hash_node *next;
} hash_node;

typedef struct hash_table
{
    hash_node *arr[101];
} hash_table;

typedef struct Node
{
    hash_table *hash_ptr;
    struct Node *next;
    struct Node *prev;
} Node;

void begin(Node **topptr)
{
    printf("1");
    Node *top = *topptr;
    Node *nptr = (Node *)(malloc(sizeof(Node)));

    if (nptr != NULL)
    {
        printf("1");
        nptr->prev = top;
        nptr->next = NULL;
        if (top != NULL)
        {
            printf("1");
            top->next = nptr;
        }
        nptr->hash_ptr = (hash_table *)malloc(sizeof(hash_table));
        *topptr = nptr;
        for (int i = 0; i < 101; i++)
        {
            // if (i == 100)
            //  printf("1");
            nptr->hash_ptr->arr[i] = NULL;
        }
    }
}

void assign(string ch, int value, Node *top)
{
    printf("2");
    int idx = hash_func(ch);
    if (top != NULL)
    {
        printf("2");
        if (top->hash_ptr != NULL)
        {
            printf("2");
            hash_node *ptr = top->hash_ptr->arr[idx];
            if (ptr != NULL)
            {
                printf("2");
                while (ptr->next != NULL && (ptr->variable != ch))
                {
                    printf("2");
                    ptr = ptr->next;
                }
                if (ptr->variable == ch)
                {
                    printf("2");
                    ptr->value = value;
                }
                else
                {
                    printf("2");
                    hash_node *qptr = (hash_node *)malloc(sizeof(hash_node));
                    qptr->variable = ch;
                    qptr->value = value;
                    qptr->next = NULL;
                    ptr->next = qptr;
                }
            }
            else
            {
                printf("2");
                hash_node *qptr = (hash_node *)malloc(sizeof(hash_node));
                qptr->variable = ch;
                qptr->value = value;
                qptr->next = NULL;
                ptr = qptr;
            }

            // top->hash_ptr->arr[idx].variable = ch;
            // top->hash_ptr->arr[idx].value = value;
        }
    }
    printf(" ");
}

void print(string ch, Node *top)
{
    printf("3");
    Node *ptr = top;
    int flag = 0; // =>we've not yet found ch
    while (flag == 0 && ptr != NULL)
    {
        hash_node *start = ptr->hash_ptr->arr[hash_func(ch)];
        while (start != NULL && flag == 0)
        {
            if (start->variable == ch)
            {
                flag = 1;
                printf("\n%d\n", start->value);
            }
            else
            {
                start = start->next;
            }
        }
        ptr = ptr->prev;
    }
    if (flag == 0 && ptr == NULL)
    {
        printf("\nVariable doesn't exist\n");
    }
}

void free_list(hash_node *lptr)
{
    while (lptr != NULL)
    {
        hash_node *ptr = lptr;
        lptr = lptr->next;
        free(ptr);
        ptr = NULL;
    }
}

void end(Node **topptr)
{
    Node *top = *topptr;
    Node *ptr = top;
    if (top)
    {
        *topptr = top->prev;
        for (int i = 0; i < 101; i++)
        {
            free_list(top->hash_ptr->arr[i]);
            top->hash_ptr->arr[i] = NULL;
        }
        free(top->hash_ptr);
        top->hash_ptr = NULL;
        free(top);
        top = NULL;
    }
}

int main()
{
    Node *top = NULL;
    // printf("\n1\n");
    begin(&top);
    assign("a", 5, top);
    print("a", top);
    assign("b", 9, top);
    print("a", top);
    print("b", top);

    begin(&top);
    assign("b", 7, top);
    print("a", top);
    print("b", top);
    end(&top);

    print("b", top);
    end(&top);
    return 0;
}