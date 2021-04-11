void viewRecursive(WINDOW *window, Node *node) {
    if (!node)
        return;

    viewRecursive(window, node->left);

    if (view_counter >= view_scroll && view_counter < tree_count && view_counter - view_scroll < getmaxy(window)) {
        if (view_counter == view_option) {
            waddch(window, '>' | A_BLINK);
            view_selected = &node;
        } else {
            waddch(window, ' ');
        }
        wprintw(window, " %d. %s - %s\n", view_counter + 1, node->word, node->translation);
    }
    view_counter++;

    viewRecursive(window, node->right);
}

// Window updateContents() function
void UC_viewRecursive(Window *window) {
    werase(window->window);

    view_counter = 0;
    viewRecursive(window->window, tree);

    wrefresh(window->window);
}

// Window handleInput() function
void HI_viewRecursive(int input, Window *window) {
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
    case KEY_ENTER:
    case KEY_RETURN:
        nodeDelete(view_selected);
        break;
    default:
        break;
    }
}

// Menu function
void MENU_viewRecursive() {
    windowPush("Dictionary view (recursive)", 2, 2, cols - 4, rows - 4, &UC_viewRecursive, &HI_viewRecursive);
    view_scroll = 0;
    view_option = 0;
}
