#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a string matches the pattern a*bb
bool isValidString(const char *str)
{
    int i = 0;

    // Check for zero or more 'a's
    while (str[i] == 'a')
    {
        i++;
    }

    // Check for exactly two 'b's at the end
    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0')
    {
        return true;
    }

    return false;
}

int main() {
    char input[100][100]; // Array to hold multiple strings
    int count;

    printf("Enter the number of strings: ");
    scanf("%d", &count);
    getchar(); // Consume the newline character left by scanf

    printf("Enter %d strings:\n", count);
    for (int i = 0; i < count; i++) {
        fgets(input[i], sizeof(input[i]), stdin);

        // Remove newline character if present
        size_t len = strlen(input[i]);
        if (len > 0 && input[i][len - 1] == '\n') {
            input[i][len - 1] = '\0';
        }
    }

    printf("\nResults:\n");
    for (int i = 0; i < count; i++) {
        if (isValidString(input[i])) {
            printf("String %d: %s -> Valid String\n", i + 1, input[i]);
        } else {
            printf("String %d: %s -> Invalid String\n", i + 1, input[i]);
        }
    }

    return 0;
}
