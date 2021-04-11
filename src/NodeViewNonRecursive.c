// License: CC BY-NC-SA 4.0
/*
 * NodeViewNonRecursive.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "NodeViewNonRecursive.h"

void nodeViewNonRecursiveUpdateContents() {
    nodeViewNonRecursive.counter = 0;

    Stack *stack;
    Node *node = dictionary.root;
    aStackInit(&stack);

    while (true) {
        while (node) {
            aStackPush(&stack, node);
            node = node->left;
        }
        if (!stack)
            break;
        node = (Node *)aStackTop(&stack);
        if (nodeViewNonRecursive.counter >= nodeViewNonRecursive.start && nodeViewNonRecursive.counter < nodeViewNonRecursive.end && nodeViewNonRecursive.counter < dictionary.count) {
            if (nodeViewNonRecursive.counter == nodeViewNonRecursive.choice) {
                waddch(window->window, '>' | A_BLINK);
                memcpy(nodeViewNonRecursive.word, node->word, 64 * sizeof(int));
                memcpy(nodeViewNonRecursive.translation, node->translation, 64 * sizeof(int));
            } else {
                waddch(window->window, ' ');
            }
            wprintw(window->window, " %d. %ls - %ls\n", nodeViewNonRecursive.counter + 1, node->word, node->translation);
        }
        nodeViewNonRecursive.counter++;
        node = node->right;
        aStackPop(&stack);
    }
}

void nodeViewNonRecursiveHandleInput(int ret, int inp) {
    switch (inp) {
    case KEY_UP:
        if (nodeViewNonRecursive.choice > 0) {
            if (nodeViewNonRecursive.choice == nodeViewNonRecursive.start) {
                nodeViewNonRecursive.start--;
                nodeViewNonRecursive.end--;
            }
            nodeViewNonRecursive.choice--;
        }
        break;
    case KEY_DOWN:
        if (nodeViewNonRecursive.choice < dictionary.count - 1) {
            if (nodeViewNonRecursive.choice == nodeViewNonRecursive.end - 1) {
                nodeViewNonRecursive.start++;
                nodeViewNonRecursive.end++;
            }
            nodeViewNonRecursive.choice++;
        }
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        memcpy(nodeEdit.word, nodeViewNonRecursive.word, 64 * sizeof(int));
        memcpy(nodeEdit.translation, nodeViewNonRecursive.translation, 64 * sizeof(int));
        nodeEdit.createWindow();
        break;
    default:
        break;
    }
}

void nodeViewNonRecursiveCreateWindow() {
    newWindow(L"View dictionary (non-recursive)", 5, 5, getmaxx(stdscr) - 10, getmaxy(stdscr) - 10, nodeViewNonRecursiveUpdateContents, nodeViewNonRecursiveHandleInput);
    nodeViewNonRecursive.choice = 0;
    nodeViewNonRecursive.start = 0;
    nodeViewNonRecursive.end = getmaxy(window->window);
}

struct NodeViewNonRecursive nodeViewNonRecursive = {
    .choice = 0,
    .start = 0,
    .end = 0,
    .counter = 0,

    .createWindow = nodeViewNonRecursiveCreateWindow
};
