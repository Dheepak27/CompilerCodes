#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

char stack[100];
int top = -1;

void push(char x) 
{
    stack[++top] = x;
}

char pop() 
{
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

int precedence(char x) 
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return -1;
}

void conpost(char *exp, char *postfix) 
{
    char *e, x;
    int i = 0; 
    e = exp;
    
    while (*e != '\0') 
    {
        if (isalnum(*e))
            postfix[i++] = *e;
        else if (*e == '(') 
            push(*e);
        else if (*e == ')') 
        {
            while ((x = pop()) != '(')
                postfix[i++] = x;
        } else 
        {
            while (top != -1 && precedence(stack[top]) >= precedence(*e))
                postfix[i++] = pop();
            push(*e);
        }
        e++;
    }
    while (top != -1)
        postfix[i++] = pop();
    
    postfix[i] = '\0';
}

void genTAC(char *postfix) 
{
    char operands[100][100];
    int opTop = -1, tempCount = 1;
    
    printf("Three Address Code:\n");
    
    for (int i = 0; i < strlen(postfix); i++) 
    {
        if (isalnum(postfix[i])) 
        {
            char operand[2];operand[0]=postfix[i];operand[1]='\0';
            strcpy(operands[++opTop], operand);
        } 
        else 
        {
            char op1[100], op2[100], res[100];
            strcpy(op2, operands[opTop--]);
            strcpy(op1, operands[opTop--]);
            sprintf(res, "T%d", tempCount++);
            printf("%s = %s %c %s\n", res, op1, postfix[i], op2);
            strcpy(operands[++opTop], res);
        }
    }
}

int main() 
{
    char exp[100], postfix[100];
    printf("Enter Infix expression:\n");
    scanf("%s", exp);
    conpost(exp, postfix);
    printf("Postfix Expression:\n%s\n", postfix);
    genTAC(postfix);
    return 0;
}
