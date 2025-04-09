#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
bool iskeyword(char st[])
{
    const char* keywords[]= 
            { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if",
            "int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union",
            "unsigned", "void","volatile","while" };
    for (int i = 0;i < sizeof(keywords) / sizeof(keywords[0]); i++) 
    {
        if (strcmp(st, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}
bool delimeter(char chr)
{
    return (chr == ',' || chr == ';' || chr == '%' || chr == '(' || chr == ')' || chr == '[' || chr == ']'|| chr == '{' || chr == '}');
}
bool operator(char chr)
{
    return (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '>' || chr == '<' || chr == '=');
}
bool isValidIdentifier(char str[])
{
    return (str[0] != '0' && str[0] != '1' && str[0] != '2' && str[0] != '3' && str[0] != '4' && str[0] != '5' && str[0] != '6' && str[0] != '7' && str[0] != '8'
     && str[0] != '9' && !delimeter(str[0]) && str[0]!='\0');
}
int main()
{
    FILE *fptr;
    fptr = fopen("source.txt", "r");
    char str[500];
    int ind=0;
    if(fptr != NULL) 
    {
        while(fgets(str, 100, fptr)) 
        {
            int i=0,j=0;
            char each[100];
            while(str[i]!='\0')
            {
                if(!isalpha(str[i]) && (delimeter(str[i])||operator(str[i]))) 
                {
                    if(iskeyword(each))
                    {
                        printf("<%s,Keyword>\n",each);
                    }
                    else if(isValidIdentifier(each))
                    {
                        printf("<%s,Indentifier>\n",each);
                    }
                    if(delimeter(str[i]))
                    {
                        printf("<%c,Delimeter>\n",str[i]);
                    }
                    if(operator(str[i]))
                    {
                        printf("<%c,Operator>\n",str[i]);
                    }
                    for(int k=0;k<j;k++)
                        each[k]='\0';
                    j=0;
                    i++;
                    continue;
                }
                else if(str[i]==' ')
                {
                    if(iskeyword((each)))printf("<%s,Keyword>\n",each);
                    else if(isValidIdentifier(each)) printf("<%s,Indentifier>\n",each);
                    for(int k=0;k<j;k++)
                        each[k]='\0';
                    j=0;
                    i++;
                }
                else
                {
                    each[j++]=str[i];
                    i++;
                }
            }
        }
    } 
    else 
    {
        printf("Not able to open the file.");
    }
    fclose(fptr);
}


