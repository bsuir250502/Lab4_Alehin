#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NUM 30
#define MAX_WORD_SIZE 1024
#define MAX_TREE_DEPTH 1024

struct tree_el {
    char val[MAX_WORD_SIZE];
    char *word;
    struct tree_el *right, *left;
};

typedef struct tree_el node;

struct stack_str {
    char *data;
    struct stack_str *prev;
};

typedef struct stack_str stack_el;

stack_el *push(char *content, stack_el * head)
{
    stack_el *newhead = (stack_el *) malloc(sizeof(stack_el));
    newhead->data = content;
    newhead->prev = head;
    return newhead;
}

stack_el *pop(stack_el * head)
{
    stack_el *prev_elem;
    if (!head)
        return 0;
    prev_elem = head->prev;
    free(head);
    return prev_elem;
}

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

void max_word(stack_el * stack_head)
{
    static char *max;
    if (!stack_head)
        printf("Max word is %s", max);
    else
        max = "";
    while (stack_head) {
        if (strlen(stack_head->data) > strlen(max))
            max = stack_head->data;
        stack_head = stack_head->prev;
    }
}

int min_subtree(node * tree, int c)
{
    static int min = MAX_TREE_DEPTH;
    static stack_el *stack_head = NULL;
    if (tree->left) {
        stack_head = push(tree->word, stack_head);
        min_subtree(tree->left, c + 1);
    }
    if (tree->right) {
        stack_head = push(tree->word, stack_head);
        min_subtree(tree->right, c + 1);
    }
    if (c < min && !tree->left && !tree->right) {
        stack_head = push(tree->word, stack_head);
        max_word(stack_head);
        min = c;
    }
    stack_head = pop(stack_head);
    if (!c) {
        stack_head = pop(stack_head);
        max_word(stack_head);
    }
    return min;
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
    printf("Min subtree depth - %d\n", min_subtree(root, 0) + 1);
    free_tree(root);
    return 0;
}
