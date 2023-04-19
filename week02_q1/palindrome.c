/** Algorithm & Complexity Analysis
 *
 * isPalindrome(char A[], int len):
 *
 * Input:  String array A and length of a string(n characters)
 * Output: true or false
 *
 * Statement                     # primitive operations
 * ----------------------------------------------------
 * for all i=1 up to n do      (n+1)+n
 *   if A[i] == A[len - 1] then 2n
 *     n=n-1                    n
 *   else return false          1
 * end for
 * return true                  1
 * ----------------------------------------------------
 * Total: 5n+3, which is O(n)
 *
 **/

#include "stdio.h"
#include "stdbool.h"
#include "string.h"

bool isPalindrome(char A[], int len) {
    int i;
    for (i = 0; i<=len; i++) {
        if (A[i] == A[len - 1]) {
            len--;
        } else {
            return false;
        }
    }
    return true;
}

int main(void) {
    bool result = 0;
    char w[BUFSIZ];
    int len;

    printf("Enter a word: ");
    scanf("%s", w);
    len = strlen(w);

    result = isPalindrome(w, len);

    if (result) {
        printf("yes");
    } else {
        printf("no");
    }

    return 0;
}
