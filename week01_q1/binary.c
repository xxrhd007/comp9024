#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"

int main(void){
    char str[BUFSIZ];
    int n;
    int k=2;


    StackInit();

    printf("Enter a number: ");
    scanf("%s", str);
    n = atoi(str);
    do {
        StackPush(n % k);
        n = n / k;
    } while (n > 0);

    while (!StackIsEmpty()) {
        printf("%d", StackPop());
    }


    return 0;
}
