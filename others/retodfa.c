#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct Node
{
    char data;
    struct Node* left;
    struct Node* right;
    int firstpos[50];
    int lastpos[50];
    int firstposSize;
    int lastposSize;
}Node;
Node* createNode(char data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->firstposSize = 0;
    newNode->lastposSize = 0;
    return newNode;
}
bool isoperator(char ch)
{
    if(ch=='|' || ch=='+' || ch=='*' || ch=='(' || ch==')')
        return true;
    return false;
}
int main()
{ 
    char re[50];
    scanf("%s",re);
    char augre[50];
    int ind=0;
    for(int i=0;i<strlen(re)-1;i++)
    {
        if((isalpha(re[i]) && isalpha(re[i+1])) || (re[i]=='*' && isalpha(re[i+1])))
        {
            augre[ind++]=re[i];
            augre[ind++]='.';
        }
        else if(re[i]=='('&& isalpha(re[i+1]) && i!=0)
        {
            augre[ind++]='.';
            augre[ind++]=re[i];
        }
        else if((re[i]=='*' && isalpha(re[i+1])) || (re[i]==')'&& isalpha(re[i+1]))) 
        {
            augre[ind++]=re[i];
            augre[ind++]='.';
        }
        else
        {
            augre[ind++]=re[i];
        }
    }
    augre[ind++]=re[strlen(re)-1];
    augre[ind++]='.';
    augre[ind++]='#';
    printf("Augmneted RE: %s\n",augre);
    char nodes[50],operators[50];
    int ind1=0,ind2=0;
    for(int i=0;i<strlen(augre);i++)
    {
        if(isalpha(augre[i]) || augre[i]=='#')
            nodes[ind1++]=augre[i];        
        else if(!isalpha(augre[i]) && augre[i]!=')' && augre[i]!='(')
            operators[ind2++]=augre[i];
    }
    for(int i=0;i<ind1;i++)
    {
        printf("%c ",nodes[i]);
    }
    printf("\n");
    for(int i=0;i<ind2;i++)
    {
        printf("%c ",operators[i]);
    }
    Node* root=NULL;
    printf("\n");
    int i=0,k=0,temp1=ind1,temp2=ind2;
    root=createNode(operators[temp2-1]);
    Node* head=root;
    while(temp2>=2 && temp1>=1)
    {
        if(k==1)
        {
            Node* node1=createNode(operators[temp2-2]);
            root->left=node1;
            temp2--;
            k=0;
        }
        else if(operators[temp2-2]!='*')
        {   
            Node* node1=createNode(operators[temp2-2]);
            Node* node2=createNode(nodes[temp1-1]);
            root->left=node1;
            root->right=node2;
            temp2--;temp1--;
        }
        else if(operators[temp2-2]=='*')
        {
            Node* node1=createNode(operators[temp2-2]);
            Node* node2=createNode(nodes[temp1-1]);
            root->left=node1;
            root->right=node2;
            temp2--;temp1--;
            k=1;
        }
        root=root->left;
        Node* node1=createNode(nodes[temp1-2]);
        Node* node2=createNode(nodes[temp1-1]);
        root->left=node1;
        root->right=node2;
    }
    structure(head,0);
    printTree(head);
    printf("Reverse Postorder Traversal with Firstpos and Lastpos:\n");
    reversePostorder(root);
}

void printFirstAndLast(Node* root) {
    if (root == NULL) return;

    printf("Node: %c\n", root->data);
    printf("Firstpos: { ");
    for (int i = 0; i < root->firstposSize; i++) {
        printf("%d ", root->firstpos[i]);
    }
    printf("}\n");
    printf("Lastpos: { ");
    for (int i = 0; i < root->lastposSize; i++) {
        printf("%d ", root->lastpos[i]);
    }
    printf("}\n");
}

// Function to compute firstpos and lastpos for all nodes
void computeFirstAndLast(Node* root, int* pos) {
    if (root == NULL) return;

    if (isalpha(root->data) || root->data == '#') { // Leaf nodes
        root->firstpos[root->firstposSize++] = (*pos);
        root->lastpos[root->lastposSize++] = (*pos);
        (*pos)++;
    } else if (root->data == '.') { // Concatenation
        computeFirstAndLast(root->left, pos);
        computeFirstAndLast(root->right, pos);

        // Firstpos
        for (int i = 0; i < root->left->firstposSize; i++) {
            root->firstpos[root->firstposSize++] = root->left->firstpos[i];
        }
        if (root->left->data == '*' || root->left->data == '|') {
            for (int i = 0; i < root->right->firstposSize; i++) {
                root->firstpos[root->firstposSize++] = root->right->firstpos[i];
            }
        }

        // Lastpos
        for (int i = 0; i < root->right->lastposSize; i++) {
            root->lastpos[root->lastposSize++] = root->right->lastpos[i];
        }
        if (root->right->data == '*' || root->right->data == '|') {
            for (int i = 0; i < root->left->lastposSize; i++) {
                root->lastpos[root->lastposSize++] = root->left->lastpos[i];
            }
        }
    } else if (root->data == '|') { // Union
        computeFirstAndLast(root->left, pos);
        computeFirstAndLast(root->right, pos);

        // Firstpos
        for (int i = 0; i < root->left->firstposSize; i++) {
            root->firstpos[root->firstposSize++] = root->left->firstpos[i];
        }
        for (int i = 0; i < root->right->firstposSize; i++) {
            root->firstpos[root->firstposSize++] = root->right->firstpos[i];
        }

        // Lastpos
        for (int i = 0; i < root->left->lastposSize; i++) {
            root->lastpos[root->lastposSize++] = root->left->lastpos[i];
        }
        for (int i = 0; i < root->right->lastposSize; i++) {
            root->lastpos[root->lastposSize++] = root->right->lastpos[i];
        }
    } else if (root->data == '*') { // Kleene star
        computeFirstAndLast(root->left, pos);

        // Firstpos and Lastpos are the same as the child
        for (int i = 0; i < root->left->firstposSize; i++) {
            root->firstpos[root->firstposSize++] = root->left->firstpos[i];
        }
        for (int i = 0; i < root->left->lastposSize; i++) {
            root->lastpos[root->lastposSize++] = root->left->lastpos[i];
        }
    }
}
void reversePostorder(Node* root) {
    if (root == NULL) return;

    reversePostorder(root->right);
    reversePostorder(root->left);
    printFirstAndLast(root);
}

void printTree(Node* root) 
{
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%c ", root->data);
    printTree(root->right);
}

void padding ( char ch, int n )
{
  int i;

  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure (Node *root, int level )
{
  int i;

  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->right, level + 1 );
    padding ( '\t', level );
    printf ( "%c\n", root->data );
    structure ( root->left, level + 1 );
  }
}
