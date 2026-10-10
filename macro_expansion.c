#include <stdio.h>
#include <string.h>

#define MAX_MACROS 20
#define MAX_LINES 50
#define MAX_LEN 200

struct Macro {
char name[50];
char body[MAX_LINES][MAX_LEN];
int lines;
};

struct Macro macros[MAX_MACROS];
int macroCount;

int findMacro(char *name) {
int i;

for (i = 0; i < macroCount; i++) {
    if (strcmp(macros[i].name, name) == 0)
        return i;
}

return -1;

}

void expandMacro(char *name, int depth) {
int index, i;

if (depth > 10) {
    printf("Error: Recursive expansion limit reached.\n");
    return;
}

index = findMacro(name);

if (index == -1) {
    printf("%s\n", name);
    return;
}

for (i = 0; i < macros[index].lines; i++) {
    char line[MAX_LEN];
    char *token;

    strcpy(line, macros[index].body[i]);
    token = strtok(line, " \t\n");

    if (token != NULL && findMacro(token) != -1) {
        expandMacro(token, depth + 1);
    } else {
        printf("%s", macros[index].body[i]);

        if (strchr(macros[index].body[i], '\n') == NULL)
            printf("\n");
    }
}

}

int main(void) {
int i, j;
char line[MAX_LEN];
char name[50];

printf("Enter number of macro definitions: ");
scanf("%d", &macroCount);
getchar();

if (macroCount < 1 || macroCount > MAX_MACROS) {
    printf("Invalid number of macro definitions.\n");
    return 1;
}

for (i = 0; i < macroCount; i++) {
    printf("\nEnter macro name: ");
    scanf("%49s", macros[i].name);
    getchar();

    printf("Enter number of lines in macro %s: ",
           macros[i].name);
    scanf("%d", &macros[i].lines);
    getchar();

    if (macros[i].lines < 1 ||
        macros[i].lines > MAX_LINES) {
        printf("Invalid number of lines.\n");
        return 1;
    }

    printf("Enter macro %s body:\n", macros[i].name);

    for (j = 0; j < macros[i].lines; j++) {
        fgets(macros[i].body[j], MAX_LEN, stdin);
    }
}

printf("\nIdentified Macro Definitions:\n");

for (i = 0; i < macroCount; i++) {
    printf("\nMacro %s:\n", macros[i].name);

    for (j = 0; j < macros[i].lines; j++)
        printf("%s", macros[i].body[j]);
}

printf("\nEnter assembly instruction to expand: ");
scanf("%49s", name);

printf("\nExpanded Assembly Code:\n");
expandMacro(name, 0);

return 0;

}