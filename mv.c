#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "fs_struct.h"

int run_mv(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: mv source target\n");
        return 1;
    }

    char *src_path = argv[1];
    char *dst_path = argv[2];

    pthread_mutex_lock(&fs_mutex);

    Node *src_node;

    if (strchr(src_path, '/') == NULL) {
	    src_node = find_child(current_node, src_path);
    } else {
	    src_node = resolve_path(src_path);
    }

    if (src_node == NULL) {
        fprintf(stderr, "mv: cannot stat '%s': No such file or directory\n", src_path);
        pthread_mutex_unlock(&fs_mutex);
        return 1;
    }

    if (src_node == root) {
        fprintf(stderr, "mv: cannot move root directory\n");
        pthread_mutex_unlock(&fs_mutex);
        return 1;
    }

    Node *dst_node;

    if (strchr(dst_path, '/') == NULL) {
	    dst_node = find_child(current_node, dst_path);
    } else {
	    dst_node = resolve_path(dst_path);
    }

    if (dst_node != NULL && dst_node->type == TYPE_DIR) {
        if (find_child(dst_node, src_node->name) != NULL) {
            fprintf(stderr, "mv: cannot move '%s': File exists\n", src_node->name);
            pthread_mutex_unlock(&fs_mutex);
            return 1;
        }

        remove_child(src_node->parent, src_node);
        add_child(dst_node, src_node);

        printf("Moved '%s' into '%s'\n", src_path, dst_path);

        pthread_mutex_unlock(&fs_mutex);
        return 0;
    }

    
    if (dst_node != NULL) {
        fprintf(stderr, "mv: cannot overwrite existing file '%s'\n", dst_path);
        pthread_mutex_unlock(&fs_mutex);
        return 1;
    }


    char dst_copy[MAX_PATH_LENGTH];
    strncpy(dst_copy, dst_path, MAX_PATH_LENGTH - 1);
    dst_copy[MAX_PATH_LENGTH - 1] = '\0';

    char *last_slash = strrchr(dst_copy, '/');

    Node *dst_parent;
    char *new_name;

    if (last_slash == NULL) {
        dst_parent = src_node->parent;
        new_name = dst_copy;
    } else {
        *last_slash = '\0';
        new_name = last_slash + 1;

        if (strlen(new_name) == 0) {
            fprintf(stderr, "mv: invalid target '%s'\n", dst_path);
            pthread_mutex_unlock(&fs_mutex);
            return 1;
        }

        if (strlen(dst_copy) == 0) {
            dst_parent = root;
        } else {
            dst_parent = resolve_path(dst_copy);
        }

        if (dst_parent == NULL || dst_parent->type != TYPE_DIR) {
            fprintf(stderr, "mv: target directory '%s' does not exist\n", dst_copy);
            pthread_mutex_unlock(&fs_mutex);
            return 1;
        }
    }

    if (find_child(dst_parent, new_name) != NULL) {
        fprintf(stderr, "mv: cannot move '%s': File exists\n", new_name);
        pthread_mutex_unlock(&fs_mutex);
        return 1;
    }

    remove_child(src_node->parent, src_node);
    rename_node(src_node, new_name);
    add_child(dst_parent, src_node);

    printf("Moved '%s' to '%s'\n", src_path, dst_path);

    pthread_mutex_unlock(&fs_mutex);
    return 0;
}
