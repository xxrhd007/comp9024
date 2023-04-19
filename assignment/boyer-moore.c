#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TEXT_LENGTH 1024
#define MAX_P_A_LENGTH 128
#define TEXT_FORMAT_STRING "%[^\n]%*c"

int *lastOccurrence(char *pattern, char *alphabet) {
    int *array = malloc(sizeof(int) * strlen(alphabet) + 1);
    for (size_t i = 0; i < strlen(alphabet); ++i) {
        array[i] = -1;
    }
    for (int i = 0; i < strlen(alphabet); ++i) {
        for (int j = 0; j < strlen(pattern); ++j) {
            if (alphabet[i] == pattern[j]) {
                array[i] = j;
            }
        }
    }
    return array;
}

int min(int i, int j) {
    if (i < j) {
        return i;
    } else {
        return j;
    }
}

int BoyerMooreMatch(char *text, char *pattern, char *alphabet) {
    int *list = lastOccurrence(pattern, alphabet);
    int i, j;
    i = strlen(pattern) - 1;
    j = strlen(pattern) - 1;
    while (i < strlen(text)) {
        if (text[i] == pattern[j]) {
            if (j == 0) {
                return i;
            } else {
                i = i - 1;
                j = j - 1;
            }
        } else {
            int r = 0;
            for (int k = 0; k < strlen(alphabet); ++k) {
                if (alphabet[k] == text[i]){
                    r = k;
                }
            }
            i = i + strlen(pattern) - min(j, 1 + list[r]);
            j = strlen(pattern) - 1;
        }
    }
    return -1;
}

int main(void) {
    printf("Enter alphabet: ");
    char A[MAX_P_A_LENGTH];
    scanf(TEXT_FORMAT_STRING, A);
    printf("Enter text: ");
    char T[MAX_TEXT_LENGTH];
    scanf(TEXT_FORMAT_STRING, T);
    printf("Enter pattern: ");
    char P[MAX_P_A_LENGTH];
    scanf(TEXT_FORMAT_STRING, P);
    printf("\n");
    int *L = lastOccurrence(P, A);
    for (size_t i = 0; i < strlen(A); ++i) {
        printf("L[%c] = %d\n", A[i], L[i]);
    }
    printf("\n");
    int p = BoyerMooreMatch(T, P, A);
    if (p != -1) {
        printf("Match found at position %d.", p);
    } else {
        printf("No match.");
    }
}