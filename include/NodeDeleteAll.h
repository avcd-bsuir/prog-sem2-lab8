// License: CC BY-NC-SA 4.0
/*
 * NodeDeleteAll.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef NODEDELETEALL_H
#define NODEDELETEALL_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "Utils.h"
#include "Window.h"

struct NodeDeleteAll {
    int option;
    void (*createWindow)();
};

extern struct NodeDeleteAll nodeDeleteAll;

#endif
