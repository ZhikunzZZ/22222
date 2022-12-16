#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"tldlist.h"
/*  
 * This is my own work as defined in the Academic Ethics agreement I have signed.
 */

struct tldlist{
    Date *begin, *end;
    TLDNode *head;
};
struct tldnode{
    char tld[32];
    TLDNode *next;
    long count;
};
struct tlditerator{
    TLDNode *head, *current;
};

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end){
    TLDList *tldlist = (TLDList *)malloc(sizeof(TLDList));
    tldlist->begin = date_duplicate(begin);
    tldlist->end = date_duplicate(end);
    tldlist->head = NULL;
    return tldlist;
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld){
    TLDNode *curr_node=tld->head;
    TLDNode *need_free;
    while(curr_node != NULL){
        need_free = curr_node;
        curr_node = curr_node->next;
        free(need_free);
    }
    date_destroy(tld->begin);
    date_destroy(tld->end);
    free(tld);
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
    char *tld_1 = hostname;
    while(strchr(tld_1,'.') != NULL){
        tld_1 = strchr(tld_1,'.')+1;
    }
    if((date_compare(d,tld->begin) >= 0) && (date_compare(d,tld->end) <= 0)){
        TLDNode *new_node = (TLDNode*)malloc(sizeof(TLDNode));
        strcpy(new_node->tld,tld_1);
        new_node->next = NULL;
        new_node->count = 1;
        if(tld->head == NULL){
            tld->head = new_node;
        }
        else{
            TLDNode *curr = tld->head;
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = new_node;
        }
        return 1;
    }
    else{
        return 0;
    }
    return 0;
}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
    long sum = 0;
    TLDNode *curr_node = tld->head;
    while(curr_node != NULL){
        sum += curr_node->count;
        curr_node = curr_node->next;
    }
    return sum;
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator *iterator = (TLDIterator*)malloc(sizeof(TLDIterator));
    iterator->head = NULL;
    TLDNode *curr_tldlist = tld->head;
    while(curr_tldlist != NULL){
        if(iterator->head == NULL){
            TLDNode *head_node = (TLDNode*)malloc(sizeof(TLDNode));
            strcpy(head_node->tld,curr_tldlist->tld);
            head_node->next = NULL;
            head_node->count = curr_tldlist->count;
            iterator->head = head_node;
            iterator->current = iterator->head;
        }
        else{
            TLDNode *curr_iter = iterator->head;
            TLDNode *prev_iter;
            int a = 0;
            while(curr_iter != NULL){
                if(strcmp(curr_iter->tld,curr_tldlist->tld) == 0){
                    a = 1;
                    curr_iter->count++;
                    break;
                }
                prev_iter = curr_iter;
                curr_iter = curr_iter->next;
            }
            if(a == 0){
                TLDNode *new_node = (TLDNode*)malloc(sizeof(TLDNode));
                strcpy(new_node->tld,curr_tldlist->tld);
                new_node->next = NULL;
                new_node->count = curr_tldlist->count;
                prev_iter->next = new_node;
            }
        }
        curr_tldlist = curr_tldlist->next;
    }
    return iterator;
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
    TLDNode *next_node = iter->current;
    if(iter->current != NULL)
        iter->current = iter->current->next;
    return next_node;
}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
    TLDNode *curr_node = iter->head;
    TLDNode *need_free;
    while(curr_node != NULL){
        need_free = curr_node;
        curr_node = curr_node->next;
        free(need_free);
    }
    free(iter);
}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
    return node->tld;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
    if(node != NULL){
        return node->count;
    }
    else{
        return 0;
    }
}
