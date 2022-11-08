//#ifndef _TLDLIST_H_INCLUDED_
//#define _TLDLIST_H_INCLUDED_

#include "date.h"
#include "tldlist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct tldlist{
    Date* start;
    Date* end;
    int count;
    TLDNode * root;
};

struct tldnode{
    char* tldStr;
    int count;
    TLDNode * left_child;
    TLDNode * right_child;
};

struct tlditerator{
    TLDNode *node;
    TLDIterator *next;
};


/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end){
    //TLDNode* node = (TLDNode*) malloc(sizeof(TLDNode));
    TLDList* ptr = (TLDList*) malloc(sizeof(TLDList));
    if(ptr == NULL){
        return NULL;
    }

    ptr->start = begin;
    ptr->end = end;   
    ptr->count = 0;
    ptr->root = NULL;

    return ptr;
    
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld){
    TLDIterator* it = tldlist_iter_create(tld);
    TLDNode*temp; //create a fresh iterator this is because my iterator works by making the node null
    //to iterate through it
    while(it != NULL){
        temp = it->node;
        it = it->next;
        free(temp->tldStr);
        free(temp);
        temp = NULL;
    }
    tld = NULL;
    tldlist_iter_destroy(it);
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
    int added;
    char* ending;
    char* reset;
    char* token;
    char hostcopy[strlen(hostname)];

    strcpy(hostcopy,hostname);
    reset = hostcopy;
    //parse the string
    while((token = strtok_r(reset,".", &reset))){
       ending=token; 
    }
    

    if(date_compare(d,tld->start) == 1 & date_compare(d, tld->end) == -1){
        char* ptr = (char*) malloc(sizeof(char)*(strlen(ending)+1));
        if(ptr == NULL){
            return(0);
        }
        strcpy(ptr,ending);
        // if no root then add the details provided to root
        //else call node_add which recursivly finds a place to add the node
        if(tld->root == NULL){
            tld->root = (TLDNode*) malloc(sizeof(TLDNode));
            if(tld->root == NULL){
                return 0;
            }
            tld->count = 1;
            tld->root->tldStr = ptr;
            tld->root->count = 1;        
            tld->root->right_child = NULL;
            tld->root->left_child = NULL;
        }else{
            added = node_add(tld->root, ptr); 
            if(added>0){
                tld->count+=1;
                return 1;
            }else{
                return 0;
            }
        }
    }
    return(0);
}

// Recursivly goes through the tree to find a child node to place the
// provided tld.
int node_add(TLDNode *parent, char *ending){  
    if(strcmp(parent->tldStr,ending) == 0){
        parent->count+=1;
        return 1;
    }

    if(strcmp(ending,parent->tldStr)>0){
        if(parent->right_child == NULL){
            parent->right_child = (TLDNode*) malloc(sizeof(TLDNode));
            TLDNode * ptr = (TLDNode*) malloc(sizeof(TLDNode));
            if(ptr == NULL || parent->right_child == NULL){
                return 0;
            }
            ptr->right_child = NULL;
            ptr->left_child = NULL;
            ptr->count = 0;
            ptr->tldStr = NULL;
            parent->right_child->tldStr = ending;
            parent->right_child->count = 1;        
            parent->right_child->right_child = ptr->right_child;
            parent->right_child->left_child = ptr->left_child;
            return(1);
        }else{
            return node_add(parent->right_child,ending);
        }

    }else{
        if(parent->left_child == NULL){
            parent->left_child = (TLDNode*) malloc(sizeof(TLDNode));
            TLDNode* ptr = (TLDNode*) malloc(sizeof(TLDNode));
            if(ptr == NULL){
                return 0;
            }
            ptr->left_child = NULL;
            ptr->right_child = NULL;
            ptr->count = 0;
            ptr->tldStr = NULL;
            parent->left_child->right_child = ptr->right_child;
            parent->left_child->left_child = ptr->left_child;
            parent->left_child->tldStr = ending;
            parent->left_child->count = 1;      
            return 1;  
        }else{
            return node_add(parent->left_child,ending);
        }


    return(0);
        

    }
}


/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
    return(tld->count);
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator* itr = (TLDIterator*) malloc(sizeof(TLDIterator));
    //TLDNode* nd = (TLDNode*) malloc(sizeof(TLDNode));
    if(itr==NULL){
        return NULL;
    }
    itr->node = NULL;
    itr->next = NULL;
    flatten(tld->root, itr);
    //if(done==NULL){
      //  return NULL;
    //}
    return(itr);
}


// recusivly traverses the tree to flatten it to a linked list
void flatten(TLDNode *node, TLDIterator *it){ 
    if(node==NULL){
        return;
    }

    //TLDIterator* itr = (TLDIterator*) malloc(sizeof(TLDIterator));
    //flatten(node->left_child,itr);
    //printf("%s\n", node->tldStr);
    //it->node = node;
    //it->next = itr;
    //flatten(node->right_child,itr);

    if(node==NULL){
        return;
    }

    it->node = node;
    it->next = NULL;
    if (node->left_child){
        TLDIterator* left_itr = (TLDIterator*) malloc(sizeof(TLDIterator));
        it->next = left_itr;
        flatten(node->left_child, left_itr);
        while (it->next){
            it = it->next;
        }

    } if (node->right_child) {
        TLDIterator* right_itr = (TLDIterator*) malloc(sizeof(TLDIterator));
        it->next = right_itr;
        flatten(node->right_child, right_itr);
    }
}
/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
    TLDNode* node;

    if(iter == NULL){
        return NULL;
    }

    while(!iter->node && iter->next){
        iter = iter->next;
    }

    if(iter->node == NULL){
        return NULL;
    }
    node = iter->node;
    iter->node = NULL;
    return(node);
}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
    TLDIterator* temp;

    while(iter != NULL){
        temp = iter;
        iter = iter->next;
        free(temp);
        temp = NULL;
    }
    iter = NULL;
}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
    return(node->tldStr);
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
    return(node->count);
}

// int main(int argc, char *argv[]) {
//     Date* date1 = date_create("01/01/2000");
//     Date* date2 = date_create("01/01/2005");
//     Date* date3 = date_create("01/01/2003");
//     TLDList* tld = tldlist_create(date1,date2);
//     tldlist_add(tld,"www.com",date3);
//     tldlist_add(tld,"www.aom",date3);
//     tldlist_add(tld,"www.dom",date3);
//     tldlist_add(tld,"www.bom",date3);
//     tldlist_add(tld,"www.eom",date3);
//     tldlist_add(tld,"www.gom",date3);
//     tldlist_add(tld,"www.fom",date3);
//     TLDIterator* iter = tldlist_iter_create(tld);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_next(iter);
//     tldlist_iter_destroy(iter);
//     date_destroy(date1);
//     date_destroy(date2);
//     date_destroy(date3);
//     tldlist_destroy(tld);
// }
//#endif /* _TLDLIST_H_INCLUDED_ */