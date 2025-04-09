#include <stdio.h>
#include <ctype.h>
#include <string.h>
void printst(char stack[],int top)
{
    for(int i=0;i<=top;i++)
    {
        printf("%c",stack[i]);
    }
    printf("\t\t");
}
void printstring(int ind,char string[])
{
    for(int i=ind;i<strlen(string);i++)
    {
        printf("%c",string[i]);
    }
    printf("\t\t");
}
int main()
{
    int n;
    scanf("%d",&n);
    char productions[n][10];
    for(int i=0;i<n;i++)
    {
        scanf("%s",productions[i]);
    }
    char string[10];char stack[10];
    scanf("%s",string);int top=-1;
    printf("Stack\t\tInputBuffer\tAction\n");
    stack[++top]='$';int ind=0,flag,c=0;
    printst(stack,top);
    printstring(ind,string);
    printf("\n");
    while(c<6)
    {
        flag=0;
        for(int i=0;i<n;i++)
        {
            char rhs[50],temp[50];int k=0,m=0;
            for(int j=3;j<strlen(productions[i]);j++)
                rhs[k++]=productions[i][j];
            for(int j=1;j<=top;j++)
            {
                temp[m++]=stack[j];
            }
            rhs[k]='\0';
            temp[m]='\0';
            if(strcmp(rhs,temp)==0)
            {
                top-=strlen(rhs);
                printst(stack,top);
                printstring(ind,string);
                printf("Reduce %s\n",productions[i]);
                stack[++top]=productions[i][0];
                flag=1;
                break;
            }
            else if(stack[top]==rhs[0] && strlen(rhs)==1)
            {
                top--;
                printst(stack,top);
                printstring(ind,string);
                printf("Reduce %s\n",productions[i]);
                stack[++top]=productions[i][0];
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            stack[++top]=string[ind++];
            printst(stack,top);
            printstring(ind,string);
            printf("Shift\n");
        }
        c++;
    }
}