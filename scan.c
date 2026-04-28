#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[1000];
int i = 0;

// keywords
char *keywords[] = {"int", "float", "if", "else", "while", "return"};
int keywordCount = 6;

// check keyword
int isKeyword(char *str) {
    for (int k = 0; k < keywordCount; k++) {
        if (strcmp(str, keywords[k]) == 0)
            return 1;
    }
    return 0;
}

// IDENTIFIER / KEYWORD
void getIdentifier() {
    char temp[50];
    int j = 0;

    while (isalnum(input[i])) {
        temp[j++] = input[i++];
    }
    temp[j] = '\0';

    if (isKeyword(temp))
        printf("KEYWORD: %s\n", temp);
    else
        printf("IDENTIFIER: %s\n", temp);
}

// NUMBER (INT / DOUBLE)
void getNumber() {
    int state = 0;
    int start = i;

    while (input[i] != '\0') {
        switch (state) {

            case 0:
                if (isdigit(input[i]))
                    state = 1;
                else if (input[i] == '.')
                    state = 2;
                else
                    return;
                break;

            case 1:
                if (isdigit(input[i]))
                    state = 1;
                else if (input[i] == '.')
                    state = 2;
                else
                    goto end;
                break;

            case 2:
                if (isdigit(input[i]))
                    state = 3;
                else
                    goto end;
                break;

            case 3:
                if (isdigit(input[i]))
                    state = 3;
                else
                    goto end;
                break;
        }
        i++;
    }

end:
    if (state == 1) {
        printf("INT: ");
    } else if (state == 3) {
        printf("DOUBLE: ");
    } else {
        return;
    }

    for (int j = start; j < i; j++)
        printf("%c", input[j]);
    printf("\n");
}

// OPERATORS
void getOperator() {
    if (input[i] == '=' && input[i+1] == '=') {
        printf("OPERATOR: ==\n");
        i += 2;
    }
    else if (input[i] == '<' && input[i+1] == '=') {
        printf("OPERATOR: <=\n");
        i += 2;
    }
    else if (input[i] == '>' && input[i+1] == '=') {
        printf("OPERATOR: >=\n");
        i += 2;
    }
    else {
        printf("OPERATOR: %c\n", input[i]);
        i++;
    }
}

// COMMENTS (//)
void getComment() {
    if (input[i] == '/' && input[i+1] == '/') {
        i += 2;
        printf("COMMENT: ");
        while (input[i] != '\n' && input[i] != '\0') {
            printf("%c", input[i]);
            i++;
        }
        printf("\n");
    }
}

// MAIN SCANNER
void scanner() {
    while (input[i] != '\0') {

        // skip whitespace
        if (isspace(input[i])) {
            i++;
        }

        // identifier / keyword
        else if (isalpha(input[i])) {
            getIdentifier();
        }

        // number
        else if (isdigit(input[i]) || input[i] == '.') {
            getNumber();
        }

        // comment
        else if (input[i] == '/' && input[i+1] == '/') {
            getComment();
        }

        // operators
        else if (strchr("+-*/=<>()", input[i])) {
            getOperator();
        }

        // unknown
        else {
            printf("UNKNOWN: %c\n", input[i]);
            i++;
        }
    }
}

int main() {
    printf("Enter input:\n");
    fgets(input, sizeof(input), stdin);

    scanner();

    return 0;
}
