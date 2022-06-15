#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include "ijvm.h"

typedef struct stack
{
    word_t value;
    struct stack* next;
}stack_t;

stack_t *head = NULL;
int stackSize = 0;

void push(word_t data)
{
    stack_t *newNode;
    newNode = (stack_t*) malloc(sizeof(stack_t));
    newNode->value = data;
    if(head == NULL)
    {
        newNode->next = NULL;
    }
    else
    {
        newNode->next = head;
    }
    head = newNode;
    stackSize++;
}

void pop()
{
    assert(head != NULL);
    stack_t *temp = head;
    //word_t temp_val = head->value;
    head = head->next;
    free(temp);
    stackSize--;
}

word_t top()
{
    return head->value;
}

int size()
{
    return stackSize;
}