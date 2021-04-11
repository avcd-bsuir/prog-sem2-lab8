// License: CC BY-NC-SA 4.0
/*
 * Utils.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "Utils.h"

void shutdown() {
    endwin();
    exit(0);
}

void throwError(int text[]) {
    endwin();
    printf("error: %ls\n", text);
    exit(-1);
}

int length(int text[]) {
    int len = 0;
    while (text[++len] != 0);
    return len;
}

int compare(int a[64], int b[64]) {
    int a_lower[64], b_lower[64], i;
    for (i = 0; i < 64 && a[i] && b[i] && ((a[i] >= L'A' && a[i] <= L'Z') ? (a[i] + 32) : (a[i])) == ((b[i] >= L'A' && b[i] <= L'Z') ? (b[i] + 32) : (b[i])); i++);
    return a[i] - b[i];
}
