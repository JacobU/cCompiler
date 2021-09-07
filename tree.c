#include "util.h"
#include "types.h"

typedef struct tree * T_tree;

struct tree {T_tree left; string key; void * binding; T_tree right;};

T_tree Tree(T_tree l, string k, void * b, T_tree r) {
    T_tree t = checked_malloc(sizeof(*t));
    t->left = l; t->key = k; t->binding = b; t->right = r;
    return t;
}

T_tree insert(string key, void * binding, T_tree t) {
    if(t==NULL) return Tree(NULL, key, binding, NULL);
    else if(strcmp(key,t->key) < 0)
        return Tree(insert(key, binding, t->left), t->key, t->binding, t->right);
    else if(strcmp(key, t->key) > 0)
        return Tree(t->left, t->key, t->binding, insert(key, binding, t->right));
    else return Tree(t->left, key, binding, t->right);
}

bool member(string item, T_tree t) {
    if(t==NULL) return FALSE;
    else if(strcmp(item, t->key) == 0) return TRUE;
    else if(strcmp(item, t->key) < 0)
        return member(item, t->left);
    else if(strcmp(item, t->key) > 0)
        return member(item, t->right);
}

void * lookup(string key, T_tree t) {
    if(t==NULL) return NULL;
    else if(strcmp(key, t->key) == 0) return t->binding;
    else if(strcmp(key, t->key) < 0)
        return lookup(key, t->left);
    else if(strcmp(key, t->key) > 0)
        return lookup(key, t->right);
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int height(T_tree t) {
    if(t == NULL) return 0;
    return 1 + max(height(t->left), height(t->right));
}

bool isBalanced(T_tree t) {
    int lh;
    int rh;

    if(t == NULL) return 1;

    lh = height(t->left);
    rh = height(t->right);
    if(abs(lh - rh) <= 1 && isBalanced(t->left) && isBalanced(t->right))
        return 1;
    return 0;
}

int main() {


    T_tree t = Tree(NULL, "t", NULL, NULL);
    t = insert("s", NULL, t);
    t = insert("p", NULL, t);
    t = insert("i", NULL, t);
    t = insert("p", NULL, t);
    t = insert("f", NULL, t);
    t = insert("b", NULL, t);
    t = insert("s", NULL, t);
    t = insert("t", NULL, t);

    bool checkBalance = isBalanced(t);

    printf("%d\n", checkBalance);
}