// License: CC BY-NC-SA 4.0
/*
 * NodeViewTree.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef NODEVIEWTREE_H
#define NODEVIEWTREE_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "NodeEdit.h"
#include "Utils.h"
#include "Window.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

struct NodeViewTree {
    int *buffer;
    int x, y, w, h;
    void (*createWindow)();
};

extern struct NodeViewTree nodeViewTree;

#endif
