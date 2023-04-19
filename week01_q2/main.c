#include "stdio.h"
#include "stdlib.h"
#include "IntQueue.h"

int main(void) {
    char str[BUFSIZ];
    int n;
    int i;
    int k=2;

    QueueInit();

    printf("Enter a positive number: ");
    scanf("%s", str);
    n = atoi(str);
    do {
        QueueEnqueue(n % k);
        n = n / k;
    } while (n > 0);

    while (!QueueIsEmpty()) {
        printf("%d", QueueDequeue());
    }

    return 0;
}