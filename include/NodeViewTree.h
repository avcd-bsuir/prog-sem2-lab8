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

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "NodeEdit.h"
#include "Utils.h"
#include "Window.h"

struct NodeViewTree {
    void (*createWindow)();
};

extern struct NodeViewTree nodeViewTree;

#endif
