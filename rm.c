#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "fs_struct.h"

typedef struct {
    char *target_path;
    int r_option, f_option;
} RmThreadArg;

void* rm_thread_func(void *arg) {
    RmThreadArg *t_arg = (RmThreadArg *)arg;

    pthread_mutex_lock(&fs_mutex);
    
    char *target_path = t_arg->target_path;
    
    Node *target_node;
    
    if (strchr(target_path, '/') == NULL) {
        target_node = find_child(current_node, target_path);
        } else {
        target_node = resolve_path(target_path);
    }
    
    if (target_node == NULL) {
        if (!t_arg->f_option) {
          fprintf(stderr, "rm: cannot remove '%s' : No such file or directory\n", target_path);
        }
        
        pthread_mutex_unlock(&fs_mutex);
        
        return NULL;
    }
    
    if (target_node == root) {
        fprintf(stderr, "rm: cannot remove root directory\n");
        
        pthread_mutex_unlock(&fs_mutex);
        
        return NULL;
    }
    
    if (target_node->type == TYPE_DIR && !t_arg->r_option) {
        fprintf(stderr, "rm: cannot remove '%s' : Is a directory\n", target_path);
        
        pthread_mutex_unlock(&fs_mutex);
        
        return NULL;
    }
    
    remove_child(target_node->parent, target_node);
    
    if(target_node->type == TYPE_DIR) {
        delete_recursive(target_node);
    } else {
        if (target_node->content != NULL) {
            free(target_node->content);
        }
        free(target_node);
    }
    
    printf("Removed '%s' \n", target_path);
    
    pthread_mutex_unlock(&fs_mutex);
    
    return NULL;
}
    

int run_rm(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: rm [-r] [-f] [-rf] target...\n");
        return 1;
    }

    int r_option = 0;
    int f_option = 0;
    int start_index = 1;

    if (argv[1][0] == '-') {
        for (int i = 1; argv[1][i] != '\0'; i++) {
            if (argv[1][i] == 'r') {
                r_option = 1;
            } else if (argv[1][i] == 'f') {
                f_option = 1;
            } else {
                fprintf(stderr, "rm: invalid option -- '%c'\n", argv[1][i]);
                return 1;
            }
        }
        start_index = 2;
    }

    if (argc <= start_index) {
        fprintf(stderr, "Usage: rm [-r] [-f] [-rf] target...\n");
        return 1;
    }

    int num_targets = argc - start_index;
    
    pthread_t *threads = malloc(sizeof(pthread_t) * num_targets);
    
    RmThreadArg *args = malloc(sizeof(RmThreadArg) * num_targets);
    
    if (threads == NULL || args == NULL) {
        fprintf(stderr, "rm: memory allocation failed\n");
        free(threads);
        free(args);
        return 1;
    }
    
    for (int i = 0; i < num_targets; i++) {
        args[i].target_path = strdup(argv[start_index + i]);
    
        args[i].r_option = r_option;
        args[i].f_option = f_option;
    
        pthread_create(&threads[i], NULL, rm_thread_func, &args[i]);
    }
    
    for (int i = 0; i < num_targets; i++) {
        pthread_join(threads[i], NULL);
        free(args[i].target_path);
    }
    
    free(threads);
    free(args);
    
    return 0;
}
