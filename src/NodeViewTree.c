// License: CC BY-NC-SA 4.0
/*
 * NodeViewTree.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "NodeViewTree.h"

void nodeViewTreeUpdateContents() {
    for (int y = 0; y < getmaxy(window->window); y++) {
        wprintw(window->window, " ");
        for (int x = 0; x < getmaxx(window->window) - 2; x++)
            if (x + nodeViewTree.x < nodeViewTree.w && y + nodeViewTree.y < nodeViewTree.h)
                wprintw(window->window, "%lc", nodeViewTree.buffer[x + nodeViewTree.x + (y + nodeViewTree.y) * nodeViewTree.w]);
        wprintw(window->window, "\n");
    }
}

void nodeViewTreeHandleInput(int ret, int inp) {
    switch (inp) {
    case KEY_UP:
        if (nodeViewTree.y > 0)
            nodeViewTree.y -= 5;
        break;
    case KEY_DOWN:
        if (nodeViewTree.y + getmaxy(window->window) < nodeViewTree.h)
            nodeViewTree.y += 5;
        break;
    case KEY_LEFT:
        if (nodeViewTree.x > 0)
            nodeViewTree.x -= 15;
        break;
    case KEY_RIGHT:
        if (nodeViewTree.x + getmaxx(window->window) < nodeViewTree.w)
            nodeViewTree.x += 15;
        break;
    default:
        break;
    }
}

// Help me
bool nodeViewTreeGenerate(Node *node, int **buffer, int *w, int *h, int *center) {
    if (!node)
        return false;

    int *left_buffer = NULL, *right_buffer = NULL;
    int w_left = 0, h_left = 0, center_left = 0, w_right = 0, h_right = 0, center_right = 0;

    bool ret_left = nodeViewTreeGenerate(node->left, &left_buffer, &w_left, &h_left, &center_left);
    bool ret_right = nodeViewTreeGenerate(node->right, &right_buffer, &w_right, &h_right, &center_right);

    *w = MAX(length(node->word), length(node->translation)) + 8;
    *w = MAX(*w, w_left + w_right);
    *h = 5 + MAX(h_left, h_right);

    *buffer = (int *)calloc((*w + 1) * (*h + 1), sizeof(int));
    if (!*buffer)
        throwError(L"calloc() returned a null pointer");

    for (int i = 0; i < (*w) * (*h); i++)
        (*buffer)[i] = L'.';

    // Upper line
    int x = ((*w) - (MAX(length(node->word), length(node->translation)) + 8)) / 2, y = 0;

    (*buffer)[(x++) + y * (*w)] = L'┌';
    for (int i = 0; i < MAX(length(node->word), length(node->translation)) + 6; i++)
        (*buffer)[(x++) + y * (*w)] = (i != (MAX(length(node->word), length(node->translation)) + 6) / 2 || node == dictionary.root) ? L'─' : L'┴';
    (*buffer)[(x++) + y * (*w)] = L'┐';

    // English word
    x = ((*w) - (MAX(length(node->word), length(node->translation)) + 8)) / 2;
    y++;

    (*buffer)[(x++) + y * (*w)] = L'│';
    (*buffer)[(x++) + y * (*w)] = L' ';
    (*buffer)[(x++) + y * (*w)] = L'e';
    (*buffer)[(x++) + y * (*w)] = L'n';
    (*buffer)[(x++) + y * (*w)] = L':';
    (*buffer)[(x++) + y * (*w)] = L' ';

    for (int i = 0; i < MAX(length(node->word), length(node->translation)); i++)
        (*buffer)[(x++) + y * (*w)] = (i < length(node->word)) ? node->word[i] : L' ';

    (*buffer)[(x++) + y * (*w)] = L' ';
    (*buffer)[(x++) + y * (*w)] = L'│';

    // Russian translation
    x = ((*w) - (MAX(length(node->word), length(node->translation)) + 8)) / 2;
    y++;

    (*buffer)[(x++) + y * (*w)] = L'│';
    (*buffer)[(x++) + y * (*w)] = L' ';
    (*buffer)[(x++) + y * (*w)] = L'r';
    (*buffer)[(x++) + y * (*w)] = L'u';
    (*buffer)[(x++) + y * (*w)] = L':';
    (*buffer)[(x++) + y * (*w)] = L' ';

    for (int i = 0; i < MAX(length(node->word), length(node->translation)); i++)
        (*buffer)[(x++) + y * (*w)] = (i < length(node->translation)) ? node->translation[i] : L' ';

    (*buffer)[(x++) + y * (*w)] = L' ';
    (*buffer)[(x++) + y * (*w)] = L'│';

    // Lower line
    x = ((*w) - (MAX(length(node->word), length(node->translation)) + 8)) / 2;
    y++;

    (*buffer)[(x++) + y * (*w)] = L'└';
    for (int i = 0; i < MAX(length(node->word), length(node->translation)) + 6; i++) {
        (*buffer)[(x++) + y * (*w)] = (i != (MAX(length(node->word), length(node->translation)) + 6) / 2 || (!node->left && !node->right)) ? L'─' : L'┬';
        if (i == (MAX(length(node->word), length(node->translation)) + 6) / 2)
            *center = x - 1;
    }
    (*buffer)[(x++) + y * (*w)] = L'┘';

    // Connector line
    y++;

    if (node->left)
        (*buffer)[center_left + y * (*w)] = (center_left == *center) ? (L'│') : ((center_left < *center) ? L'┌' : L'┐');
    if (node->right)
        (*buffer)[center_right + w_left + y * (*w)] = (center_right + w_left == *center) ? (L'│') : ((center_right + w_left < *center) ? L'┌' : L'┐');

    if (node->left && node->right) {
        if ((*buffer)[*center + y * (*w)] == L'.')
            (*buffer)[*center + y * (*w)] = L'┴';
        for (int i = MIN(*center, MIN(center_left, center_right + w_left)); i < MAX(*center, MAX(center_left, center_right + w_left)); i++)
            if ((*buffer)[i + y * (*w)] == L'.')
                (*buffer)[i + y * (*w)] = L'─';
    } else if (node->left || node->right) {
        if ((*buffer)[*center + y * (*w)] == L'.')
            (*buffer)[*center + y * (*w)] = (((node->left) ? (center_left) : (center_right + w_left)) < *center) ? L'┘' : L'└';
        for (int i = MIN(*center, (node->left) ? (center_left) : (center_right + w_left)); i < MAX(*center, (node->left) ? (center_left) : (center_right + w_left)); i++)
            if ((*buffer)[i + y * (*w)] == L'.')
                (*buffer)[i + y * (*w)] = L'─';
    }

    y++;
    // Copy left subtree
    for (int i = 0; i < h_left; i++)
        for (int j = 0; j < w_left; j++)
            (*buffer)[j + (i + y) * (*w)] = left_buffer[j + i * w_left];

    // Copy right subtree
    for (int i = 0; i < h_right; i++)
        for (int j = 0; j < w_right; j++)
            (*buffer)[(j + w_left) + (i + y) * (*w)] = right_buffer[j + i * w_right];

    free(left_buffer);
    free(right_buffer);
    return true;
}

void nodeViewTreeCreateWindow() {
    newWindow(L"View dictionary (tree)", 3, 5, getmaxx(stdscr) - 6, getmaxy(stdscr) - 6, nodeViewTreeUpdateContents, nodeViewTreeHandleInput);
    nodeViewTree.x = 0;
    nodeViewTree.y = 0;
    nodeViewTree.w = 0;
    nodeViewTree.h = 0;
    if (nodeViewTree.buffer)
        free(nodeViewTree.buffer);
    nodeViewTree.buffer = NULL;

    int center;
    nodeViewTreeGenerate(dictionary.root, &nodeViewTree.buffer, &nodeViewTree.w, &nodeViewTree.h, &center);
}

struct NodeViewTree nodeViewTree = {
    .buffer = NULL,
    .x = 0,
    .y = 0,
    .w = 0,
    .h = 0,

    .createWindow = nodeViewTreeCreateWindow
};
