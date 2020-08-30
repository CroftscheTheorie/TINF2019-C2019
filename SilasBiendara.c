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
        return searchValue(node->left, val);
    } else if (val > node->content){
        return searchValue(node->right, val);
    } else{
        return NULL;
    }
}

void printTree(struct tnode *node){
    if (node != NULL){
        printTree(node->left);
        printf("%d\t", node->content);
        printTree(node->right);
    }
}

void printPadding(char ch, int n){
    int i;

    for ( i = 0; i < n; i++ )
        putchar ( ch );
}

void printStrucutred(struct tnode* root, int level){
    if (root == NULL){
        printPadding ('\t', level);
        puts ("~");
    } else  {
        printStrucutred(root->right, level+1);
        printPadding( '\t', level);
        printf("%d\n", root->content);
        printStrucutred( root->left, level+1);
    }
}

struct tnode* minContentNode(struct tnode* node){
    struct tnode* curr = node;

    while (curr && curr->left != NULL)
        curr = curr->left;

    return curr;
}

struct tnode* removeNode(struct tnode *root, int content){
    // Check if root is null
    if (root == NULL) return root;

    // Check if content is in left or right path of tree
    if (content < root->content)
        root->left = removeNode(root->left, content);
    else if (content > root->content)
        root->right = removeNode(root->right, content);
    // If is in current tree
    else{
        // Check if only one child or no child
        if (root->left == NULL){
            struct tnode *tmpNode = root->right;
            root->right = NULL;
            deletenode(root);
            return tmpNode;
        } else if (root->right == NULL){
            struct tnode *tmpNode = root->left;
            root->left = NULL;
            deletenode(root);
            return tmpNode;
        }
        // if root has two children, remove current one and replace wiht inorder sucessor (smallest right child)
        struct tnode *tmpNode = minContentNode(root->right);

        root->content = tmpNode->content;

        root->right = removeNode(root->right, tmpNode->content);  
    }
    // Content not found in tree -> nothing to do
    return root;
}

void main(){
    struct tnode* root = addelement(NULL, 20);
    addelement(root, 10);
    addelement(root, 20);
    addelement(root, 50);
    addelement(root, 100);
    addelement(root, 80);
    addelement(root, 90);
    addelement(root, 70);

    //printTree(root);
    printStrucutred(root, 0);

    removeNode(root, 80);

    printf("---\t---\t---\t---\t---\t---\t---\t---\n");

    printStrucutred(root, 0);

    deletenode(root);
}

