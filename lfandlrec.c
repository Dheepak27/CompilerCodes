#include <stdio.h>
#include <string.h>
int min(int a,int b)
{
    if(a<b) return a;
    else return b;
}
int main()
{
    int n;
    printf("Enter Number of Productions:\n");
    scanf("%d",&n);
    char productions[n][50];
    char lr[20][50];
    int ind=0;
    printf("Enter Productions:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%s",productions[i]);
    }
    printf("After Elimnating Left Recursion\n");
    for(int i=0;i<n;i++)
    {
        char beta[20][50];
        char alpha[20][50];
        int ind1=0,ind2=0,flag=0;char A=productions[i][0];
        for(int j=0;j<strlen(productions[i]);j++)
        {
            if((productions[i][j]=='>' || productions[i][j]=='|') && productions[i][j+1]==productions[i][0])
            {
                int p=0;
                for(int k=j+1;k<strlen(productions[i]);k++)
                {
                    if(productions[i][k]!=productions[i][0] && productions[i][k]!='|')
                    {
                        alpha[ind1][p++]=productions[i][k];
                    }
                    else if(productions[i][k]=='|')
                    {
                        break;
                    }
                }
                alpha[ind1][p++]='\0';
                ind1++;
                flag=1;
            }
            else if(productions[i][j]=='|' && flag==1)
            {
                int p=0;
                for(int k=j+1;k<strlen(productions[i]);k++)
                {
                    if(productions[i][k]!='|')
                    {
                        beta[ind2][p++]=productions[i][k];
                    }
                    else
                        break;
                }
                beta[ind2][p++]='\0';
                ind2++;
            }
        }
        if(flag==1)
        {
            int t=0;char temp[50];
            temp[t++]=A;
            temp[t++]='-';
            temp[t++]='>';
            for(int i=0;i<ind2;i++)
            {
                if(i!=ind2-1)
                {
                    for(int k=0;k<strlen(beta[i]);k++)
                        temp[t++]=beta[i][k];
                    temp[t++]=A;
                    temp[t++]='\'';
                    temp[t++]='|';
                }
                else
                {
                    for(int k=0;k<strlen(beta[i]);k++)
                        temp[t++]=beta[i][k];
                    temp[t++]=A;
                    temp[t++]='\'';
                }
            }
            temp[t++]='\0';
            strcpy(lr[ind++],temp);
            temp[50];t=0;
            temp[t++]=A;
            temp[t++]='\'';
            temp[t++]='-';
            temp[t++]='>';
            for(int i=0;i<ind1;i++)
            {
                for(int k=0;k<strlen(alpha[i]);k++)
                    temp[t++]=alpha[i][k];
                temp[t++]=A;
                temp[t++]='\'';
                temp[t++]='|';
            }
            temp[t++]='e';
            temp[t++]='\0';
            strcpy(lr[ind++],temp); 
        }
        else
        {
            strcpy(lr[ind++],productions[i]);
        }
    }
    for(int i=0;i<ind;i++)
    {
        printf("%s\n",lr[i]);
    }
    printf("After Removing Left Factoring\n");
    
    for(int i=0;i<ind;i++)
    {
        char t[50];int ind4=0;int ind3=0;char alpha[20][50];
        for(int j=3;j<strlen(lr[i]);j++)
        {
            if(lr[i][j]=='|')
            {
                t[ind4++]='\0';
                strcpy(alpha[ind3++],t);
                t[50];ind4=0;
                continue;
            }
            t[ind4++]=lr[i][j];
        }
        t[ind4++]='\0';
        strcpy(alpha[ind3++],t);
        // printf("%d\n",i);
        int match=10000;
        char str1[50];
        strcpy(str1,alpha[0]);
        for(int j=1;j<ind3;j++)
        {
            int loc=0;
            for(int k=0;k<min(strlen(str1),strlen(alpha[j]));k++)
            {
                if(str1[k]==alpha[j][k])
                    loc++;
                else
                    break;
            }
            match=min(match,loc);
        }
        if(match==10000)
            match=0;
        // printf("%d\n",match);
        // for(int m=0;m<ind3;m++)
        // {
        //     printf("%s\n",alpha[m]);
        // }
        if(match>0)
        {
            char alp[50];
            strncpy(alp,str1+0,match);
            alp[match]='\0';
            printf("%c->%s%c'\n",lr[i][0],alp,lr[i][0]);
            printf("%c'->",lr[i][0]);
            for(int m=0;m<ind3;m++)
            {
                char bet[50];
                strncpy(bet,alpha[m]+match,strlen(alpha[m]));
                bet[strlen(alpha[m])+1]='\0';
                if(m!=ind3-1)
                    printf("%s|",bet);
                else
                    printf("%s",bet);
            }
        }
        else
        {
            printf("%s\n",lr[i]);
        }
    }
}