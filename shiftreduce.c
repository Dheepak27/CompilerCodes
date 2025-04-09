#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void printSt(char stack[],int top)
{
    for(int i=0;i<=top;i++)
        printf("%c",stack[i]);
    printf("\t\t");
}
void printString(char string[],int t)
{
    for(int i=t;i<strlen(string);i++)
        printf("%c",string[i]);
    printf("\t\t");
}
int main()
{
    int n;
    printf("Enter number of productions\n");
    scanf("%d",&n);
    char productions[n][50];
    printf("Enter Productions\n");
    for(int i=0;i<n;i++)
    {
        scanf("%s",productions[i]);
    }
    char stack[50];
    int top=-1;
    stack[++top]='$';
    char string[50];
    printf("Enter String\n");
    scanf("%s",string);
    int ind=strlen(string);
    string[ind++]='$';
    string[ind++]='\0';
    int t=0;
    printf("Stack\t\tInput\t\tAction\n");
    printSt(stack,top);
    printString(string,t);
    int co=0,k;
    for(int i=0;i<n;i++)
    {
        if(productions[i][0]==productions[0][0])
            co++;
    }
    while(true)
    {
        k=0;
        if(stack[top]!='$')
        {
            for(int i=0;i<n;i++)
            {
                if((productions[i][3]==stack[top] && strlen(productions[i])==4 && (productions[i][0]!=productions[0][0] || co==n))
                || (productions[i][3]==stack[top] && strlen(productions[i])==4 && t+1==strlen(string)))
                {
                    printSt(stack,top);
                    printString(string,t);
                    printf("Reduce by %s\n",productions[i]);
                    top--;
                    stack[++top]=productions[i][0];
                    k=1;
                    // printf("1\n");
                    continue;
                }
                if(strlen(productions[i])>=4 && top>=2)
                {
                    char p[10];int tind=0,x=1;
                    for(int j=3;j<strlen(productions[i]);j++)
                    {
                        p[tind++]=productions[i][j];
                    
                    }
                    while(x<top)
                    {
                        char st1[10];int sind=0;
                        for(int i=x;i<=top;i++)
                        {
                            st1[sind++]=stack[i];
                        }
                        p[tind++]='\0';
                        st1[sind++]='\0';
                        if(strcmp(p,st1)==0)
                        {
                            printSt(stack,top);
                            printString(string,t);
                            printf("Reduce by %s\n",productions[i]);
                            while(sind>1)
                            {
                                top--;sind--;
                            }
                            stack[++top]=productions[i][0];
                            k=1;
                        }
                        x++;
                    }
                    // printf("2\n");
                }
            }
        }
        if(stack[0]=='$' && (stack[1]=='S' || stack[1]=='E' || stack[1]=='C') && t+1==strlen(string) && top==1)
        {
            printSt(stack,top);
            printString(string,t);
            printf("Accepted");break;
        }
        if((t<strlen(string) && string[t]!='$' && k==0))
        {
            if(t!=0)
            {
                printSt(stack,top);
                printString(string,t);
            }
            printf("Shift\n");
            stack[++top]=string[t++];
            k=1;
        }
        if(k==0 && t+1==strlen(string))
        {
            printSt(stack,top);
            printString(string,t);
            printf("Rejected");break;
        }
        // co++;
        // // printf("%d\n",t);
    }
}