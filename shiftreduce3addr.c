#include <stdio.h>
 #include <ctype.h>
 #include <string.h>
 int precedence(char a)
 {
    if(a=='=')return 0;
    if(a=='+' || a=='-')return 1;
    if(a=='*' || a=='/')return 2;
    return -1;
 }
 void genTAC(char post[])
 {
    printf("Stack\t\tInput Buffer\t\tAction\n");
    char opst[50][50];int ind=0,t=1;
    for(int i=0;i<strlen(post);i++)
    {
        if(post[i]>='a' && post[i]<='z')
        {
            char operand[2];operand[0]=post[i],operand[1]='\0';
            for(int i=0;i<ind;i++)
            {
                for(int j=0;j<strlen(opst[i]);j++)
                {
                    printf("%c",opst[i][j]);
                }
            }
            printf("\t\t");
            for(int k=i;k<strlen(post);k++)
            {
                printf("%c",post[k]);
            }
            printf("\t\t");
            printf("Shift");
            strcpy(opst[ind++],operand);
            printf("\n");
        }
        else if(post[i]=='=')
        {
            for(int i=0;i<ind;i++)
            {
                for(int j=0;j<strlen(opst[i]);j++)
                {
                    printf("%c",opst[i][j]);
                }
            }
            printf("\t\t");
            for(int k=i;k<strlen(post);k++)
            {
                printf("%c",post[k]);
            }
            printf("\t\t");
            printf("Reduce ");
            printf("%c %c %s\n",post[0],post[i],opst[--ind]);
        }
        else
        {
            for(int i=0;i<ind;i++)
            {
                for(int j=0;j<strlen(opst[i]);j++)
                {
                    printf("%c",opst[i][j]);
                }
            }
            printf("\t\t");
            for(int k=i;k<strlen(post);k++)
            {
                printf("%c",post[k]);
            }
            printf("\t\t");printf("Reduce ");
            char op1[50],op2[50],res[50];
            strcpy(op2,opst[--ind]);
            strcpy(op1,opst[--ind]);
            sprintf(res,"T%d",t);
            t++;
            printf("%s = %s %c %s\n",res,op1,post[i],op2);
            strcpy(opst[ind++],res);
        }
    }
 }
 int main()
 {
    char exp[50];
    scanf("%s",exp);
    char post[50];int ind=0;char stack[50];int top=-1;
    for(int i=0;i<strlen(exp);i++)
    {
        if(exp[i]>='a' && exp[i]<='z')
        {
            post[ind++]=exp[i];
        }
        else if(exp[i]=='(')
        {
            stack[++top]=exp[i];
        }
        else if(exp[i]==')')
        {
            while(top!=-1 && stack[top]!='(')
            {
                post[ind++]=stack[top--];
            }
            top--;
        }
        else
        {
            while(precedence(stack[top])>=precedence(exp[i]))
            {
                post[ind++]=stack[top--];
            }
            stack[++top]=exp[i];
        }
    }
    while(top!=-1)
    {
        post[ind++]=stack[top--];
    }
    post[ind]='\0';
    printf("%s\n",post);
    genTAC(post);
 }