#include <stdio.h>
#include <string.h>

#define EPSILON "#"
#define MAX_NT 30
#define MAX_PROD 50
#define MAX_LEN 50

int main() {
    int original_n, total_n;
    char nt[MAX_NT][10]; // 2D char array to hold strings like "A", "A'", "A''"
    char prod[MAX_NT][MAX_PROD][MAX_LEN];
    int num_prods[MAX_NT];

    printf("Enter number of non-terminals: ");
    if (scanf("%d", &original_n) != 1) return 1;
    total_n = original_n;

    // --- 1. Input Phase ---
    for (int i = 0; i < original_n; i++) {
        char temp_nt;
        printf("\nEnter non-terminal %d: ", i + 1);
        scanf(" %c", &temp_nt);
        
        // Convert the single char into a string so we can easily append "'" later
        nt[i][0] = temp_nt;
        nt[i][1] = '\0';

        printf("Enter number of productions for %s: ", nt[i]);
        scanf("%d", &num_prods[i]);

        for (int j = 0; j < num_prods[i]; j++) {
            printf("Enter production %d for %s (use '%s' for epsilon): ", j + 1, nt[i], EPSILON);
            scanf("%s", prod[i][j]);
        }
    }

    // --- 2. Processing Phase (Indirect & Direct Left Recursion) ---
    for (int i = 0; i < original_n; i++) {
        
        // Step A: Substitute A_i -> A_j (gamma) for all j < i
        for (int j = 0; j < i; j++) {
            int new_num = 0;
            char new_prod[MAX_PROD][MAX_LEN];

            for (int k = 0; k < num_prods[i]; k++) {
                // If the production starts with A_j, it's an indirect recursion candidate
                if (prod[i][k][0] == nt[j][0]) {
                    
                    // Replace A_j with all of A_j's productions
                    for (int m = 0; m < num_prods[j]; m++) {
                        
                        // Handle epsilon appropriately
                        if (strcmp(prod[j][m], EPSILON) == 0) {
                            strcpy(new_prod[new_num], prod[i][k] + 1);
                            if (strlen(new_prod[new_num]) == 0) {
                                strcpy(new_prod[new_num], EPSILON);
                            }
                        } else {
                            strcpy(new_prod[new_num], prod[j][m]);
                            strcat(new_prod[new_num], prod[i][k] + 1);
                        }
                        new_num++;
                    }
                } else {
                    // Keep original production
                    strcpy(new_prod[new_num], prod[i][k]);
                    new_num++;
                }
            }
            
            // Update A_i's productions after substitution
            num_prods[i] = new_num;
            for (int k = 0; k < new_num; k++) {
                strcpy(prod[i][k], new_prod[k]);
            }
        }

        // Step B: Eliminate Direct Left Recursion for A_i
        int has_rec = 0;
        for (int k = 0; k < num_prods[i]; k++) {
            if (prod[i][k][0] == nt[i][0]) {
                has_rec = 1;
                break;
            }
        }

        if (has_rec) {
            int prime_idx = total_n; 
            total_n++; // Expand our grammar to include the new A_i'

            // Create the A_i' string
            strcpy(nt[prime_idx], nt[i]);
            strcat(nt[prime_idx], "'");

            int new_num_i = 0;
            int new_num_prime = 0;
            char new_prod_i[MAX_PROD][MAX_LEN];
            char new_prod_prime[MAX_PROD][MAX_LEN];

            for (int k = 0; k < num_prods[i]; k++) {
                if (prod[i][k][0] == nt[i][0]) {
                    // Recursive case (Alpha)
                    strcpy(new_prod_prime[new_num_prime], prod[i][k] + 1);
                    strcat(new_prod_prime[new_num_prime], nt[prime_idx]);
                    new_num_prime++;
                } else {
                    // Non-recursive case (Beta)
                    if (strcmp(prod[i][k], EPSILON) == 0) {
                        strcpy(new_prod_i[new_num_i], nt[prime_idx]);
                    } else {
                        strcpy(new_prod_i[new_num_i], prod[i][k]);
                        strcat(new_prod_i[new_num_i], nt[prime_idx]);
                    }
                    new_num_i++;
                }
            }

            // Fallback for an invalid grammar with zero Beta productions
            if (new_num_i == 0) {
                strcpy(new_prod_i[new_num_i++], nt[prime_idx]);
            }

            // A' -> epsilon
            strcpy(new_prod_prime[new_num_prime++], EPSILON);

            // Save the updated base non-terminal
            num_prods[i] = new_num_i;
            for (int k = 0; k < new_num_i; k++) {
                strcpy(prod[i][k], new_prod_i[k]);
            }

            // Save the newly generated prime non-terminal
            num_prods[prime_idx] = new_num_prime;
            for (int k = 0; k < new_num_prime; k++) {
                strcpy(prod[prime_idx][k], new_prod_prime[k]);
            }
        }
    }

    // --- 3. Output Phase ---
    printf("\n--- Final Grammar Without Left Recursion ---\n");
    for (int i = 0; i < total_n; i++) {
        printf("%s -> ", nt[i]);
        for (int j = 0; j < num_prods[i]; j++) {
            printf("%s", prod[i][j]);
            if (j < num_prods[i] - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    }

    return 0;
}
