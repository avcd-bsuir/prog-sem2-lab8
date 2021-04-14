// License: CC BY-NC-SA 4.0
/*
 * Layers.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#include "Layers.h"

void layersUpdateContents() {
    for (int i = 0; i < layers.height; i++)
        wprintw(window->window, "Sum of string lengths on level %d: %d\n", i + 1, layers.layer_info[i]);
}

void layersHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    default:
        break;
    }
}

int layersHeight(Node *node) {
    if (!node)
        return 0;

    int left = layersHeight(node->left);
    int right = layersHeight(node->right);

    return (left > right) ? (left + 1) : (right + 1);
}

void getLayerInfo(Node *node, int layer) {
    if (!node)
        return;

    layers.layer_info[layer] += length(node->word) + length(node->translation);

    getLayerInfo(node->left, layer + 1);
    getLayerInfo(node->right, layer + 1);
}

void layersCreateWindow() {
    newWindow(L"Layer information", 5, 5, getmaxx(stdscr) - 10, getmaxy(stdscr) - 10, layersUpdateContents, layersHandleInput);
    layers.height = layersHeight(dictionary.root);

    if (layers.layer_info)
        free(layers.layer_info);
    layers.layer_info = (int *)calloc(layers.height, sizeof(int));

    getLayerInfo(dictionary.root, 0);
}

struct Layers layers = {
    .layer_info = NULL,
    .height = 0,

    .createWindow = layersCreateWindow
};
