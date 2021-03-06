/**
 * hash_table.c
 * Implementation for hash table using linked list.
 * Author: Libao Jin
 * Email: jinlibao@outlook.com
 * Date: 07/21/2018
 * Copyright (c) 2018 Libao Jin
 * All rights reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct linkedlist
{
    int key;
    int val;
    struct linkedlist *next;
} node;

void init(node *head, int key, int val, node *next)
{
    head->key = key;
    head->val = val;
    head->next = next;
}

void insert(node *head, int key, int val)
{
    node* cur = head;

    if (key == cur->key)
        cur->val += val;

    for (cur = head; key != cur->key; cur = cur->next)
    {
        if (cur->next && key > cur->next->key)
            continue;
        else if (cur->next && key == cur->next->key)
            cur->next->val += val;
        else
        {
            node *new = (node *) malloc(sizeof(node));
            init(new, key, val, cur->next);
            cur->next = new;
        }
    }
}

int touch(node *head, int key)
{
    node *cur = head;
    while (cur && key != cur->key)
        cur = cur->next;
    if (cur && key == cur->key)
        return cur->val > 0 ? cur->val-- : 0;
    return 0;
}

int search(node *head, int key)
{
    node *cur = head;
    while (cur && key != cur->key)
        cur = cur->next;
    return (cur && key == cur->key && cur->val > 0) ? 1 : 0;
}

void update(node *head, int key, int val)
{
    node *cur = head;
    while (cur && key != cur->key)
        cur = cur->next;
    if (cur && key == cur->key)
        cur->val = val;
}

void printNodes(node *head)
{
    node *cur;
    for (cur = head; cur->next; cur = cur->next)
        printf("(%d, %d) - ", cur->key, cur->val);
    printf("(%d, %d)\n", cur->key, cur->val);
}

#define M 100
#define N 17

int main(int argc, char *argv[])
{
    int key;
    srand((unsigned) time(0));
    node *hash = malloc(N * sizeof(node));
    for (int i = 0; i < N; init(hash + i, i, 0, NULL), i++) {}
    for (int i = 0; i < M; key = rand() % 100, insert(&hash[key % N], key, 1), i++) {}

    for (int i = 0; i < N; printNodes(&hash[i]), i++)
        printf("Node[%d]: ", i);
    for (int i = 0; i < M; key = rand() % 100, update(&hash[key % N], key, 1),i++) {}
    // for (int i = 0; i < M; key = rand() % 100, touch(&hash[key % N], key),i++) {}
    printf("\nUpdated: \n");
    for (int i = 0; i < N; printNodes(&hash[i]), i++)
        printf("Node[%d]: ", i);

    free(hash);
    return 0;
}
