// Window updateContents() function
void UC_viewNonRecursive(Window *window) {
    werase(window->window);

    view_counter = 0;

    Stack *stack;
    Node *node = tree;
    aStackInit(&stack);

    while (true) {
        while (node) {
            aStackPush(&stack, node);
            node = node->left;
        }
        if (!stack)
            break;
        node = (Node *)aStackTop(&stack);
        if (view_counter >= view_scroll && view_counter < tree_count && view_counter - view_scroll < getmaxy(window->window)) {
            if (view_counter == view_option) {
                waddch(window->window, '>' | A_BLINK);
                view_selected = &node;
            } else {
                waddch(window->window, ' ');
            }
            wprintw(window->window, " %d. %s - %s\n", view_counter + 1, node->word, node->translation);
        }
        view_counter++;
        node = node->right;
        aStackPop(&stack);
    }

    wrefresh(window->window);
}

// Window handleInput() function
void HI_viewNonRecursive(int input, Window *window) {
    switch (input) {
    case KEY_UP:
        if (view_option) {
            view_option--;
            if (view_option == view_scroll - 1)
                view_scroll--;
        }
        break;
    case KEY_DOWN:
        if (view_option != tree_count - 1) {
            view_option++;
            if (view_option == getmaxy(window->window) + view_scroll)
                view_scroll++;
        }
        break;
    default:
        break;
    }
}

// Menu function
void MENU_viewNonRecursive() {
    windowPush("Dictionary view (non-recursive)", 2, 2, cols - 4, rows - 4, &UC_viewNonRecursive, &HI_viewNonRecursive);
    view_scroll = 0;
    view_option = 0;
}
