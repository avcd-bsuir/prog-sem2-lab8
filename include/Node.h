// License: CC BY-NC-SA 4.0
/*
 * Node.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef NODE_H
#define NODE_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include "stdlib.h"
#include "string.h"

#include "Utils.h"

struct Node {
    struct Node *left, *right;
    int word[64], translation[64];
};
typedef struct Node Node;

struct Tree {
    Node *root;
    int count;
};
typedef struct Tree Tree;

void pushNode(Tree *tree, int word[64], int translation[64]);

void deleteNode(Tree *tree, int word[64]);

void deleteTree(Tree *tree);

extern struct Tree dictionary;

extern struct Tree equation;

#endif
