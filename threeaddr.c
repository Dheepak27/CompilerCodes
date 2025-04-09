#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
char stack[100];
int top=-1;
int precedence(char a)
{
    if(a=='(') return 0;
    if(a=='+' || a=='-')    return 1;
    if(a=='*' || a=='/')    return 2;
    return -1;
}
void genTAC(char post[],int ind)
{
    char opst[100][100];int p=0;int t=1;
    for(int i=0;i<ind;i++)
    {
        if(isalnum(post[i]))
        {
            char op[2];
            op[0]=post[i];op[1]='\0';
            strcpy(opst[p++],op);
        }
        else if(post[i]=='=')
        {
            printf("%c = %s",post[0],opst[--p]);
        }
        else
        {
            char op1[5],op2[5],res[5];
            strcpy(op2,opst[--p]);
            strcpy(op1,opst[--p]);
            sprintf(res,"T%d",t++);
            printf("%s = %s %c %s\n",res,op1,post[i],op2);
            strcpy(opst[p++],res);
        }
    }
}
int main()
{
    char exp[50];char post[50];int ind=0;
    scanf("%s",exp);
    for(int i=0;i<strlen(exp);i++)
    {
        if(isalpha(exp[i]))
        {
            post[ind++]=exp[i];
        }
        else if(exp[i]=='(')
        {
            stack[++top]=exp[i];
        }
        else if(exp[i]==')')
        {
            while(stack[top]!='(')
            {
                post[ind++]=stack[top--];
            }
            top--;
        }
        else if(precedence(exp[i])<=precedence(stack[top]))
        {
            while(top!=-1 && precedence(exp[i])<=precedence(stack[top]))
            {
                post[ind++]=stack[top--];
            }
            stack[++top]=exp[i];
        }
        else
        {
            stack[++top]=exp[i];
        }
    }
    while(top!=-1)
        post[ind++]=stack[top--];
    post[ind]='\0';
    printf("%s\n",post);
    genTAC(post,ind);
}