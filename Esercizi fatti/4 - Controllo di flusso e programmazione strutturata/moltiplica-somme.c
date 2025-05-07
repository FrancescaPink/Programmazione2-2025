#include <stdio.h>

int main () {
    int a=5, b=9, ris=0, conta=0;
    while (conta < b) {
        ris = ris + a;
        conta++;
    }
    printf("Il risultato è %d\n", ris);
    return 0;
}