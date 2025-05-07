#include <stdio.h>

int main () {
    int a=4, ris=1, conta=0;
    while (a > 0) {
        ris = ris * a;
        a--;
    }
    printf("Il risultato è %d\n", ris);
    return 0;
}