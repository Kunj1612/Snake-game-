#include <stdio.h>
#include <string.h>

char input[1000];
int i = 0;
int error = 0;

// function declarations
void E();
void E_Dash();
void T();
void T_Dash();
void F();

// match function
void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        printf("Error: expected %c\n", expected);
        error = 1;
    }
}

// E → T E'
void E() {
    T();
    E_Dash();
}

// E' → + T E' | ε
void E_Dash() {
    if (input[i] == '+') {
        match('+');
        T();
        E_Dash();
    }
}

// T → F T'
void T() {
    F();
    T_Dash();
}

// T' → * F T' | ε
void T_Dash() {
    if (input[i] == '*') {
        match('*');
        F();
        T_Dash();
    }
}

// F → (E) | i
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    }
    else if (input[i] == 'i') {
        match('i');
    }
    else {
        printf("Error\n");
        error = 1;
    }
}

int main() {
    printf("Enter input: ");

    // read full line (handles spaces)
    fgets(input, sizeof(input), stdin);

    // remove newline if present
    input[strcspn(input, "\n")] = '\0';

    E();

    if (error == 0 && input[i] == '\0')
        printf("Valid String\n");
    else
        printf("Invalid String\n");

    return 0;
}
