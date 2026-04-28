#include <stdio.h>
#include <ctype.h>
#include <string.h>

int total_nt;
char nt_list[10];
int num_prods[10];
char prod[10][20][20];

void add_result(char c, char res[], int *ptr) {
    for (int i = 0; i < *ptr; i++) {
        if (res[i] == c) return;
    }
    res[(*ptr)++] = c;
}

void find_first(char c, char res[], int *ptr) {
    if (!isupper(c)) {
        add_result(c, res, ptr);
        return;
    }

    int idx = -1;
    for (int i = 0; i < total_nt; i++) {
        if (nt_list[i] == c) { idx = i; break; }
    }
    if (idx == -1) return;

    for (int i = 0; i < num_prods[idx]; i++) {
        if (prod[idx][i][0] == '#') {
            add_result('#', res, ptr);
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
            if (has_eps) add_result('#', res, ptr);
        }
    }
}

void find_follow(char c, char res[], int *ptr) {
    if (nt_list[0] == c) {
        add_result('$', res, ptr);
    }

    for (int i = 0; i < total_nt; i++) {
        for (int j = 0; j < num_prods[i]; j++) {
            for (int k = 0; prod[i][j][k] != '\0'; k++) {
                if (prod[i][j][k] == c) {
                    int next = k + 1;
                    int has_eps = 1;

                    while (prod[i][j][next] != '\0' && has_eps) {
                        int prev_ptr = *ptr;
                        find_first(prod[i][j][next], res, ptr);
                        
                        has_eps = 0;
                        for (int x = prev_ptr; x < *ptr; x++) {
                            if (res[x] == '#') {
                                has_eps = 1;
                                res[x] = res[--(*ptr)];
                                break;
                            }
                        }
                        next++;
                    }

                    if (prod[i][j][next] == '\0' && has_eps && c != nt_list[i]) {
                        find_follow(nt_list[i], res, ptr);
                    }
                }
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

        printf("Enter productions (use '#' for epsilon):\n");
        for (int j = 0; j < num_prods[i]; j++) {
            scanf("%s", prod[i][j]);
        }
    }

    printf("\n--- FOLLOW Sets ---\n");
    for (int i = 0; i < total_nt; i++) {
        int ptr = 0;
        find_follow(nt_list[i], res, &ptr);

        printf("FOLLOW(%c) = { ", nt_list[i]);
        for (int j = 0; j < ptr; j++) {
            printf("%c", res[j]);
            if (j < ptr - 1) printf(", ");
        }
        printf(" }\n");
    }

    return 0;
}
