#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int content;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *addelement(struct tnode *p, int i){
    int cond;
    if (p == NULL) {
        p = talloc();
        p->content = i;
        p->left = p->right = NULL;
    } else if (p->content == i) {
        return p;
    } else if (i < p->content)
    {
        p->left = addelement(p->left, i);
    } else {
        p->right = addelement(p->right, i);
    }
    return p;
}

int deletenode(struct tnode *p) {
    if (p == NULL) return 0;
    else {
        deletenode(p->left);
        deletenode(p->right);
        p->left = NULL;
        p->right = NULL;
        free(p);
        return 0;
    }
}

struct tnode *addtree(struct tnode *top, struct tnode *p){
    if (p == NULL){
        return top;
    }
    else
    {
        return addtree(addtree(addelement(top, p->content),p->right), p->left);
    }
    
}

struct tnode *searchValue(struct tnode *node, int val){
    if(node == NULL) return NULL;
    if (val == node->content){
        return node;
    } else if (val < node->content){
        searchValue(node->left, val);
    } else if (val > node->content){
        searchValue(node->right, val);
    }
    
}

void printTree(struct tnode *node){
    if (node != NULL){
        printTree(node->left);
        printf("%d\t", node->content);
        printTree(node->right);
    }
}

void removeNodeByValue(struct tnode *node){
    //TODO
}

void main(){
    struct tnode* root = addelement(NULL, 20);
    addelement(root, 10);
    addelement(root, 20);
    addelement(root, 100);
    addelement(root, 80);
    addelement(root, 90);
    addelement(root, 70);

    printTree(root);

    deletenode(root);
}

