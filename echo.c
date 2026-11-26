#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs_struct.h"

int run_echo(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\n");
        return 0;
    }

    int redirect_index = -1;
    int append_mode = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], ">") == 0) {
            redirect_index = i;
            append_mode = 0;
            break;
        }
        else if (strcmp(argv[i], ">>") == 0) {
            redirect_index = i;
            append_mode = 1;
            break;
        }
    }

    if (redirect_index == -1) {
        for (int i = 1; i < argc; i++) {
            printf("%s", argv[i]);
            if (i != argc - 1)
                printf(" ");
        }
        printf("\n");
        return 0;
    }

    if (redirect_index == argc - 1) {
        printf("echo: missing file name\n");
        return 1;
    }

    char *filename = argv[redirect_index + 1];

    Node *file = resolve_path(filename);

    if (file == NULL) {
        file = create_node(filename, TYPE_FILE, "user");
        add_child(current_node, file);
    }

    if (file->type == TYPE_DIR) {
        printf("echo: cannot write directory\n");
        return 1;
    }

    char buffer[4096] = "";

    for (int i = 1; i < redirect_index; i++) {
        strcat(buffer, argv[i]);
        if (i != redirect_index - 1)
            strcat(buffer, " ");
    }

    strcat(buffer, "\n");

    if (append_mode)
        append_file_content(file, buffer);
    else
        set_file_content(file, buffer);

    return 0;
}
