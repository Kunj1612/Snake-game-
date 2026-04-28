#include <stdio.h>
#include <ctype.h>
#include <string.h>

int total_nt;
char nt_list[10];
int num_prods[10];
char prod[10][20][20];

void find_first(char c, char res[], int *ptr) {
    if (!isupper(c)) {
        for (int i = 0; i < *ptr; i++) {
            if (res[i] == c) return;
        }
        res[(*ptr)++] = c;
        return;
    }

    int idx = -1;
    for (int i = 0; i < total_nt; i++) {
        if (nt_list[i] == c) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) return;

    for (int i = 0; i < num_prods[idx]; i++) {
        if (prod[idx][i][0] == '#') {
            int exists = 0;
            for (int k = 0; k < *ptr; k++) {
                if (res[k] == '#') exists = 1;
            }
            if (!exists) res[(*ptr)++] = '#';
        } else {
            int j = 0, has_eps = 1;
            while (prod[idx][i][j] != '\0' && has_eps) {
                int prev = *ptr;
                find_first(prod[idx][i][j], res, ptr);

                has_eps = 0;
                for (int k = prev; k < *ptr; k++) {
                    if (res[k] == '#') {
                        has_eps = 1;
                        res[k] = res[--(*ptr)];
                        break;
                    }
                }
                j++;
            }
            if (has_eps) {
                int exists = 0;
                for (int k = 0; k < *ptr; k++) {
                    if (res[k] == '#') exists = 1;
                }
                if (!exists) res[(*ptr)++] = '#';
            }
        }
    }
}

int main() {
    char res[20];

    printf("Enter number of non-terminals: ");
    scanf("%d", &total_nt);

    for (int i = 0; i < total_nt; i++) {
        printf("\nEnter Non-Terminal: ");
        scanf(" %c", &nt_list[i]);

        printf("Enter number of productions: ");
        scanf("%d", &num_prods[i]);

        printf("Enter productions:\n");
        for (int j = 0; j < num_prods[i]; j++) {
            scanf("%s", prod[i][j]);
        }
    }

    printf("\n--- FIRST Sets ---\n");
    for (int i = 0; i < total_nt; i++) {
        int ptr = 0;
        find_first(nt_list[i], res, &ptr);

        printf("FIRST(%c) = { ", nt_list[i]);
        for (int j = 0; j < ptr; j++) {
            printf("%c", res[j]);
            if (j < ptr - 1) printf(", ");
        }
        printf(" }\n");
    }

    return 0;
}
