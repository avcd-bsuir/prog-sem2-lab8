// License: CC BY-NC-SA 4.0
/*
 * EquationSolver.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 14 apr 2021
 */

#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "Utils.h"
#include "Window.h"

struct EquationSolver {
    int *equation, *screen_data;
    int eq_length, i, y;
    bool error;
    void (*createWindow)();
};

extern struct EquationSolver equationSolver;

#endif
