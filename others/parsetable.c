#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool ispresent(char first[],char a,int ind)
{
   for(int i=0;i<ind;i++)
   {
        if(first[i]==a)
            return true;
   }
    return false;
} 
bool isterm(char a)
{
    if(a=='(' || a==')' || a=='+' || (a>='a' && a<='z' && a!='e') || a=='*')
        return true;
    return false;
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
    char first[n][10];
    char cfirst[26];
    for(int i=0;i<26;i++)
    {
        cfirst[i]=0;
    }
    for(int i=n-1;i>=0;i--)
    {
        int ind=0,flag=0,k=0;
        for(int j=3;j<strlen(productions[i]);j++)
        {
            if(k==1 && productions[i][j]!='|')
            {
                continue;
            }
            if(productions[i][j]=='|')
            {
                k=0;
                continue;
            }
            if((productions[i][j]>='a' && productions[i][j]<='z') || productions[i][j]=='+' || productions[i][j]=='(' 
            || productions[i][j]==')' || productions[i][j]=='*')
            {
                if(ispresent(first[i],productions[i][j],ind)==false)
                    first[i][ind++]=productions[i][j];
                if(j==3 || productions[i][j-1]=='|')
                    k=1;
            }
            else if(productions[i][j]>='A' && productions[i][j]<='Z' && (productions[i][j-1]=='|' || flag==1 || j==3))
            {  
                int find=0;
                while(productions[find][0]!=productions[i][j])
                    find++;
                for(int m=0;m<strlen(first[find]);m++)
                {
                    if(first[find][m]!='e')
                    {
                        if(ispresent(first[i],first[find][m],ind)==false)
                            first[i][ind++]=first[find][m];
                        flag=0;
                    }
                    else
                    {
                        flag=1;
                        break;
                    }
                }
            }
        }
        if(flag==1)
            first[i][ind++]='e';     
        first[i][ind++]='\0';
    }
    for(int i=0;i<n;i++)
    {
        printf("First of %c { ",productions[i][0]);
        for(int j=0;j<strlen(first[i]);j++)
        {
            printf("%c ",first[i][j]);
        }  
        printf("}\n");
    }
    char follow[n][10];
    for(int i=0;i<n;i++)
    {
        int ind=0,flag=0,k=0;
        if(i==0)
        {
            follow[i][ind++]='$'; 
        }
        for(int a=0;a<n;a++)
        {
            for(int b=3;b<strlen(productions[a]);b++)
            {
                if(a==i)break;
                if(productions[a][b]==productions[i][0] || flag==1)
                {
                    if(k==1 && productions[a][b]!='|')
                    {
                        continue;
                    }
                    if(productions[a][b]=='|')
                    {
                        k=0;
                        continue;
                    }
                    if((productions[a][b+1]>='a' && productions[a][b+1]<='z') || productions[a][b+1]=='+' 
                    || productions[a][b+1]=='(' || productions[a][b+1]==')' || productions[i][b+1]=='*')
                    {
                        if(ispresent(follow[i],productions[a][b+1],ind)==false)
                            follow[i][ind++]=productions[a][b+1];
                        flag=0;
                        k=1;
                    }
                    else if(b+1==strlen(productions[a]))
                    {
                        int find=0;
                        while(productions[find][0]!=productions[a][0])
                            find++;
                        for(int p=0;p<strlen(follow[find]);p++)
                        {
                            if(ispresent(follow[i],follow[find][p],ind)==false)
                                follow[i][ind++]=follow[find][p];
                        }
                        flag=0;
                    }
                    else if(productions[a][b+1]>='A' && productions[a][b+1]<='Z')
                    {
                        int find=0;
                        while(productions[find][0]!=productions[a][b+1])
                            find++;
                        for(int p=0;p<strlen(first[find]);p++)
                        {
                            if(first[find][p]!='e')
                            {
                                if(ispresent(follow[i],first[find][p],ind)==false)
                                    follow[i][ind++]=first[find][p];
                                flag=0;
                            }
                            if(first[find][p]=='e')
                            {
                                flag=1;
                                break;
                            }
                        }
                    }
                    
                }
            }
        }
        follow[i][ind++]='\0';
    }
    for(int i=0;i<n;i++)
    {
        printf("Follow of %c { ",productions[i][0]);
        for(int j=0;j<strlen(follow[i]);j++)
        {
            printf("%c ",follow[i][j]);
        }  
        printf("}\n");
    }
    for(int i=0;i<n;i++)
    {
        int flag=0;
        for(int j=3;j<strlen(productions[i]);j++)
        {
            if(j==3)
            {
                if(isterm(productions[i][j]))
                {
                    char prod[50];int ind=0;
                    for(int k=j;k<strlen(productions[i]);k++)
                    {
                        if(productions[i][k]=='|' || k==strlen(productions[i]))
                            break;
                        prod[ind++]=productions[i][k];
                    }
                    prod[ind++]='\0';
                    printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],productions[i][j]);
                    flag=1;

                }
                if(productions[i][j]>='A' && productions[i][j]<='Z')
                {
                    char prod[50];int ind=0,t=0;
                    for(int k=j;k<strlen(productions[i]);k++)
                    {
                        if(productions[i][k]=='|' || k==strlen(productions[i]))
                            break;
                        prod[ind++]=productions[i][k];
                    }
                    prod[ind++]='\0';
                   
                    while(productions[t][0]!=productions[i][j])
                        t++;
                    for(int k=0;k<strlen(first[t]);k++)
                    {
                        if(first[t][k]!='e')
                            printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],first[t][k]);
                    }
                    flag=1;
                }

            }

            if(productions[i][j]=='|')
            {
                if(isterm(productions[i][j+1]))
                {
                    char prod[50];int ind=0;
                    for(int k=j+1;k<strlen(productions[i]);k++)
                    {
                        if(productions[i][k]=='|' || k==strlen(productions[i]))
                            break;
                        prod[ind++]=productions[i][k];
                    }
                    prod[ind++]='\0';
                    printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],productions[i][j+1]);
                    flag=1;
                }
                if(productions[i][j+1]=='e')
                {
                    int t=0;
                    while(productions[t][0]!=productions[i][0])
                        t++;
                    for(int m=0;m<strlen(follow[t]);m++)
                        printf("%c->e,M[%c,%c]\n",productions[i][0],productions[i][0],follow[t][m]);
                    flag=1;
                    
                }
                if(productions[i][j+1]>='A' && productions[i][j+1]<='Z')
                {
                    char prod[50];int ind=0,t=0;
                    for(int k=j+1;k<strlen(productions[i]);k++)
                    {
                        if(productions[i][k]=='|' || k==strlen(productions[i]))
                            break;
                        prod[ind++]=productions[i][k];
                    }
                    prod[ind++]='\0';
                   
                    while(productions[t][0]!=productions[i][j])
                        t++;
                    for(int k=0;k<strlen(first[t]);k++)
                    {
                        if(first[t][k]!='e')
                            printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],first[t][k]);
                    }
                    flag=1;
                }
            }
        }
    }   
}