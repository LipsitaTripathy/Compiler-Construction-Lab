#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MACROS 20
#define MAX_LINES 100
#define MAX_LEN 200

typedef struct {
char name[50];
char body[MAX_LINES][MAX_LEN];
int count;
} Macro;

Macro macros[MAX_MACROS];
int macroCount = 0;

int findMacro(char *name) {
int i;
for (i = 0; i < macroCount; i++) {
if (strcmp(macros[i].name, name) == 0)
return i;
}
return -1;
}

void expandLine(char *line, int depth) {
char word[50];
int i = 0, j = 0, index;

if (depth > 10) {
    printf("Error: Recursive expansion limit reached.\n");
    return;
}

while (line[i] != '\0') {
    if (isalnum((unsigned char)line[i]) || line[i] == '_') {
        j = 0;

        while (isalnum((unsigned char)line[i]) ||
               line[i] == '_') {
            if (j < 49)
                word[j++] = line[i];
            i++;
        }

        word[j] = '\0';
        index = findMacro(word);

        if (index != -1) {
            int k;
            for (k = 0; k < macros[index].count; k++)
                expandLine(macros[index].body[k], depth + 1);
        } else {
            printf("%s", word);
        }
    } else {
        putchar(line[i]);
        i++;
    }
}

}

int main() {
char line[MAX_LEN];
char name[50];
int i, index;

printf("Enter number of macro definitions: ");
scanf("%d", &macroCount);
getchar();

if (macroCount < 0 || macroCount > MAX_MACROS) {
    printf("Invalid number of macros.\n");
    return 1;
}

for (i = 0; i < macroCount; i++) {
    printf("\nEnter macro name: ");
    scanf("%49s", macros[i].name);
    getchar();

    printf("Enter number of lines in macro body: ");
    scanf("%d", &macros[i].count);
    getchar();

    if (macros[i].count < 0 ||
        macros[i].count > MAX_LINES) {
        printf("Invalid number of lines.\n");
        return 1;
    }

    printf("Enter macro body, one line at a time:\n");

    for (int j = 0; j < macros[i].count; j++)
        fgets(macros[i].body[j], MAX_LEN, stdin);
}

printf("\nIdentified Macro Definitions:\n");

for (i = 0; i < macroCount; i++) {
    printf("Macro: %s\n", macros[i].name);
    for (int j = 0; j < macros[i].count; j++)
        printf("%s", macros[i].body[j]);
}

printf("\nEnter assembly program (END to finish):\n");

while (fgets(line, MAX_LEN, stdin)) {
    if (strncmp(line, "END", 3) == 0)
        break;
    expandLine(line, 0);
}

return 0;

}