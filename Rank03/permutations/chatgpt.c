#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to swap two characters
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Function to compare two strings (used for sorting)
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Recursive function to generate permutations
void permute(char *str, int left, int right, char **results, int *count) {
    if (left == right) {
        results[*count] = (char *)malloc((strlen(str) + 1) * sizeof(char));
        if (!results[*count]) {
            fputs("Memory allocation failed\n", stderr);
            exit(1);
        }
        strcpy(results[*count], str);
        (*count)++;
        return;
    }

    for (int i = left; i <= right; i++) {
        printf("%i %s\n", i, str);
	
	swap(&str[left], &str[i]);
        printf("%i %s\n\n", i, str);
        
	permute(str, left + 1, right, results, count);
        swap(&str[left], &str[i]); // Backtrack
        
        printf("%i %s\n", i, str);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fputs("Usage: ./permutations <characters>\n", stderr);
        return 1;
    }

    char *input = argv[1];
    int length = strlen(input);

    // Calculate factorial of length to determine maximum permutations
    int max_permutations = 1;
    for (int i = 2; i <= length; i++) {
        max_permutations *= i;
    }

    // Allocate memory to store all permutations
    char **results = (char **)calloc(max_permutations, sizeof(char *));
    if (!results) {
        fputs("Memory allocation failed\n", stderr);
        return 1;
    }

    // Generate permutations
    int count = 0;
    permute(input, 0, length - 1, results, &count);

    // Sort permutations in alphabetical order
    qsort(results, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        fputs(results[i], stdout);
        fputs("\n", stdout);
        free(results[i]);
    }
    free(results);
    return 0;
}

