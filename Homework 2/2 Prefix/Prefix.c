#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

// Define structure for each node in the call tree
struct Node
{
    int start;
    int end;
    struct Node *left;
    struct Node *right;
};

// Create a new node in the call tree
struct Node *newNode(int start, int end)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->start = start;
    node->end = end;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Insert a node into the call tree
struct Node *insertNode(struct Node *root, int start, int end)
{
    if (root == NULL)
    {
        return newNode(start, end);
    }
    else if (end < root->start)
    {
        root->left = insertNode(root->left, start, end);
    }
    else
    {
        root->right = insertNode(root->right, start, end);
    }
    return root;
}

// Print the call tree in Graphviz format
void printTree(struct Node *root, FILE *fp)
{
    if (root != NULL)
    {
        if (root->left != NULL)
        {
            fprintf(fp, "    %d-%d -> %d-%d;\n", root->start, root->end, root->left->start, root->left->end);
        }
        if (root->right != NULL)
        {
            fprintf(fp, "    %d-%d -> %d-%d;\n", root->start, root->end, root->right->start, root->right->end);
        }
        printTree(root->left, fp);
        printTree(root->right, fp);
    }
}

int main()
{
    // Read input
    int n;
    printf("Give me the number of functions: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("Give me the %d. function start and end point: ", i + 1);
        scanf("%d", &arr[i]);
    }

    // Create call tree
    struct Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insertNode(root, i, arr[i]);
    }

    // Print call tree in Graphviz format
    FILE *fp = fopen("call_tree.dot", "w");
    fprintf(fp, "digraph {\n");
    printTree(root, fp);
    fprintf(fp, "}\n");
    fclose(fp);

    // Free memory
    free(arr);

    return 0;
}