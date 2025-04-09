#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define N 100
char stack[N];
int top = -1;

typedef struct Node{
    char symbol;
    int position;
    int nullable;
    int firstPos[N];
    int lastPos[N];
    int firstPosCount;
    int lastPosCount;
    int index;
    struct Node *left,*right;
}Node;

int adjacencyMatrix[N][N];
int nodeCount=0;

void initAdjacencyMatrix(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            adjacencyMatrix[i][j]=0;
        }
    }
}

void addEdge(int parent,int child){
    if(parent>=0&&child>=0){
        adjacencyMatrix[parent][child]=1;
    }
}

void initArray(int *array,int size){
    for(int i=0;i<size;i++){
        array[i]=0;
    }
}

void addToArray(int *array,int *count,int value){
    for(int i=0;i<*count;i++){
        if(array[i]==value)return;
    }
    array[(*count)++]=value;
}

void mergeArrays(int *dest,int *destCount,int *src,int srcCount){
    for(int i=0;i<srcCount;i++){
        addToArray(dest,destCount,src[i]);
    }
}

Node* createNode(char symbol){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->symbol=symbol;
    newNode->position=0;
    newNode->nullable=0;
    newNode->firstPosCount=0;
    newNode->lastPosCount=0;
    newNode->index=nodeCount++;
    newNode->left=newNode->right=NULL;
    return newNode;
}

Node* buildSyntaxTree(char *postfix,int *positionCounter){
    Node* stack[N];
    int top=-1;

    for(int i=0;postfix[i]!='\0';i++){
        char c=postfix[i];
        Node* newNode=createNode(c);

        if(isalnum(c)){
            newNode->position=(*positionCounter)++;
            newNode->nullable=0;
            addToArray(newNode->firstPos,&newNode->firstPosCount,newNode->position);
            addToArray(newNode->lastPos,&newNode->lastPosCount,newNode->position);
        }else if(c=='*'){
            newNode->left=stack[top--];
            newNode->nullable=1;
            mergeArrays(newNode->firstPos,&newNode->firstPosCount,newNode->left->firstPos,newNode->left->firstPosCount);
            mergeArrays(newNode->lastPos,&newNode->lastPosCount,newNode->left->lastPos,newNode->left->lastPosCount);
            addEdge(newNode->index,newNode->left->index);
        }else if(c=='.'||c=='|'){
            newNode->right=stack[top--];
            newNode->left=stack[top--];
            if(c=='|'){
                newNode->nullable=newNode->left->nullable||newNode->right->nullable;
                mergeArrays(newNode->firstPos,&newNode->firstPosCount,newNode->left->firstPos,newNode->left->firstPosCount);
                mergeArrays(newNode->firstPos,&newNode->firstPosCount,newNode->right->firstPos,newNode->right->firstPosCount);
                mergeArrays(newNode->lastPos,&newNode->lastPosCount,newNode->left->lastPos,newNode->left->lastPosCount);
                mergeArrays(newNode->lastPos,&newNode->lastPosCount,newNode->right->lastPos,newNode->right->lastPosCount);
            }else if(c=='.'){
                newNode->nullable=newNode->left->nullable&&newNode->right->nullable;
                if(newNode->left->nullable){
                    mergeArrays(newNode->firstPos,&newNode->firstPosCount,newNode->left->firstPos,newNode->left->firstPosCount);
                    mergeArrays(newNode->firstPos,&newNode->firstPosCount,newNode->right->firstPos,newNode->right->firstPosCount);
                }else{
                    mergeArrays(newNode->firstPos,&newNode->firstPosCount,newNode->left->firstPos,newNode->left->firstPosCount);
                }
                if(newNode->right->nullable){
                    mergeArrays(newNode->lastPos,&newNode->lastPosCount,newNode->left->lastPos,newNode->left->lastPosCount);
                    mergeArrays(newNode->lastPos,&newNode->lastPosCount,newNode->right->lastPos,newNode->right->lastPosCount);
                }else{
                    mergeArrays(newNode->lastPos,&newNode->lastPosCount,newNode->right->lastPos,newNode->right->lastPosCount);
                }
            }
            addEdge(newNode->index,newNode->left->index);
            addEdge(newNode->index,newNode->right->index);
        }

        stack[++top]=newNode;
    }

    return stack[top];
}

void printArray(int *array,int count){
    printf("{ ");
    for(int i=0;i<count;i++){
        printf("%d ",array[i]);
    }
    printf("}");
}

void displayNodeInfo(Node *node){
    if(!node)return;
    displayNodeInfo(node->left);
    displayNodeInfo(node->right);

    printf("| %c | ",node->symbol);
    printArray(node->firstPos,node->firstPosCount);
    printf(" | ");
    printArray(node->lastPos,node->lastPosCount);
    printf(" |\n");
}

void displayAdjacencyMatrix(){
    printf("\nAdjacency Matrix:\n");
    for(int i=0;i<nodeCount;i++){
        for(int j=0;j<nodeCount;j++){
            printf("%d ",adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void push(char c) {
    if (top == N - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack[top--];
}

char peek() {
    if (top == -1) {
        return '\0';
    }
    return stack[top];
}

int precedence(char op) {
    if (op == '*') return 3;      
    if (op == '.') return 2;    
    if (op == '|') return 1;    
    return 0;                    
}


int isOperator(char c) {
    return c == '|' || c == '.' || c == '*';
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
    printf ( "%c\n", root->symbol );
    structure ( root->left, level + 1 );
  }
}


int main(){
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
    char postfix[N]; 
    int k = 0; 
    for (int i = 0; i < strlen(augre)-2; i++) {
        char c = augre[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (peek() != '(') {
                postfix[k++] = pop();
            }
            pop();
        } else if (isOperator(c)) {
            while (top != -1 && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; 
    printf("Postfix: %s",postfix);
    int positionCounter=1;
    initAdjacencyMatrix();
    Node* root=buildSyntaxTree(postfix,&positionCounter);

    printf("\nFirstPos() and LastPos()\n");
    printf("| Symbol | FirstPos | LastPos |\n");
    displayNodeInfo(root);
    structure(root,0);
    displayAdjacencyMatrix();

    return 0;
}
