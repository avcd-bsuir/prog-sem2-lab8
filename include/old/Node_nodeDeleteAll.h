int nodeDeleteAll_option;

// Window updateContents() function
void UC_nodeDeleteAll(Window *window) {
    werase(window->window);

    wmove(window->window, 1, 0);
    wprintw(window->window, "   Are you sure you want to    delete the whole dictionary?");

    wmove(window->window, 4, 7);
    if (!nodeDeleteAll_option) {
        windowPrintAttr(window, "<NO>", A_STANDOUT);
        wprintw(window->window, "       <YES>");
    } else {
        wprintw(window->window, "<NO>       ");
        windowPrintAttr(window, "<YES>", A_STANDOUT);
    }

    wrefresh(window->window);
}

// Window handleInput() function
void HI_nodeDeleteAll(int input, Window *window) {
    switch (input) {
    case KEY_LEFT:
    case KEY_RIGHT:
        nodeDeleteAll_option = !nodeDeleteAll_option;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        if (nodeDeleteAll_option)
            nodeDeleteAll(&tree);
        windowPop();
        break;
    default:
        break;
    }
}

// Menu function
void MENU_nodeDeleteAll() {
    windowPush("Delete dictionary", (cols - 32) / 2, (rows - 7) / 2, 32, 7, &UC_nodeDeleteAll, &HI_nodeDeleteAll);
    nodeDeleteAll_option = 0;
}
