/*
 * This is my own work as defined in the Academic Ethics agreement I have signed.
 */

#include "tldlist.h"
#include <stdlib.h>
#include <ctype.h>
#include "string.h"

struct tldlist {
    Date *date_begin;
    Date *date_end;
    int valid_nodes;
    struct tldnode *root;
};

struct tldnode {
    char *tld_value;
    int repeats;

    struct tldnode *left_child;
    struct tldnode *right_child;
};

struct tlditerator {
    struct tldnode **stack;
    int current_index;
};

/*
 * tldnode_create function return a pointer for node, needed in a tldlist tree structure
 * returns NULL if is impossible to allocaet enough memory
 */
struct tldnode *tldnode_create(char *val);

/*
 * tldnode_destroy recursively dealocates memory used for tree nodes
 */
void tldnode_destroy(struct tldnode *node);


TLDList *tldlist_create(Date *begin, Date *end) {
    struct tldlist *list = NULL;
    if ((list = malloc(sizeof(struct tldlist))) != NULL) {
        list->date_begin = date_duplicate(begin);
        list->date_end = date_duplicate(end);
        if (!(list->date_begin && list->date_end)) return NULL;
        list->root = NULL;
        list->valid_nodes = 0;
    }
    return list;
}

void tldlist_destroy(TLDList *tld) {
    tldnode_destroy(tld->root);
    date_destroy(tld->date_begin);
    date_destroy(tld->date_end);
    free(tld);
}

int tldlist_add(TLDList *tld, char *hostname, Date *d) {
    if (!d || date_compare(d, tld->date_begin) < 0
        || date_compare(d, tld->date_end) > 0)
        return 0;

    ++tld->valid_nodes;
    char *currentTLD = malloc(strlen(hostname) * sizeof(char));
    strcpy(currentTLD, hostname);
    currentTLD = strtok(currentTLD, ".");

    char *tld_val = malloc(strlen(hostname) * sizeof(char));
    while (currentTLD) {
        strcpy(tld_val, currentTLD);
        currentTLD = strtok(NULL, ".");
    }
    for (int i = 0; tld_val[i] != '\0'; ++i) {
        tld_val[i] = (char) tolower(tld_val[i]);
    }
    if (tld->root == NULL) {
        tld->root = tldnode_create(tld_val);
    } else {
        struct tldnode *temp = tld->root;
        while (temp) {
            if (strcmp(tld_val, temp->tld_value) < 0) {
                if (temp->left_child)
                    temp = temp->left_child;
                else {
                    temp->left_child = tldnode_create(tld_val);
                    break;
                }
            } else if (strcmp(tld_val, temp->tld_value) > 0) {
                if (temp->right_child)
                    temp = temp->right_child;
                else {
                    temp->right_child = tldnode_create(tld_val);
                    break;
                }
            } else {
                ++temp->repeats;
                break;
            }
        }
    }
    free(currentTLD);
    free(tld_val);
    currentTLD = NULL;
    tld_val = NULL;
    return 1;
}

struct tldnode *tldnode_create(char *value) {
    struct tldnode *node = NULL;
    if ((node = (struct tldnode *) malloc(sizeof(struct tldnode))) != NULL) {
        node->tld_value = malloc((strlen(value)) * sizeof(char *));
        strcpy(node->tld_value, value);
        node->left_child = NULL;
        node->right_child = NULL;
        node->repeats = 1;
    }
    return node;
}

long tldlist_count(TLDList *tld) {
    return tld->valid_nodes;
}

TLDIterator *tldlist_iter_create(TLDList *tld) {
    struct tlditerator *iter = NULL;
    if ((iter = malloc(sizeof(TLDIterator))) != NULL) {

        if ((iter->stack = malloc(tldlist_count(tld) * sizeof(struct tldnode))) == NULL)
            return NULL;

        iter->current_index = -1;
        struct tldnode *temp = tld->root;
        while (temp) {
            iter->stack[++iter->current_index] = temp;
            temp = temp->left_child;
        }
    }
    return iter;
}

TLDNode *tldlist_iter_next(TLDIterator *iter) {
    if (iter->current_index < 0) return NULL;
    struct tldnode *current = iter->stack[iter->current_index];
    struct tldnode *temp = current->right_child;
    --iter->current_index;
    while (temp) {
        ++iter->current_index;
        iter->stack[iter->current_index] = temp;
        temp = temp->left_child;
    }
    return current;
}

void tldlist_iter_destroy(TLDIterator *iter) {
    free(iter->stack);
    iter->stack = NULL;
    free(iter);
}

char *tldnode_tldname(TLDNode *node) {
    return node->tld_value;
}

long tldnode_count(TLDNode *node) {
    return node->repeats;
}

void tldnode_destroy(struct tldnode *node) {
    if (!node) return;
    if (node->left_child) {
        tldnode_destroy(node->left_child);
        node->left_child = NULL;
    }
    if (node->right_child) {
        tldnode_destroy(node->right_child);
        node->right_child = NULL;
    }
    free(node->tld_value);
    node->tld_value = NULL;

    free(node);
}
