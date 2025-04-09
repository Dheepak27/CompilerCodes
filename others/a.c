#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char symbol;
    struct node *left, *right;
    int nullable;
    char firstpos[10], lastpos[10];
} Node;

Node* createNode(char symbol) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->symbol = symbol;
    newNode->left = newNode->right = NULL;
    strcpy(newNode->firstpos, "");
    strcpy(newNode->lastpos, "");
    return newNode;
}

void compute(Node *root) {
    if (!root) return;
    compute(root->left);
    compute(root->right);

    if (!root->left && !root->right) {
        root->nullable = 0;
        sprintf(root->firstpos, "%c", root->symbol);
        sprintf(root->lastpos, "%c", root->symbol);
    } else if (root->symbol == '|') {
        root->nullable = root->left->nullable || root->right->nullable;
        sprintf(root->firstpos, "%s%s", root->left->firstpos, root->right->firstpos);
        sprintf(root->lastpos, "%s%s", root->left->lastpos, root->right->lastpos);
    } else if (root->symbol == '.') {
        root->nullable = root->left->nullable && root->right->nullable;
        strcpy(root->firstpos, root->left->firstpos);
        if (root->left->nullable)
            strcat(root->firstpos, root->right->firstpos);
        strcpy(root->lastpos, root->right->lastpos);
        if (root->right->nullable)
            strcat(root->lastpos, root->left->lastpos);
    } else if (root->symbol == '*') {
        root->nullable = 1;
        strcpy(root->firstpos, root->left->firstpos);
        strcpy(root->lastpos, root->left->lastpos);
    }
}

void print(Node *root) {
    if (!root) return;
    print(root->left);
    print(root->right);
    printf("Node '%c': Firstpos: %s, Lastpos: %s, Nullable: %d\n", root->symbol, root->firstpos, root->lastpos, root->nullable);
}

int main() {
    // Building (a|b)*.a
    Node *a = createNode('a');
    Node *b = createNode('b');
    Node *or = createNode('|'); or->left = a; or->right = b;
    Node *star = createNode('*'); star->left = or;
    Node *a2 = createNode('a');
    Node *concat = createNode('.'); concat->left = star; concat->right = a2;

    compute(concat);
    print(concat);
    return 0;
}
