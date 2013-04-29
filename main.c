#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NUM 30
#define MAX_WORD_SIZE 128
struct tree_el {
    char val[MAX_WORD_SIZE];
    char *word;
    struct tree_el *right, *left;
};

typedef struct tree_el node;

void insert(node ** tree, node * item)
{
    if (!(*tree)) {
        *tree = item;
        return;
    }
    if (strcmp(item->val, (*tree)->val) < 0)
        insert(&(*tree)->left, item);
    else if (strcmp(item->val, (*tree)->val) > 0)
        insert(&(*tree)->right, item);
}

char *max_word(node * tree)
{
    static char *max = "";
    if (tree->left)
        max_word(tree->left);
    if (strlen(tree->word) > strlen(max))
        max = tree->word;
    if (tree->right)
        max_word(tree->right);
    if (strlen(tree->word) > strlen(max))
        max = tree->word;
    return max;
}

int depth(node * tree, int c)
{
    static int max;
    if (!c)
        max = 0;
    if (c > max)
        max = c;
    if (tree->left)
        depth(tree->left, c + 1);
    if (tree->right)
        depth(tree->right, c + 1);
    return max;
}

void free_tree(node * tree)
{
    if (tree->left)
        free_tree(tree->left);
    if (tree->right)
        free_tree(tree->right);
    free(tree->word);
    free(tree);
}

void readme(char *argv[])
{
    if (!strcmp(argv[1], "-h")) {
        printf
            ("Help: \n"
             "1) Enter count of items you need to add to the tree\n"
             "2) Enter value and word for each item\n");
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    node *curr, *root;
    int i, num_int;
    char num_char[MAX_NUM];
    root = NULL;
    if (argc > 1)
        readme(argv);
    puts("How many items you want to add to the tree?");
    fgets(num_char, MAX_NUM, stdin);
    num_int = atoi(num_char);
    if (num_int < 1) {
        puts("Please, enter right value(>0)");
        return 0;
    }
    for (i = 0; i < num_int; i++) {
        curr = (node *) malloc(sizeof(node));
        curr->word = (char *) calloc(MAX_WORD_SIZE, 1);
        curr->left = curr->right = NULL;
        printf("Enter value for %dth item\n", i + 1);
        fgets(curr->val, MAX_WORD_SIZE, stdin);
        printf("Enter word for %dth item\n", i + 1);
        fgets(curr->word, MAX_WORD_SIZE, stdin);
        insert(&root, curr);
    }
    if (root->left && root->right)
        if (depth(root->left, 0) <= depth(root->right, 0))
            printf("Max word is %s", max_word(root->left));
        else
            printf("Max word is %s", max_word(root->right));
    else
        puts("empty subtree");
    free_tree(root);
    return 0;
}
