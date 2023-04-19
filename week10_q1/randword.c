#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int main(void) {
//    int length;
//    unsigned int seed;
//    scanf("%d", &length);
//    scanf("%d", &seed);
//    char str[length];
//    srand(seed);
//    for (int i = 0; i < length; ++i) {
//        str[i] = 'a' + rand() % 26;
//    }
//    for (int i = 0; i < length ; ++i) {
//        printf("%c", str[i]);
//    }
//}

int main(int n, char **input) {
    int length = atoi(input[1]);
    int seed = atoi(input[2]);
    char str[length];
    srand(seed);
    for (int i = 0; i < length; ++i) {
        str[i] = 'a' + rand() % 26;
    }
    for (int i = 0; i < length ; ++i) {
        printf("%c", str[i]);
    }
}
