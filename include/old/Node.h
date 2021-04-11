// License: CC BY-NC-SA 4.0
/*
 * Node.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 02 apr 2021
 */

#ifndef NODE_H
#define NODE_H

#define MAX_WORD_SIZE 32

struct Node {
    struct Node *left, *right;
    char word[MAX_WORD_SIZE], translation[2 * MAX_WORD_SIZE];
};
typedef struct Node Node;

Node *tree = NULL;
int tree_count = 0;

// Compare two strings
int compare(char a[MAX_WORD_SIZE], char b[MAX_WORD_SIZE]) {
    char a_lower[MAX_WORD_SIZE], b_lower[MAX_WORD_SIZE];
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        a_lower[i] = (a[i] >= 'A' && a[i] <= 'Z') ? (a[i] + 32) : (a[i]);
        b_lower[i] = (b[i] >= 'A' && b[i] <= 'Z') ? (b[i] + 32) : (b[i]);
    }
    return strcmp(a_lower, b_lower);
}

// Create new node
void nodeNew(Node **node, char word[], char translation[]) {
    *node = (Node *)malloc(sizeof(Node));
    if (!node || !*node) {
        endwin();
        printf("malloc() returned a null pointer\n");
        exit(-1);
    }
    strcpy((*node)->word, word);
    strcpy((*node)->translation, translation);
    (*node)->left = NULL;
    (*node)->right = NULL;
    tree_count++;
}

// Insert node
void nodePush(Node **node, char word[], char translation[]) {
    if (!node || !*node) {
        nodeNew(node, word, translation);
        return;
    }

    int cmp = compare(word, (*node)->word);
    if (cmp > 0) {
        nodePush(&(*node)->right, word, translation);
        return;
    }
    if (cmp < 0) {
        nodePush(&(*node)->left, word, translation);
        return;
    }
}

// Tree cleanup
void nodeDeleteAll(Node **node) {
    if (!node || !*node)
        return;
    nodeDeleteAll(&(*node)->left);
    nodeDeleteAll(&(*node)->right);
    free(*node);
    *node = NULL;
}

#include "Node_nodeDelete.h"
#include "Node_nodeDeleteAll.h"
#include "Node_nodePush.h"

int view_scroll, view_counter, view_option;
Node **view_selected;
#include "Node_viewNonRecursive.h"
#include "Node_viewRecursive.h"

#include "dictionary.h"

#endif
