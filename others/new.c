#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Node structure for syntax tree
typedef struct Node {
    char symbol;
    int position;
    int nullable;
    int firstPos[MAX];
    int lastPos[MAX];
    int firstPosCount;
    int lastPosCount;
    int index; // Unique index for adjacency matrix
    struct Node *left, *right;
} Node;

// Adjacency matrix
int adjacencyMatrix[MAX][MAX];
int nodeCount = 0;

// Initialize the adjacency matrix
void initAdjacencyMatrix() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

// Add edge to adjacency matrix
void addEdge(int parent, int child) {
    if (parent >= 0 && child >= 0) {
        adjacencyMatrix[parent][child] = 1;
    }
}

// Utility functions
void initArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

void addToArray(int *array, int *count, int value) {
    for (int i = 0; i < *count; i++) {
        if (array[i] == value) return;
    }
    array[(*count)++] = value;
}

void mergeArrays(int *dest, int *destCount, int *src, int srcCount) {
    for (int i = 0; i < srcCount; i++) {
        addToArray(dest, destCount, src[i]);
    }
}

// Create a new node
Node *createNode(char symbol) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->symbol = symbol;
    newNode->position = 0;
    newNode->nullable = 0;
    newNode->firstPosCount = 0;
    newNode->lastPosCount = 0;
    newNode->index = nodeCount++; // Assign unique index
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Build syntax tree from postfix expression
Node *buildSyntaxTree(char *postfix, int *positionCounter) {
    Node *stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        Node *newNode = createNode(c);

        if (isalnum(c)) { // Operand
            newNode->position = (*positionCounter)++;
            newNode->nullable = 0;
            addToArray(newNode->firstPos, &newNode->firstPosCount, newNode->position);
            addToArray(newNode->lastPos, &newNode->lastPosCount, newNode->position);
        } else if (c == '*') { // Unary operator
            newNode->left = stack[top--];
            newNode->nullable = 1;
            mergeArrays(newNode->firstPos, &newNode->firstPosCount, newNode->left->firstPos, newNode->left->firstPosCount);
            mergeArrays(newNode->lastPos, &newNode->lastPosCount, newNode->left->lastPos, newNode->left->lastPosCount);

            // Add edge for the syntax tree
            addEdge(newNode->index, newNode->left->index);
        } else if (c == '.' || c == '|') { // Binary operators
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            if (c == '|') {
                newNode->nullable = newNode->left->nullable || newNode->right->nullable;
                mergeArrays(newNode->firstPos, &newNode->firstPosCount, newNode->left->firstPos, newNode->left->firstPosCount);
                mergeArrays(newNode->firstPos, &newNode->firstPosCount, newNode->right->firstPos, newNode->right->firstPosCount);
                mergeArrays(newNode->lastPos, &newNode->lastPosCount, newNode->left->lastPos, newNode->left->lastPosCount);
                mergeArrays(newNode->lastPos, &newNode->lastPosCount, newNode->right->lastPos, newNode->right->lastPosCount);
            } else if (c == '.') {
                newNode->nullable = newNode->left->nullable && newNode->right->nullable;
                if (newNode->left->nullable) {
                    mergeArrays(newNode->firstPos, &newNode->firstPosCount, newNode->left->firstPos, newNode->left->firstPosCount);
                    mergeArrays(newNode->firstPos, &newNode->firstPosCount, newNode->right->firstPos, newNode->right->firstPosCount);
                } else {
                    mergeArrays(newNode->firstPos, &newNode->firstPosCount, newNode->left->firstPos, newNode->left->firstPosCount);
                }
                if (newNode->right->nullable) {
                    mergeArrays(newNode->lastPos, &newNode->lastPosCount, newNode->left->lastPos, newNode->left->lastPosCount);
                    mergeArrays(newNode->lastPos, &newNode->lastPosCount, newNode->right->lastPos, newNode->right->lastPosCount);
                } else {
                    mergeArrays(newNode->lastPos, &newNode->lastPosCount, newNode->right->lastPos, newNode->right->lastPosCount);
                }
            }

            // Add edges for the syntax tree
            addEdge(newNode->index, newNode->left->index);
            addEdge(newNode->index, newNode->right->index);
        }

        stack[++top] = newNode;
    }

    return stack[top];
}

// Print an array
void printArray(int *array, int count) {
    printf("{ ");
    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("}");
}

// Display node info
void displayNodeInfo(Node *node) {
    if (!node) return;
    displayNodeInfo(node->left);
    displayNodeInfo(node->right);

    printf("| %c | %d | ", node->symbol, node->nullable);
    printArray(node->firstPos, node->firstPosCount);
    printf(" | ");
    printArray(node->lastPos, node->lastPosCount);
    printf(" |\n");
}

// Display adjacency matrix
void displayAdjacencyMatrix() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    char postfix[MAX];
    printf("Enter the regular expression (in postfix): ");
    scanf("%s", postfix);

    int positionCounter = 1;
    initAdjacencyMatrix();
    Node *root = buildSyntaxTree(postfix, &positionCounter);

    printf("\nSyntax Tree Information:\n");
    printf("| Symbol | Nullable | FirstPos | LastPos |\n");
    printf("|--------|----------|----------------|----------------|\n");
    displayNodeInfo(root);

    displayAdjacencyMatrix();

    return 0;
}