#include <ctype.h>
#include <stdio.h>
#include <string.h>

char input[200], result[200];
int pos = 0, temp = 1, error = 0;

void expression();
void term();
void factor();

void factor()
{
    int j = 0;

    if (input[pos] == '(')
    {
        pos++;
        expression();

        if (input[pos] == ')')
            pos++;
        else
            error = 1;
    }
    else if (isalnum((unsigned char)input[pos]) || input[pos] == '_')
    {
        while (isalnum((unsigned char)input[pos]) || input[pos] == '_')
            result[j++] = input[pos++];

        result[j] = '\0';
    }
    else
    {
        error = 1;
    }
}

void term()
{
    char left[200], t[10], op;

    factor();
    if (error) return;
    strcpy(left, result);

    while (input[pos] == '*' || input[pos] == '/')
    {
        op = input[pos++];
        factor();
        if (error) return;

        sprintf(t, "t%d", temp++);
        printf("%s = %s %c %s\n", t, left, op, result);
        strcpy(left, t);
    }

    strcpy(result, left);
}

void expression()
{
    char left[200], t[10], op;

    term();
    if (error) return;
    strcpy(left, result);

    while (input[pos] == '+' || input[pos] == '-')
    {
        op = input[pos++];
        term();
        if (error) return;

        sprintf(t, "t%d", temp++);
        printf("%s = %s %c %s\n", t, left, op, result);
        strcpy(left, t);
    }

    strcpy(result, left);
}

int main()
{
    printf("Enter an arithmetic expression: ");
    scanf("%199s", input);

    printf("\nThree-address intermediate code:\n");
    expression();

    if (error || input[pos] != '\0')
        printf("Invalid expression.\n");
    else
        printf("Result is stored in: %s\n", result);

    return 0;
}
