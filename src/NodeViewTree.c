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

}

void nodeViewTreeHandleInput(int ret, int inp) {

}

void nodeViewTreeCreateWindow() {
    newWindow(L"View dictionary (tree)", 5, 5, getmaxx(stdscr) - 10, getmaxy(stdscr) - 10, nodeViewTreeUpdateContents, nodeViewTreeHandleInput);
}

struct NodeViewTree nodeViewTree = {
    .createWindow = nodeViewTreeCreateWindow
};
