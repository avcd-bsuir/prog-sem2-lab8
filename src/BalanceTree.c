// License: CC BY-NC-SA 4.0
/*
 * BalanceTree.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#include "BalanceTree.h"

void balanceTreeUpdateContents() {
    mvwprintw(window->window, 1, 1, "Binary search tree");
    mvwprintw(window->window, 2, 4, "was balanced");
    wmove(window->window, 3, 8);
    windowPrintAttr(L"<OK>", A_STANDOUT);
}

void balanceTreeHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    case KEY_ENTER:
    case KEY_RETURN:
        window = window->parent;
        free(win);
        if (!window)
            shutdown();
        break;
    default:
        break;
    }
}

void balanceTreeStoreNodes(Node *node) {
    if (!node)
        return;

    balanceTreeStoreNodes(node->left);
    balanceTree.nodes[balanceTree.counter++] = node;
    balanceTreeStoreNodes(node->right);
}

Node *balanceTreeBuild(int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node *node = balanceTree.nodes[mid];

    node->left = balanceTreeBuild(start, mid - 1);
    node->right = balanceTreeBuild(mid + 1, end);

    return node;
}

void balanceTreeCreateWindow() {
    newWindow(L"BST was balanced", (getmaxx(stdscr) - 22) / 2, (getmaxy(stdscr) - 7) / 2, 22, 7, balanceTreeUpdateContents, balanceTreeHandleInput);
    balanceTree.nodes = (Node **)malloc(dictionary.count * sizeof(Node *));
    balanceTree.counter = 0;

    balanceTreeStoreNodes(dictionary.root);
    dictionary.root = balanceTreeBuild(0, balanceTree.counter - 1);

    free(balanceTree.nodes);
}

struct BalanceTree balanceTree = {
    .nodes = NULL,
    .counter = 0,

    .createWindow = balanceTreeCreateWindow
};
