// License: CC BY-NC-SA 4.0
/*
 * NodeViewRecursive.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "NodeViewRecursive.h"

void viewRecursive(Node *node) {
    if (!node)
        return;

    viewRecursive(node->left);

    if (nodeViewRecursive.counter >= nodeViewRecursive.start && nodeViewRecursive.counter < nodeViewRecursive.end && nodeViewRecursive.counter < dictionary.count) {
        if (nodeViewRecursive.counter == nodeViewRecursive.choice) {
            waddch(window->window, '>' | A_BLINK);
            memcpy(nodeViewRecursive.word, node->word, 64 * sizeof(int));
            memcpy(nodeViewRecursive.translation, node->translation, 64 * sizeof(int));
        } else {
            waddch(window->window, ' ');
        }
        wprintw(window->window, " %d. %ls - %ls\n", nodeViewRecursive.counter + 1, node->word, node->translation);
    }

    nodeViewRecursive.counter++;

    viewRecursive(node->right);
}

void nodeViewRecursiveUpdateContents() {
    nodeViewRecursive.counter = 0;
    viewRecursive(dictionary.root);
}

void nodeViewRecursiveHandleInput(int ret, int inp) {
    switch (inp) {
    case KEY_UP:
        if (nodeViewRecursive.choice > 0) {
            if (nodeViewRecursive.choice == nodeViewRecursive.start) {
                nodeViewRecursive.start--;
                nodeViewRecursive.end--;
            }
            nodeViewRecursive.choice--;
        }
        break;
    case KEY_DOWN:
        if (nodeViewRecursive.choice < dictionary.count - 1) {
            if (nodeViewRecursive.choice == nodeViewRecursive.end - 1) {
                nodeViewRecursive.start++;
                nodeViewRecursive.end++;
            }
            nodeViewRecursive.choice++;
        }
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        memcpy(nodeEdit.word, nodeViewRecursive.word, 64 * sizeof(int));
        memcpy(nodeEdit.translation, nodeViewRecursive.translation, 64 * sizeof(int));
        nodeEdit.createWindow();
        break;
    default:
        break;
    }
}

void nodeViewRecursiveCreateWindow() {
    newWindow(L"View dictionary (recursive)", 5, 5, getmaxx(stdscr) - 10, getmaxy(stdscr) - 10, nodeViewRecursiveUpdateContents, nodeViewRecursiveHandleInput);
    nodeViewRecursive.choice = 0;
    nodeViewRecursive.start = 0;
    nodeViewRecursive.end = getmaxy(window->window);
}

struct NodeViewRecursive nodeViewRecursive = {
    .choice = 0,
    .start = 0,
    .end = 0,
    .counter = 0,

    .createWindow = nodeViewRecursiveCreateWindow
};
