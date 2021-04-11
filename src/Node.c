// License: CC BY-NC-SA 4.0
/*
 * Node.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "Node.h"

void pushNodeFunction(Node **node, int word[64], int translation[64]) {
    if (!node)
        throwError(L"pushNode() was given a null pointer");

    if (!*node) {
        *node = (Node *)malloc(sizeof(Node));
        if (!*node)
            throwError(L"malloc() returned a null pointer");
        for (int i = 0; i < 64; i++) {
            (*node)->word[i] = 0;
            (*node)->translation[i] = 0;
        }
        memcpy((*node)->word, word, 64 * sizeof(int));
        memcpy((*node)->translation, translation, 64 * sizeof(int));
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }

    int cmp = compare(word, (*node)->word);
    if (cmp > 0) {
        pushNodeFunction(&(*node)->right, word, translation);
        return;
    } else if (cmp < 0) {
        pushNodeFunction(&(*node)->left, word, translation);
        return;
    }
}

void pushNode(Tree *tree, int word[64], int translation[64]) {
    if (!tree)
        throwError(L"pushNode() was given a null pointer");
    pushNodeFunction(&tree->root, word, translation);
    tree->count++;
}

void deleteNodeFunction(Node **root, int word[64]) {
    if (!root || !(*root))
        return;

    Node *parent = NULL, *current = *root;

    int cmp;
    while (current != NULL && (cmp = compare(word, current->word))) {
        parent = current;
        if (cmp > 0)
            current = current->right;
        else
            current = current->left;
    }

    if (!current)
        return;

    Node *child = NULL;
    if (!current->left || !current->right) {
        if (current->left)
            child = current->left;
        if (current->right)
            child = current->right;

        if (current != *root) {
            if (parent->left == current)
                parent->left = child;
            else
                parent->right = child;
        } else {
            *root = child;
        }

        free(current);
    } else {
        child = current->right;
        while (child->left)
            child = child->left;

        int data[64];
        memcpy(data, child->word, 64 * sizeof(int));

        deleteNodeFunction(root, data);

        memcpy(current->word, data, 64 * sizeof(int));
    }
}

void deleteNode(Tree *tree, int word[64]) {
    if (!tree)
        throwError(L"deleteNode() was given a null pointer");
    deleteNodeFunction(&tree->root, word);
    tree->count--;
}

void deleteTreeFunction(Node **node) {
    if (!node || !*node)
        return;
    deleteTreeFunction(&(*node)->left);
    deleteTreeFunction(&(*node)->right);
    free(*node);
    *node = NULL;
}

void deleteTree(Tree *tree) {
    if (!tree)
        throwError(L"deleteTree() was given a null pointer");
    deleteTreeFunction(&tree->root);
    tree->count = 0;
}

struct Tree dictionary = {
    .root = NULL,
    .count = 0
};

struct Tree equation = {
    .root = NULL,
    .count = 0
};
