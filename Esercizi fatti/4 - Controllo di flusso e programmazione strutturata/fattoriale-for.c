#include <stdio.h>

int main () {
    int a=4, ris=1;
    for (int conta=0; conta < a; conta++) {
        ris = ris * (a - conta);
    }
    printf("Il risultato è %d\n", ris);
    return 0;
}