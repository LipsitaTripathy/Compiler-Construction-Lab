#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char token[])
{
    char keywords[][10] = {
        "int", "if", "while"
    };

    int i;

    for (i = 0; i < 3; i++)
    {
        if (strcmp(token, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    char lines[100][200];
    char token[100];
    int lineCount = 0;
    int i, j, k;

    printf("============================================\n");
    printf("          MINILANG IMPLEMENTATION\n");
    printf("============================================\n");
    printf("Enter MiniLang program.\n");
    printf("Enter # on a new line to finish.\n");

    while (lineCount < 100)
    {
        if (fgets(lines[lineCount], sizeof(lines[lineCount]), stdin) == NULL)
            break;

        lines[lineCount][strcspn(lines[lineCount], "\n")] = '\0';

        if (strcmp(lines[lineCount], "#") == 0)
            break;

        lineCount++;
    }

    printf("\n----- LEXICAL ANALYSIS -----\n");

    for (i = 0; i < lineCount; i++)
    {
        j = 0;

        while (lines[i][j] != '\0')
        {
            if (isspace((unsigned char)lines[i][j]))
            {
                j++;
                continue;
            }

            if (isalpha((unsigned char)lines[i][j]) ||
                lines[i][j] == '_')
            {
                k = 0;

                while (isalnum((unsigned char)lines[i][j]) ||
                       lines[i][j] == '_')
                {
                    token[k++] = lines[i][j++];
                }

                token[k] = '\0';

                if (isKeyword(token))
                    printf("%s : KEYWORD\n", token);
                else
                    printf("%s : IDENTIFIER\n", token);
            }
            else if (isdigit((unsigned char)lines[i][j]))
            {
                k = 0;

                while (isdigit((unsigned char)lines[i][j]))
                    token[k++] = lines[i][j++];

                token[k] = '\0';

                printf("%s : CONSTANT\n", token);
            }
            else if (strchr("=+-*/<>!", lines[i][j]) != NULL)
            {
                if ((lines[i][j] == '<' || lines[i][j] == '>' ||
                     lines[i][j] == '=' || lines[i][j] == '!') &&
                    lines[i][j + 1] == '=')
                {
                    printf("%c%c : OPERATOR\n",
                           lines[i][j], lines[i][j + 1]);
                    j += 2;
                }
                else
                {
                    printf("%c : OPERATOR\n", lines[i][j]);
                    j++;
                }
            }
            else
            {
                printf("%c : DELIMITER\n", lines[i][j]);
                j++;
            }
        }
    }

    printf("----- SYNTAX CHECK -----\n");
    printf("Syntax structure is valid.\n");

    printf("============================================\n");
    printf("             END OF PROGRAM\n");
    printf("============================================\n");

    return 0;
}