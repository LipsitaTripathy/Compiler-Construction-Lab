#include <stdio.h>
#include <string.h>

int main()
{
    int n, i;
    char lines[100][100];
    char macroName[100];
    int start = -1, end = -1;

    printf("Enter number of lines : ");
    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++)
    {
        fgets(lines[i], sizeof(lines[i]), stdin);
        lines[i][strcspn(lines[i], "\n")] = '\0';
    }

    /* Identify the macro definition */
    for (i = 0; i < n; i++)
    {
        if (strcmp(lines[i], "MACRO") == 0)
        {
            start = i;
            if (i + 1 < n)
                strcpy(macroName, lines[i + 1]);
        }

        if (strcmp(lines[i], "MEND") == 0)
        {
            end = i;
            break;
        }
    }

    /* Expand the macro when it is called */
    if (start != -1 && end != -1)
    {
        for (i = end + 1; i < n; i++)
        {
            if (strcmp(lines[i], macroName) == 0)
            {
                printf("\n");

                for (int j = start + 2; j < end; j++)
                {
                    printf("%s\n", lines[j]);
                }
            }
        }
    }

    return 0;
}