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
}Node;
Node* createNode(char data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
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
    printf("Nodes: ");
    for(int i=0;i<ind1;i++)
    {
        printf("%c ",nodes[i]);
    }
    printf("\nOperators:");
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


