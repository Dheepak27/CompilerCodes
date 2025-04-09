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
void printSting(char st[],int t)
{
    for(int i=t;i<strlen(st);i++)
        printf("%c",st[i]);
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
    printf("First and Follow\n");
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
    char term[10],nonterm[10];
    int teind=0,nind=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<strlen(productions[i]);j++)
        {
            if(((productions[i][j]>='a' && productions[i][j]<='z' && productions[i][j]!='e') || isterm(productions[i][j])) 
            && ispresent(term,productions[i][j],teind)==false) 
            {
                term[teind++]=productions[i][j];
            }   
            else if(productions[i][j]>='A' && productions[i][j]<='Z' && ispresent(nonterm,productions[i][j],nind)==false)
            {
                nonterm[nind++]=productions[i][j];
            }
        }
    }
    term[teind++]='$';

    char table[nind][teind][10];
    for(int i=0;i<nind;i++)
    {
        for(int j=0;j<teind;j++)
        {
            table[i][j][0]='.';
            table[i][j][1]='\0';
        }
    }
    printf("Parse Table Entries\n");
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
                    int tep=0,ntp=0;
                    for(int te=0;te<teind;te++)
                    {
                        if(term[te]==productions[i][j])
                            tep=te;
                    }
                    for(int nt=0;nt<nind;nt++)
                    {
                        if(nonterm[nt]==productions[i][0])
                            ntp=nt;
                    }
                    strcpy(table[ntp][tep],prod);
                    table[ntp][tep][strlen(table[ntp][tep])]='\0';
                    printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],productions[i][j]);
                    flag=1;
                }
                if(productions[i][j]>='A' && productions[i][j]<='Z')
                {
                    char prod[50];int ind=0,t=0;int tep=0,ntp=0;
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
                        {
                            for(int te=0;te<teind;te++)
                            {
                                if(term[te]==first[t][k])
                                    tep=te;
                            }
                            for(int nt=0;nt<nind;nt++)
                            {
                                if(nonterm[nt]==productions[i][0])
                                    ntp=nt;
                            }
                            strcpy(table[ntp][tep],prod);
                            table[ntp][tep][strlen(table[ntp][tep])]='\0';
                            printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],first[t][k]);
                        }
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
                    int tep=0,ntp=0;
                    for(int te=0;te<teind;te++)
                    {
                        if(term[te]==productions[i][j+1])
                            tep=te;
                    }
                    for(int nt=0;nt<nind;nt++)
                    {
                        if(nonterm[nt]==productions[i][0])
                            ntp=nt;
                    }
                    strcpy(table[ntp][tep],prod);
                    table[ntp][tep][strlen(table[ntp][tep])]='\0';
                    printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],productions[i][j+1]);
                    flag=1;
                }
                if(productions[i][j+1]=='e')
                {
                    int t=0;
                    while(productions[t][0]!=productions[i][0])
                        t++;
                    for(int m=0;m<strlen(follow[t]);m++)
                    {
                        int tep=0,ntp=0;
                        for(int te=0;te<teind;te++)
                        {
                            if(term[te]==follow[t][m])
                                tep=te;
                        }
                        for(int nt=0;nt<nind;nt++)
                        {
                            if(nonterm[nt]==productions[i][0])
                                ntp=nt;
                        }
                        strcpy(table[ntp][tep],"e");
                        table[ntp][tep][strlen(table[ntp][tep])]='\0';
                        printf("%c->e,M[%c,%c]\n",productions[i][0],productions[i][0],follow[t][m]);
                    }
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
                        {
                            int tep=0,ntp=0;
                            for(int te=0;te<teind;te++)
                            {
                                if(term[te]==first[t][k])
                                    tep=te;
                            }
                            for(int nt=0;nt<nind;nt++)
                            {
                                if(nonterm[nt]==productions[i][0])
                                    ntp=nt;
                            }
                            strcpy(table[ntp][tep],prod);
                            table[ntp][tep][strlen(table[ntp][tep])]='\0';
                            printf("%c->%s,M[%c,%c]\n",productions[i][0],prod,productions[i][0],first[t][k]);
                        }
                    }
                    flag=1;
                }
            }
        }
    }   
    // for(int i=0;i<teind;i++)
    // {
    //     printf("%c",term[i]);
    // }
    // printf("\n");
    // for(int j=0;j<nind;j++)
    // {
    //     printf("%c",nonterm[j]);
    // }
    printf("Parse Table\n");
    printf("\t");
    for(int i=0;i<teind;i++)
    {
        printf("%c\t",term[i]);
    }
    printf("\n");
    for(int i=0;i<nind;i++)
    {
        printf("%c\t",nonterm[i]);
        for(int j=0;j<teind;j++)
        {
            printf("%s\t",table[i][j]);
        }
        printf("\n");
    }
    printf("Parsing\n");
    char st[50];
    scanf("%s",st);
    int k=strlen(st);
    st[k]='$';
    st[k+1]='\0';
    char stack[50];int top=-1;
    stack[++top]=productions[0][0];
    stack[++top]='\0';
    int t=0;
    int c=0;
    printf("Stack\tString\tRule\n");
    printf("%s\t%s\n",stack,st);
    while(true)
    {
        if(top==0 && st[t]=='$')
        {
            printf("Accepted");
            break;
        }
        if(((stack[top-1]>='a' && stack[top-1]<='z') || isterm(stack[top-1])) && st[t]!='$')
        {
            t++;
            top--;
            printf("%s\t",stack);
            printSting(st,t);
            printf("\t");
            printf("Match");
            printf("\n");
        }
        if(stack[top-1]>='A' && stack[top-1]<='Z')
        {
            char temp=stack[top-1];
            int tid=-1,ntid=-1;
            for(int i=0;i<nind;i++)
            {
                if(nonterm[i]==stack[top-1])
                    ntid=i;  
            }
            for(int i=0;i<teind;i++)
            {
                if(term[i]==st[t])
                {
                    tid=i;
                }
            }
            top--;
            top--;
            if(ntid==-1 || tid==-1)
            {
                printf("Not Accpted");
                break;
            }
            if(strcmp(table[ntid][tid],"e")!=0)
            {
                for(int i=strlen(table[ntid][tid])-1;i>=0;i--)
                {
                    stack[++top]=table[ntid][tid][i];
                }
            }
            stack[++top]='\0';
            printf("%s\t",stack);
            printSting(st,t);
            printf("\t");
            printf("%c->%s",temp,table[ntid][tid]);
            printf("\n");   
        }
    }
}