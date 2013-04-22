#include<stdlib.h>
#include<stdio.h>

struct tree_el {
    int val;
	int word;
    struct tree_el *right, *left;
};

typedef struct tree_el node;

void insert(node ** tree, node * item)
{
    if (!(*tree)) {
        *tree = item;
        return;
    }
    if (item->val < (*tree)->val)
        insert(&(*tree)->left, item);
    else if (item->val > (*tree)->val)
        insert(&(*tree)->right, item);
}
int max_word(node * tree)
{    
	static int max;
	if (tree->left)
        max_word(tree->left);
	if (tree->word > max) max = tree->word;
    if (tree->right)
        max_word(tree->right);
	if (tree->word > max) max = tree->word;
	return max;
}
int depth(node * tree, int c)
{
	static int max;
	if (!c) max = 0;
	if (c > max) max=c;
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
    free(tree);
}

void printout(node * tree)
{
    if (tree->left)
        printout(tree->left);
    printf("%d\n", tree->val);
    if (tree->right)
        printout(tree->right);
}

int main()
{
    node *curr, *root;
    int i;

    root = NULL;

    for (i = 1; i <= 10; i++) {
        curr = (node *) malloc(sizeof(node));
        curr->left = curr->right = NULL;
		scanf("%d %d", &curr->val, &curr->word);
        /*curr->val = rand(); */
        insert(&root, curr);
    }
    puts("###");
    printout(root);
    puts("###");
	printf("%d\n", depth(root->left, 0));
	printf("%d\n", depth(root->right, 0));
	if(depth(root->left, 0) <= depth(root->right, 0))
		printf("%d\n", max_word(root->left));
	else 
		printf("%d\n", max_word(root->right));
    free_tree(root);
    return 0;
}
