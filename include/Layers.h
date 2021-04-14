// License: CC BY-NC-SA 4.0
/*
 * Layers.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#ifndef LAYERS_H
#define LAYERS_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "Utils.h"
#include "Window.h"

struct Layers {
    int *layer_info;
    int height;
    void (*createWindow)();
};

extern struct Layers layers;

#endif
