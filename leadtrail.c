#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
bool isterm(char a)
{
    if(a=='+' || a=='*' || a==')' || a=='(' || (a>='a' && a<='z') || a==',')
        return true;
    return false;
}
bool ispresent(char arr[],char a,int ind)
{
    for(int i=0;i<ind;i++)
    {
        if(arr[i]==a)   
            return true;
    }
    return false;
}   
int main()
{
    int n;
    scanf("%d",&n);
    char productions[n][50];
    for(int i=0;i<n;i++)
    {
        scanf("%s",productions[i]);
    }
    char trailing[n][10],leading[n][10];
    //finding leading 
    for(int i=n-1;i>=0;i--)
    {
        int flag=0,ind=0;
        for(int j=3;j<strlen(productions[i]);j++)
        {
            if(productions[i][j]=='|')
            {
                flag=0;continue;
            }
            if(isterm(productions[i][j]) && flag==0)
            {
                if(!ispresent(leading[i],productions[i][j],ind))
                {
                    leading[i][ind++]=productions[i][j];
                    flag=1;
                }
            }
            else if(productions[i][j]>='A' && productions[i][j]<='Z' && flag==0)
            {
                int p=0;
                for(int k=0;k<n;k++)
                {
                    if(productions[k][0]==productions[i][j])
                    {
                        p=k;break;
                    }
                }
                for(int k=0;k<strlen(leading[p]);k++)
                {
                    if(!ispresent(leading[i],leading[p][k],ind))
                        leading[i][ind++]=leading[p][k];
                }
            }
        }
        leading[i][ind++]='\0';
    }
    for(int i=0;i<n;i++)
    {
        printf("%c : %s\n",productions[i][0],leading[i]);
    }
    //finding trailing
    for(int i=n-1;i>=0;i--)
    {
        int flag=0,ind=0;
        for(int j=strlen(productions[i])-1;j>=0;j--)
        {
            if(productions[i][j]=='|')
            {
                flag=0;continue;
            }
            if(isterm(productions[i][j]) && flag==0)
            {
                if(!ispresent(trailing[i],productions[i][j],ind))
                {
                    trailing[i][ind++]=productions[i][j];
                    flag=1;
                }
            }
            else if(productions[i][j]>='A' && productions[i][j]<='Z' && flag==0)
            {
                int p=0;
                for(int k=0;k<n;k++)
                {
                    if(productions[k][0]==productions[i][j])
                    {
                        p=k;break;
                    }
                }
                for(int k=0;k<strlen(leading[p]);k++)
                {
                    if(!ispresent(trailing[i],trailing[p][k],ind))
                        trailing[i][ind++]=trailing[p][k];
                }
            }
        }
        trailing[i][ind++]='\0';
    }
    for(int i=0;i<n;i++)
    {
        printf("%c : %s\n",productions[i][0],trailing[i]);
    }
}