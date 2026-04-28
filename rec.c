#include <stdio.h>
#include <string.h>

#define EPSILON "#"

int main() {
    char nt[10];
    int n;
    char prod[10][20][20];
    int num_prods[10];

    printf("Enter number of non-terminals: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter non-terminal %d: ", i + 1);
        scanf(" %c", &nt[i]);

        printf("Enter number of productions for %c: ", nt[i]);
        scanf("%d", &num_prods[i]);

        for (int j = 0; j < num_prods[i]; j++) {
            printf("Enter production %d for %c (use '%s' for epsilon): ", j + 1, nt[i], EPSILON);
            scanf("%s", prod[i][j]);
        }
    }

    printf("\n--- Grammar After Removing Direct Left Recursion ---\n");

    for (int i = 0; i < n; i++) {
        int rec[20] = {0};
        int has_rec = 0;

        for (int j = 0; j < num_prods[i]; j++) {
            if (prod[i][j][0] == nt[i]) {
                rec[j] = 1;
                has_rec = 1;
            }
        }

        if (has_rec) {
            printf("%c -> ", nt[i]);

            int first = 1;
            for (int j = 0; j < num_prods[i]; j++) {
                if (!rec[j]) {
                    if (!first) printf(" | ");
                    
                    if (strcmp(prod[i][j], EPSILON) == 0) {
                        printf("%c'", nt[i]);
                    } else {
                        printf("%s%c'", prod[i][j], nt[i]);
                    }
                    first = 0;
                }
            }

            if (first) printf("%c'", nt[i]);
            printf("\n");

            printf("%c' -> ", nt[i]);

            int first2 = 1;
            for (int j = 0; j < num_prods[i]; j++) {
                if (rec[j]) {
                    if (!first2) printf(" | ");
                    printf("%s%c'", prod[i][j] + 1, nt[i]); 
                    first2 = 0;
                }
            }

            if (!first2) printf(" | ");
            printf("%s\n", EPSILON);
        } 
        else {
            printf("%c -> ", nt[i]);
            for (int j = 0; j < num_prods[i]; j++) {
                printf("%s", prod[i][j]);
                if (j < num_prods[i] - 1)
                    printf(" | ");
            }
            printf("\n");
        }
    }

    return 0;
}
